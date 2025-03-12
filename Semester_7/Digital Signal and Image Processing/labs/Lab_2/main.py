import cv2
import numpy as np
from sklearn.cluster import KMeans

from config import IMAGE_PATH, TRACKBARS, RAINBOW_PATH, WINDOW_HEIGHT, WINDOW_WIDTH, IMAGE_WIDTH, IMAGE_HEIGHT


def contour_area(cnt):
    # Количество точек в контуре
    n = len(cnt)

    # Инициализация площади
    area = 0.0

    # Применяем формулу шнуровки (Gauss's area formula)
    for i in range(n):
        x1, y1 = cnt[i][0]
        x2, y2 = cnt[(i + 1) % n][0]
        area += x1 * y2 - x2 * y1

    # Возвращаем абсолютное значение площади, так как она может быть отрицательной
    return abs(area) / 2.0


def arc_length(cnt, closed=True):
    # Инициализация длины периметра
    perimeter = 0.0

    # Количество точек в контуре
    n = len(cnt)

    for i in range(n):
        # Получаем текущую и следующую точки
        p1 = cnt[i][0]
        p2 = cnt[(i + 1) % n][0] if closed else cnt[i + 1][0] if i + 1 < n else p1

        # Вычисляем расстояние между текущей и следующей точками
        distance = np.linalg.norm(p2 - p1)

        # Добавляем к периметру
        perimeter += distance

    return perimeter


def good_features_to_track(mask, max_corners, quality_level, min_distance):
    # Преобразуем маску в формат float32
    mask = np.float32(mask)

    # Находим градиенты по X и Y
    dx = cv2.Sobel(mask, cv2.CV_64F, 1, 0, ksize=3)
    dy = cv2.Sobel(mask, cv2.CV_64F, 0, 1, ksize=3)

    # Вычисляем матрицу градиентов
    Ix2 = dx * dx
    Iy2 = dy * dy
    Ixy = dx * dy

    # Параметры для определения углов
    height, width = mask.shape
    corners = []

    # Используем np.zeros для хранения значений матриц
    M = np.zeros((2, 2), dtype=np.float64)

    # Вычисляем значения по всем пикселям изображения
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            # Соберем значения в окне 3x3
            window_Ix2 = Ix2[y - 1:y + 2, x - 1:x + 2].flatten()
            window_Iy2 = Iy2[y - 1:y + 2, x - 1:x + 2].flatten()
            window_Ixy = Ixy[y - 1:y + 2, x - 1:x + 2].flatten()

            # Соберем матрицу
            M[0, 0] = np.sum(window_Ix2)
            M[0, 1] = np.sum(window_Ixy)
            M[1, 0] = M[0, 1]  # M[1, 0] = M[0, 1]
            M[1, 1] = np.sum(window_Iy2)

            # Находим собственные значения
            eigenvalues = np.linalg.eigvals(M)

            # Проверяем условия качества
            if min(eigenvalues) > quality_level:
                corners.append((x, y))

    # Применяем min_distance для фильтрации углов
    filtered_corners = []
    corners = np.array(corners)

    for corner in corners:
        if all(np.linalg.norm(np.array(corner) - np.array(c)) >= min_distance for c in filtered_corners):
            filtered_corners.append(corner)

    # Ограничиваем количество углов до max_corners
    filtered_corners = filtered_corners[:max_corners]

    return np.array(filtered_corners, dtype=np.float32)


def count_corners(mask, max_corners=100, quality_level=0.01, min_distance=10):
    # своя реализцая оооooooooooooooooooоочень медленная
    # corners = good_features_to_track(mask, max_corners, quality_level, min_distance)
    corners = cv2.goodFeaturesToTrack(mask, maxCorners=max_corners, qualityLevel=quality_level, minDistance=min_distance)

    if corners is not None:
        return len(corners)
    return 0


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


def extract_features(cnt, img_mask):
    features = []

    area = contour_area(cnt)  # cv2.contourArea(cnt)
    # features.append(area)

    perimeter = arc_length(cnt, True)  # cv2.arcLength(cnt, True)
    # features.append(perimeter)

    aspect_ratio = area / (perimeter ** 2)
    features.append(aspect_ratio)

    corners_count = count_corners(img_mask)
    features.append(corners_count)

    angles = calculate_angles(cnt)
    mean_angle = np.mean(angles) if angles else 0
    features.append(mean_angle)

    return features


def process_img(img, color):
    img_mask = cv2.inRange(cv2.cvtColor(img, cv2.COLOR_BGR2HSV), color[0], color[1])
    img = cv2.bitwise_and(img, img, mask=img_mask)

    contours, _ = cv2.findContours(img_mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    drawing = img.copy()

    features = []
    big_contours = []

    if contours:
        for i, cnt in enumerate(contours):
            if cv2.contourArea(cnt) < 1000:
                continue
            cv2.drawContours(drawing, contours, i, (255, 255, 255), 3)

            features.append(extract_features(cnt, img_mask))
            big_contours.append(cnt)

        features = np.array(features)

        k = 3
        if len(features) >= k:
            kmeans = KMeans(n_clusters=k, random_state=0).fit(features)
            labels = kmeans.labels_
            colors = [
                (255, 0, 0),  # Blue
                (0, 255, 0),  # Green
                (0, 0, 255)   # Red
            ]

            for i, contour in enumerate(big_contours):
                cv2.drawContours(drawing, [contour], -1, colors[labels[i]], -1)

    return img_mask, drawing


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
    rainbow_mask, rainbow_mixed = process_img(rainbow, color)

    img_mask_resized = cv2.resize(cv2.cvtColor(img_mask, cv2.COLOR_GRAY2BGR), (IMAGE_WIDTH, IMAGE_HEIGHT))
    img_mixed_resized = cv2.resize(img_mixed, (IMAGE_WIDTH, IMAGE_HEIGHT))
    rainbow_mask_resized = cv2.resize(cv2.cvtColor(rainbow_mask, cv2.COLOR_GRAY2BGR), (IMAGE_WIDTH, IMAGE_HEIGHT))
    rainbow_mixed_resized = cv2.resize(rainbow_mixed, (IMAGE_WIDTH, IMAGE_HEIGHT))

    mask_combined = cv2.hconcat([img_mask_resized, rainbow_mask_resized])
    mixed_combined = cv2.hconcat([img_mixed_resized, rainbow_mixed_resized])

    combined_result = cv2.vconcat([mask_combined, mixed_combined])
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
