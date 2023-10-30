# ImageAnalysis.py

import cv2
import numpy as np

import getPath


def img_open():
    path = getPath.path
    # img = cv2.imread(path)
    img = cv2.imdecode(np.fromfile(path,dtype=np.uint8),1)
    return img


def img_array(img, img_item):
    img_array = np.array(img)
    img_item['height'] = img_array.shape[0]
    img_item['width'] = img_array.shape[1]
    return img_array

