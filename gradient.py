import cv2 as cv
import numpy as np
img = cv.imread('105180399.jpg')
cv.imshow('Profile image', img)
gray_img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('gray_img', gray_img)

#Laplacian mau but chi
lap = cv.Laplacian(gray_img, cv.CV_64F)
lap = np.uint8(np.absolute(lap))
cv.imshow('Laplacian', lap)

#Sobel
sobelx = cv.Sobel(gray_img, cv.CV_64F, 1, 0)
sobely = cv.Sobel(gray_img, cv.CV_64F, 0, 1)
cv.imshow('Sobel X', sobelx)
cv.imshow('Sobel Y', sobely)
cv.waitKey()