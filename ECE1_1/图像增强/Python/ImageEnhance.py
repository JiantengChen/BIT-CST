# ImageEnhance.py
# 双线性插值 位于ImageEnhance.py文件 第21行、第39行
# 最邻近差值 位于ImageEnhance.py文件 第56行、第86行
# 程序中选择具体图像增强方法的选择部分 位于ImageEnhance.py文件 第138行

import cv2
import numpy as np
from scipy import ndimage

print("原始图像的路径是: ", end="")  # 文字解释说明
import ImageAnalysis

algorithm = eval(input("请选择你需要的算法\n1.最邻近插值\n2.双线性插值\n请输入1或2并按下回车\n"))  # 文字解释说明
solution = eval(input("请选择你需要对图片进行放大(上采样)或缩小(下采样)\n1.放大(上采样)\n2.缩小(下采样)\n请输入1或2并按下回车\n"))  # 文字解释说明
multiple = eval(input("请输入需要放大/缩小的倍数(输入一个正整数并按下回车)\n"))  # 文字解释说明
img = ImageAnalysis.img_open()  # 创建图像类型的变量
img_item = {}  # 创建用于存储原始图像数据的空字典
img_array = ImageAnalysis.img_array(img, img_item)  # 创建用于存储原始图像数据的高维数组


def img_nearest_upsampling():
    """通过最邻近插值对图片进行上采样处理"""
    global img, img_item, img_array, multiple  # 通过全局变量导入原始图像相关信息以及操作倍数
    target_height = multiple * img_item['height'] - multiple + 1  # 目标图像的像素行数
    target_width = multiple * img_item['width'] - multiple + 1  # 目标图像的像素列数
    shape = (target_height, target_width, 3)  # 用于创建目标图像数组的元组变量
    img_n_u = np.zeros(shape, int)  # 创建目标图像的高维数组

    for count_line in range(len(img_n_u)):
        count_l1 = round(count_line / multiple)  # 本变量代表用于插值的原始图像的像素点位置
        for count_row in range(len(img_n_u[0])):
            count_r1 = round(count_row / multiple)  # 本变量代表用于插值的原始图像的像素点位置
            img_n_u[count_line][count_row] = img_array[count_l1][count_r1]  # 插值
    img_n_u = np.array(img_n_u, dtype=np.uint8)  # 转换为uin8类型，后续用cv2.imshow显示
    cv2.imshow("img_nearest_upsampling", img_n_u)
    cv2.waitKey(0)


