import cv2
import imutils
image = cv2.imread("105180399.jpg")
""""
# Read image , gray image
image = cv2.imread("105180399.jpg", cv2.IMREAD_GRAYSCALE)
# Show image
cv2.imshow("testImage",image)
# Stop screen to watch
cv2.waitKey()
# Close all windows
cv2.destroyAllWindows()
# Covert image to gray image
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
cv2.imshow("Gray image",gray_image)
cv2.waitKey()
cv2.destroyAllWindows()
"""

"""
# Resize image

image_rs = cv2.resize(image,dsize=None,fx = 0.5, fy = 0.5)
cv2.imshow("Resized image", image_rs)
cv2.waitKey()
cv2.destroyAllWindows()
"""
"""
# Rotate image
image_rotate = imutils.rotate(image,90)
cv2.imshow("Resized image", image_rotate)
cv2.waitKey()
cv2.destroyAllWindows()
"""
