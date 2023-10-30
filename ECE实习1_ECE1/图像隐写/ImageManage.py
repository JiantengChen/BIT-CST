# ImageManage.py

import os

import numpy as np
from PIL import Image


def get_path():
    up_path = os.path.dirname(os.path.realpath(__file__))  # 获取图片存储位置的上级地址
    return up_path  # 返回该地址


def imgInput(trace):
    img = Image.open(trace, 'r')  # 读取图片
    return img


def imgAnalyse(img, img_item):
    img_array = np.array(img)  # 通过np.array将图像转换为数组
    img_item['height'] = img_array.shape[0]  # 获取图片像素行数
    img_item['width'] = img_array.shape[1]  # 获取图片像素列数
    w = img_item['width']  # 方便下文引用
    h = img_item['height']  # 方便下文引用
    img_load = img.load()  # 返回一个用于读取和修改像素的像素访问对象
    RGB = []  # 创建一个列表用于存储每个像素的RGB信息
    for i in range(0, h):
        for j in range(0, w):
            RGB.append(img_load[j, i])  # 遍历每个像素 存储RGB数值到列表
    RGB_Bin = []  # 用于存储RGB数值的二进制形式
    for i in RGB:
        for item in i:
            RGB_Bin.append(''.join(str(bin(item))).replace('0b', '').rjust(8, '0'))  # 将RGB转换为二进制，其中不足八位的在数字前面补0
            # 之所以是8位，是因为RGB值在0-255之间
    return RGB_Bin, img_item
