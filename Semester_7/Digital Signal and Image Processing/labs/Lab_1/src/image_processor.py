import cv2
import numpy as np


class ImageProcessor:
    @classmethod
    def display(cls, title, image):
        cv2.namedWindow(title, cv2.WINDOW_NORMAL)
        cv2.imshow(title, image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    @classmethod
    def apply_filter(cls, image, kernel):
        height, width = image.shape[:2]
        filtered_image = np.zeros((height, width), dtype=np.float32)

        ksize = kernel.shape[0]
        pad = ksize // 2

        for y in range(pad, height - pad):
            for x in range(pad, width - pad):
                region = image[y - pad:y + pad + 1, x - pad:x + pad + 1]
                filtered_value = np.sum(region * kernel)
                filtered_image[y, x] = filtered_value

        return filtered_image

    @classmethod
    def sobel_operator(cls, image):
        # Если изображение RGB, преобразуем его в градации серого
        if len(image.shape) == 3 and image.shape[2] == 3:
            grayscale_image = cls.rgb_to_grayscale(image)
        else:
            grayscale_image = image

        # Собель по X и Y
        sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], dtype=np.float32)
        sobel_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]], dtype=np.float32)

        grad_x = cls.apply_filter(grayscale_image, sobel_x)
        grad_y = cls.apply_filter(grayscale_image, sobel_y)

        gradient_magnitude = np.sqrt(grad_x ** 2 + grad_y ** 2)
        gradient_magnitude = np.clip(gradient_magnitude, 0, 255)
        gradient_magnitude = gradient_magnitude.astype(np.uint8)

        return gradient_magnitude

    @classmethod
    def rgb_to_grayscale(cls, image):
        image = np.copy(image)
        height, width = image.shape[:2]
        grayscale_image = np.zeros((height, width), dtype=np.uint8)

        for y in range(height):
            for x in range(width):
                r, g, b = image[y, x]
                gray_value = int(0.30 * r + 0.59 * g + 0.11 * b)
                grayscale_image[y, x] = gray_value

        return grayscale_image

    @classmethod
    def extract_objects(cls, image: np.ndarray):
        # Шаг 1: Извлечение каналов R, G, B
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        b_channel, g_channel, r_channel = cv2.split(image)

        mask = (r_channel < 40) & (g_channel >= 0) & (b_channel >= 0)
        mask = mask.astype(np.uint8) * 255

        output_image = np.zeros_like(image)  # Создание черного фона
        output_image[mask > 0] = image[mask > 0]  # Сохранение объектов

        return output_image

    @classmethod
    def delete_backgroud(cls, rgb_image):
        # Создаем копию исходного изображения
        result_image = np.copy(rgb_image)

        # Определяем диапазоны для синего цвета (пороговые значения для каждого канала)
        #                        R    G    B
        lower_blue  = np.array([  0,   0, 180])  # Нижняя граница для синего цвета
        upper_blue  = np.array([255, 255, 255])  # Верхняя граница для синего цвета
        lower_green = np.array([  0, 180,   0])
        upper_green = np.array([255, 255, 255])

        # Проходим по каждому пикселю изображения
        height, width = rgb_image.shape[:2]
        for y in range(height):
            for x in range(width):
                # Извлекаем значение пикселя (RGB)
                pixel = rgb_image[y, x]

                # Проверяем, попадает ли пиксель в диапазон синего
                if (lower_blue[0] <= pixel[0] <= upper_blue[0] and
                    lower_blue[1] <= pixel[1] <= upper_blue[1] and
                    lower_blue[2] <= pixel[2] <= upper_blue[2]) \
                    or \
                    (lower_green[0] <= pixel[0] <= upper_green[0] and
                     lower_green[1] <= pixel[1] <= upper_green[1] and
                     lower_green[2] <= pixel[2] <= upper_green[2]):
                    pass
                else:
                    # Если пиксель не синий и не зеленый, закрашиваем его в черный
                    result_image[y, x] = [0, 0, 0]

        return result_image

