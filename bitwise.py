import cv2 as cv
from cv2 import rectangle
import numpy as np
import matplotlib.pyplot as plt

blank = np.zeros((400,400), dtype='uint8')
rectangle = cv.rectangle(blank.copy(), (30,30), (370,370), 255, -1)
circle = cv.circle(blank.copy(),(200,200), 200 , 255, -1)

# bitwise AND
bitwise_and = cv.bitwise_and(circle, rectangle)
cv.imshow('bitwise AND', bitwise_and)

# bitwise OR
bitwise_or = cv.bitwise_or(circle, rectangle)
cv.imshow('bitwise OR', bitwise_or)

# bitwise XOR
bitwise_xor = cv.bitwise_xor(circle, rectangle)
cv.imshow('bitwise XOR', bitwise_xor)

# bitwise NOT
bitwise_not = cv.bitwise_not(circle)
cv.imshow('bitwise NOT', bitwise_not)
cv.waitKey()