def img_nearest_downsampling():
    """通过最邻近插值对图片进行下采样处理"""
    global img, img_item, img_array, multiple  # 通过全局变量导入原始图像相关信息以及操作倍数
    if img_item['height'] % multiple == 0:
        shape = (img_item['height'] // multiple, img_item['width'] // multiple, 3)  # 用于创建像素行数能整除倍数情况下目标图像数组的元组变量
    else:
        shape = ((img_item['height'] + multiple - 1) / multiple, (img_item['width'] + multiple - 1) / multiple, 3)  # 用于创建像素行数不能整除倍数目标图像数组的元组变量

    img_n_d = np.zeros(shape, int)  # 创建目标图像的高维数组
    for count_line in range(len(img_n_d)):
        for count_row in range(len(img_n_d[0])):
            img_n_d[count_line][count_row] = img_array[multiple * count_line][multiple * count_row]  # 插值
    img_n_d = np.array(img_n_d, dtype=np.uint8)  # 转换为uin8类型，后续用cv2.imshow显示
    cv2.imshow("img_nearest_downsampling", img_n_d)
    cv2.waitKey(0)


def img_bilinear_upsampling():
    """通过双线性插值对图片进行上采样处理"""
    global img, img_item, img_array, multiple  # 通过全局变量导入原始图像相关信息以及操作倍数
    target_height = multiple * img_item['height'] - multiple + 1  # 目标图像的像素行数
    target_width = multiple * img_item['width'] - multiple + 1  # 目标图像的像素列数
    shape = (target_height, target_width, 3)  # 用于创建目标图像数组的元组变量

    ratio_width, ratio_height = img_item['width'] / target_width, img_item['height'] / target_height  # 比例，即为对齐几何中心过程中的w0/w
    img_b_d = np.zeros(shape, int)  # 创建目标图像的高维数组

    for i in range(3):  # 循环三次分别对RGB进行赋值
        for count_line in range(target_height):
            for count_row in range(target_width):
                x = (count_row + 0.5) * (ratio_width - 1 / img_item['width']) - 0.5  # 坐标变换得到的点x坐标
                y = (count_line + 0.5) * (ratio_height - 1 / img_item['height']) - 0.5  # 坐标变换得到的点y坐标
                # 以下分别为坐标变换得到的点上下左右最近的四个已知像素值的点坐标
                x_left = int(np.floor(x))
                x_right = min(x_left + 1, img_item['width'] - 1)  #
                y_down = int(np.floor(y))
                y_up = min(y_down + 1, img_item['height'] - 1)
                # 以下为代入公式计算，E代表水平方向上第一行的插值，G代表水平方向上第二行的插值，点的表示与项目说明中表示一致，计算结果为E、G两点的RGB值
                x_E = (x_right - x) * img_array[y_up, x_left, i] + (x - x_left) * img_array[y_up, x_right, i]
                x_G = (x_right - x) * img_array[y_down, x_left, i] + (x - x_left) * img_array[y_down, x_right, i]
                img_b_d[count_line, count_row, i] = int((y_up - y) * x_E + (y - y_down) * x_G)  # 插值

    img_b_d = np.array(img_b_d, dtype=np.uint8)  # 转换为uin8类型，后续用cv2.imshow显示
    cv2.imshow("img_bilinear_upsampling", img_b_d)
    cv2.waitKey(0)


def img_bilinear_downsampling():
    """通过双线性插值对图片进行下采样处理"""
    global img, img_item, img_array, multiple  # 通过全局变量导入原始图像相关信息以及操作倍数

    if img_item['height'] % multiple == 0:  # 用于创建像素行数能整除倍数情况下目标图像数组的元组变量
        target_height = img_item['height'] // multiple
        target_width = img_item['width'] // multiple
        shape = (target_height, target_width, 3)
    else:  # 用于创建像素行数不能整除倍数目标图像数组的元组变量
        target_height = (img_item['height'] + multiple - 1) / multiple
        target_width = (img_item['width'] + multiple - 1) / multiple
        shape = (target_height, target_width, 3)

    ratio_width, ratio_height = img_item['width'] / target_width, img_item['height'] / target_height  # 比例，即为对齐几何中心过程中的w0/w
    img_b_u = np.zeros(shape, int)  # 创建目标图像的高维数组

    for i in range(3):  # 循环三次分别对RGB进行赋值
        for count_line in range(target_height):
            for count_row in range(target_width):
                x = (count_row + 0.5) * ratio_width - 0.5  # 坐标变换得到的点x坐标
                y = (count_line + 0.5) * ratio_height - 0.5  # 坐标变换得到的点y坐标
                # 以下分别为坐标变换得到的点上下左右最近的四个已知像素值的点坐标
                x_left = int(np.floor(x))
                x_right = min(x_left + 1, img_item['width'] - 1)
                y_down = int(np.floor(y))
                y_up = min(y_down + 1, img_item['height'] - 1)
                # 以下为代入公式计算，E代表水平方向上第一行的插值，G代表水平方向上第二行的插值，点的表示与项目说明中表示一致，计算结果为E、G两点的RGB值
                x_E = (x_right - x) * img_array[y_up, x_left, i] + (x - x_left) * img_array[y_up, x_right, i]
                x_G = (x_right - x) * img_array[y_down, x_left, i] + (x - x_left) * img_array[y_down, x_right, i]
                img_b_u[count_line, count_row, i] = int((y_up - y) * x_E + (y - y_down) * x_G)  # 插值

    img_b_u = np.array(img_b_u, dtype=np.uint8)  # 转换为uin8类型，后续用cv2.imshow显示
    cv2.imshow("img_bilinear_upsampling", img_b_u)
    cv2.waitKey(0)


def nearest():
    global img_item, solution, multiple
    if solution == 1:
        img_nearest_upsampling()
    elif solution == 2:
        img_nearest_downsampling()


def bilinear():
    global img_item, solution, multiple
    if solution == 1:
        img_bilinear_upsampling()
    elif solution == 2:
        img_bilinear_downsampling()


if algorithm == 1:
    nearest()
elif algorithm == 2:
    bilinear()
