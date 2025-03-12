import cv2
from config import IMAGE_PATH


def display(title, image):
    cv2.namedWindow(title, cv2.WINDOW_NORMAL)
    cv2.imshow(title, image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


img = cv2.imread(IMAGE_PATH)
display('img', img)

color = (
    ( 90,  90,  90),
    (120, 255, 255),
)

img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
img_mask = cv2.inRange(img_hsv, color[0], color[1])
display('img', img_mask)

contours, _ = cv2.findContours(img_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

drawing = img.copy()
cv2.drawContours(drawing, contours, -1, (255, 255, 255), 1)
if contours:
    for i in range(len(contours)):
        cnt = contours[i]
        if cv2.contourArea(cnt) < 50:
            continue
        cv2.drawContours(drawing, contours, i, (0, 0, 255), 7)

display('drawing', drawing)