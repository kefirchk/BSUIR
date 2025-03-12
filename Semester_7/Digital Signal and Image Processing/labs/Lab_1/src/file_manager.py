import cv2


class FileManager:
    @staticmethod
    def load_image(image_path):
        image = cv2.imread(image_path, cv2.IMREAD_COLOR)
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        return image

    @staticmethod
    def save_image(image_to_save, output_path):
        # image_to_save = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        cv2.imwrite(output_path, image_to_save)
