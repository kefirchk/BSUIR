import cv2
import numpy as np
from matplotlib import pyplot as plt
from typing import Tuple


class Grid:
    def __init__(
            self,
            window_title: str,
            description: str,
            figsize: Tuple[float, float],
            nrows,
            ncols
    ):
        self.figure = plt.figure(window_title, figsize=figsize)
        self.figure.suptitle(description)
        self.axs = self.figure.subplots(ncols=ncols, nrows=nrows)

    def display_brightness_histogram(self, x: int, y: int, title: str, image):
        self.axs[x, y].hist(image.ravel(), bins=256, range=[0, 256])
        self.axs[x, y].set_title(title)

    def display_image(self, x: int, y: int, title: str, image: np.ndarray, cmap: str = None):
        self.axs[x, y].imshow(image, cmap=cmap)
        self.axs[x, y].set_title(title)
        self.axs[x, y].axis('off')

    @staticmethod
    def show():
        plt.tight_layout()
        plt.show()
