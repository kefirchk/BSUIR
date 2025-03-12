from config import IMAGE_PATH, TRACKBARS, RAINBOW_PATH, WINDOW_HEIGHT, WINDOW_WIDTH, IMAGE_WIDTH, IMAGE_HEIGHT

import cv2
import numpy as np
from sklearn.cluster import KMeans


# Функция для вычисления центра тяжести контура
def calculate_center_of_mass(contour):
    moments = cv2.moments(contour)
    if moments['m00'] != 0:
        cx = int(moments['m10'] / moments['m00'])
        cy = int(moments['m01'] / moments['m00'])
        return cx, cy
    return None


# Функция для проверки на горизонтальную симметрию
def is_horizontally_symmetric(contour):
    x, y, w, h = cv2.boundingRect(contour)
    center_x = x + w // 2

    # Проверяем симметрию относительно вертикальной оси
    left_side = contour[contour[:, :, 0] < center_x]
    right_side = contour[contour[:, :, 0] > center_x]

    if len(left_side) > 0 and len(right_side) > 0:
        # Сравниваем площадь пикселей на двух сторонах
        left_area = cv2.contourArea(left_side) if len(left_side) > 0 else 0
        right_area = cv2.contourArea(right_side) if len(right_side) > 0 else 0
        return abs(left_area - right_area) < 0.33 * max(left_area, right_area)

    return False


# Функция для проверки на перевернутость
def is_inverted_v2(contour):
    if is_horizontally_symmetric(contour):
        return False  # Если симметрична, не перевернута (например, "0" или "8")

    # Для асимметричных цифр, например "6" и "9", анализируем центр тяжести
    x, y, w, h = cv2.boundingRect(contour)
    center_of_mass = calculate_center_of_mass(contour)
    if center_of_mass:
        _, center_y = center_of_mass
        if center_y > (y + h // 2):
            return False  # Центр тяжести ниже середины, скорее всего цифра правильная
        else:
            return True  # Центр тяжести выше середины, цифра перевернута

    return False  # Если не удалось определить, считаем правильной


# Функция для подсчета углов
def count_corners(mask, max_corners=100, quality_level=0.01, min_distance=10):
    corners = cv2.goodFeaturesToTrack(mask, maxCorners=max_corners, qualityLevel=quality_level, minDistance=min_distance)
    return len(corners) if corners is not None else 0


# Функция для расчета углов в контуре
def calculate_angles(contour):
    angles = []
    num_points = len(contour)

    for i in range(num_points):
        A = contour[i][0]
        B = contour[(i + 1) % num_points][0]
        C = contour[(i + 2) % num_points][0]

        AB = B - A
        BC = C - B

        norm_AB = np.linalg.norm(AB)
        norm_BC = np.linalg.norm(BC)

        if norm_AB > 0 and norm_BC > 0:
            cos_theta = np.dot(AB, BC) / (norm_AB * norm_BC)
            angle = np.arccos(np.clip(cos_theta, -1.0, 1.0))
            angles.append(np.degrees(angle))

    return angles

# Функция для извлечения признаков контура
def extract_features(cnt, img_mask):
    features = []
    area = cv2.contourArea(cnt)
    perimeter = cv2.arcLength(cnt, True)
    aspect_ratio = area / (perimeter ** 2) if perimeter > 0 else 0
    features.append(aspect_ratio)

    corners_count = count_corners(img_mask)
    features.append(corners_count)

    angles = calculate_angles(cnt)
    mean_angle = np.mean(angles) if angles else 0
    features.append(mean_angle)

    return features


# Основная функция обработки изображения
def process_img(img, color):
    img_mask = cv2.inRange(cv2.cvtColor(img, cv2.COLOR_BGR2HSV), color[0], color[1])
    img = cv2.bitwise_and(img, img, mask=img_mask)

    contours, _ = cv2.findContours(img_mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    drawing = np.zeros_like(img)  # Создаем пустое изображение для рисования

    features = []
    big_contours = []

    if contours:
        for cnt in contours:
            if cv2.contourArea(cnt) < 50:
                continue

            # Получаем минимальный повёрнутый прямоугольник
            rect = cv2.minAreaRect(cnt)
            center = tuple(map(int, rect[0]))  # Центр рамки
            angle = rect[2]

            # Убедимся, что меньшая сторона перпендикулярна оси X
            if rect[1][0] > rect[1][1]:
                angle += 90

            # Проверяем, перевернута ли цифра с использованием улучшенной проверки
            if is_inverted_v2(cnt):
                angle += 180  # Если перевернута, корректируем угол на 180 градусов

            # Вращаем контур
            M = cv2.getRotationMatrix2D(center, angle, 1.0)
            rotated_contour = cv2.transform(cnt, M).astype(np.int32)

            # Сохраняем контуры и извлекаем признаки для кластеризации
            features.append(extract_features(rotated_contour, img_mask))
            big_contours.append(rotated_contour)

    # Применяем K-Means кластеризацию для раскраски
    features = np.array(features)
    k = 4
    if len(features) >= k:
        kmeans = KMeans(n_clusters=k, random_state=0).fit(features)
        labels = kmeans.labels_
        colors = [
            (255, 0, 0),  # Синий
            (0, 255, 0),  # Зеленый
            (0, 0, 255),  # Красный
            (0, 255, 255),  # Желтый
        ]
        for i, contour in enumerate(big_contours):
            cv2.drawContours(drawing, [contour], -1, colors[labels[i]], -1)

    return img_mask, drawing


# Функция обновления изображения с трекбара
def update(value: int = 0):
    if not cv2.getWindowProperty('Controls', cv2.WND_PROP_VISIBLE):
        return

    color_low = (
        cv2.getTrackbarPos('h_min', 'Controls'),
        cv2.getTrackbarPos('s_min', 'Controls'),
        cv2.getTrackbarPos('v_min', 'Controls')
    )

    color_high = (
        cv2.getTrackbarPos('h_max', 'Controls'),
        cv2.getTrackbarPos('s_max', 'Controls'),
        cv2.getTrackbarPos('v_max', 'Controls')
    )
    color = (color_low, color_high)

    img_mask, img_mixed = process_img(img, color)

    img_mixed_resized = cv2.resize(img_mixed, (IMAGE_WIDTH, IMAGE_HEIGHT))
    img_mask_resized = cv2.resize(img, (IMAGE_WIDTH, IMAGE_HEIGHT))

    combined_result = cv2.vconcat([img_mask_resized, img_mixed_resized])
    cv2.imshow('Result', combined_result)


if __name__ == '__main__':
    img = cv2.imread(IMAGE_PATH)
    rainbow = cv2.imread(RAINBOW_PATH)

    img = cv2.resize(img, (WINDOW_WIDTH, WINDOW_HEIGHT))
    rainbow = cv2.resize(rainbow, (WINDOW_WIDTH, WINDOW_HEIGHT))

    cv2.namedWindow('Controls', cv2.WINDOW_NORMAL)
    for t in TRACKBARS:
        cv2.createTrackbar(t['trackbarName'], 'Controls', t['value'], t['count'], update)

    update()
    cv2.waitKey(0)
    cv2.destroyAllWindows()

