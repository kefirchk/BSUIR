import sys

import cv2
import numpy as np

from config import IMAGE_PATH, titles
from src.file_manager import FileManager
from src.image_processor import ImageProcessor
from src.grid import Grid


if __name__ == "__main__":
    fm = FileManager()
    grid = Grid(
        window_title='Лабораторная работа №1',
        description='Лабораторная работа №1\n'
                    'Гистограмма и гистограммная обработка.\n'
                    'Поэлементная обработка изображений. Фильтрация изображений',
        figsize=(12, 8),
        nrows=2,
        ncols=3
    )

    rgb_original_image = fm.load_image(IMAGE_PATH)
    # image_with_extracted_objs = ImageProcessor.extract_objects(rgb_original_image)  # Обработка изображения
    sobel_image = ImageProcessor.sobel_operator(rgb_original_image)
    # image_without_bg = ImageProcessor.delete_backgroud(rgb_original_image)

    # ImageProcessor.display("ext", image_with_extracted_objs)
    ImageProcessor.display("sobel", sobel_image)
    # image_without_bg = cv2.cvtColor(image_without_bg, cv2.COLOR_RGB2BGR)
    # ImageProcessor.display("bg", image_without_bg)


    sys.exit(0)

    processed_image = ImageProcessor.delete_backgroud(rgb_original_image)

    images = [
        rgb_original_image,
        sobel_image,
        processed_image
    ]

    for y in range(0, 3):
        grid.display_image(0, y, titles[y], images[y], cmap="gray")

    for y in range(0, 3):
        grid.display_brightness_histogram(1, y, titles[y + 3], images[y])

    grid.show()

