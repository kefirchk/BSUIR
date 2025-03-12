import cv2
from config import IMAGE_PATH


def process_img(img, color):
    hsv_image = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)  # Hue, Saturation, Value — тон, насыщенность, значение (яркость)

    # Создаем маску по диапазону цветов
    img_mask = cv2.inRange(hsv_image, color[0], color[1])
    img_mixed = cv2.bitwise_and(img, img, mask=img_mask)

    return img_mask, img_mixed


def resize_to_fit(img, max_width, max_height):
    height, width = img.shape[:2]

    scale = min(max_width / width, max_height / height)
    new_width = int(width * scale)
    new_height = int(height * scale)

    return cv2.resize(img, (new_width, new_height))


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

    # Приведение масок к 3 каналам для объединения
    img_mask_3ch = cv2.cvtColor(img_mask, cv2.COLOR_GRAY2BGR)
    rainbow_mask_3ch = cv2.cvtColor(rainbow_mask, cv2.COLOR_GRAY2BGR)

    max_width = 400
    max_height = 300

    img_mask_3ch = resize_to_fit(img_mask_3ch, max_width, max_height)
    rainbow_mask_3ch = resize_to_fit(rainbow_mask_3ch, max_width, max_height)
    img_mixed = resize_to_fit(img_mixed, max_width, max_height)
    rainbow_mixed = resize_to_fit(rainbow_mixed, max_width, max_height)

    mask_combined = cv2.hconcat([img_mask_3ch, rainbow_mask_3ch])
    mixed_combined = cv2.hconcat([img_mixed, rainbow_mixed])
    combined_result = cv2.vconcat([mask_combined, mixed_combined])

    cv2.imshow('Result', combined_result)


if __name__ == '__main__':
    img = cv2.imread(IMAGE_PATH)
    rainbow = cv2.imread('figures/rainbow.png')
    window_width = 800
    window_height = 600

    img = cv2.resize(img, (window_width, window_height))
    rainbow = cv2.resize(rainbow, (window_width, window_height))

    # Создаем окно для трекбаров
    cv2.namedWindow('Controls')
    cv2.createTrackbar('h_min', 'Controls', 0, 180, update)
    cv2.createTrackbar('s_min', 'Controls', 0, 255, update)
    cv2.createTrackbar('v_min', 'Controls', 0, 255, update)
    cv2.createTrackbar('h_max', 'Controls', 180, 180, update)
    cv2.createTrackbar('s_max', 'Controls', 255, 255, update)
    cv2.createTrackbar('v_max', 'Controls', 255, 255, update)
    update()

    cv2.waitKey(0)
    cv2.destroyAllWindows()
