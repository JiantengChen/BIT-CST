# LSB_encode.py
# 加密算法位于 LSB_encode.py 第25行

import numpy as np
from PIL import Image

import ImageManage


def getBin(trace):  # 得到要加密的文本的ASCII码的二进制表示
    f = open(trace, 'r', encoding='ASCII').read()  # 打开文件
    ls_ASCII = []
    for i in f:
        ls_ASCII.append(ord(i))  # 将文本以ASCII码形式存储
    ls = []
    ls_Bin = []
    for item in ls_ASCII:
        ls.append(bin(item))  # 将文本以二进制形式存储
    for item in ls:
        if len(item) <= 10:  # 之所以小于等于10，是因为二进制表示中0b开头
            ls_Bin.append(''.join(item).replace('0b', '').rjust(8, '0'))  # 对于长度不满8位，补齐8位数
    return ls_Bin  # 返回该列表


def lsb_encode(ls_Bin, RGB_Bin):
    global img_item, length  # 导入全局变量 其中length为需要更改的像素个数
    str_Bin = ''
    for item in ls_Bin:
        str_Bin += item  # 将以二进制形式存储的列表转换为字符串
    RGB_encode_Bin = []
    RGB_encode = []
    for i in range(length):
        str_1 = RGB_Bin[i][:-1]  # RGB二进制表示的前七位数字不变
        str_1 += str_Bin[i]  # 将RGB二进制表示的最后一位数字替换
        RGB_encode_Bin.append(str_1)  # 将更改之后的RGB二进制表示存储入列表
    for i in range(length, len(RGB_Bin)):
        RGB_encode_Bin.append(RGB_Bin[i])  # 将剩余的不需更改的像素的RGB值存入原本的RGB的二进制表示值
    for item in RGB_encode_Bin:
        RGB_encode.append(''.join(str(int(item, 2))).replace('0b', '').rjust(8, '0'))  # 对于不到8位的二进制数字，补齐八位
    RGB_encode = np.array(RGB_encode)  # 通过np.array方法生成数组
    RGB = RGB_encode.reshape((img_item['height'], img_item['width'], 3))  # 生成一个 像素高*像素宽*3 的高维数组
    img_encode = Image.fromarray(RGB.astype(np.uint8)).convert('RGB')  # 通过fromarray方法，将数组转换为图片
    img_encode.save(str(ImageManage.get_path()) + "\decode_image.png")  # 图片保存路径


# os库获取路径
trace_img = str(ImageManage.get_path()) + "\encode_image.png"  # 通过ImageManage.py中的get_path方法得到上级路径，并赋值文件路径
trace_txt = str(ImageManage.get_path()) + '\encode_text.txt'  # 通过ImageManage.py中的get_path方法得到上级路径，并赋值文件路径

img = ImageManage.imgInput(trace_img)  # 通过ImageManage.py的imgInput方法，读取图片
img.convert("RGB")  # 以RGB模式读取图片
img_item = {}  # 创建空字典，用于储存图片的像素宽高数
RGB_Bin, img_item = ImageManage.imgAnalyse(img, img_item)  # 通过ImageManage.py中的imgAnalyse方法分析图片，得到存储RGB信息的数组
ls_Bin = getBin(trace_txt)  # 得到要加密的文本的ASCII码的二进制表示

# 循环次数
length = 8 * len(ls_Bin)
length_output = len(ls_Bin)  # 解密时的读取循环次数

# 执行加密函数
lsb_encode(ls_Bin, RGB_Bin)
