# LSB_decode.py
# 解密算法位于 LSB_decode.py 第7行

import ImageManage
import LSB_encode


def lsb_decode(RGB_Bin):
    global img_item  # 导入全局变量
    str_Bin = ''
    for item in RGB_Bin:
        str_Bin += item[-1]  # 将需要解码的图片的RGB的二进制表示最后一位增加到字符串中
    ls_Bin = []
    for i in range(len(str_Bin) // 8):
        ls_Bin.append(str_Bin[8 * i:8 * i + 8])  # 将上述得到的字符串按照8(RGB为0-255位)切片，存储到列表中
    ls_chr = []
    for item in ls_Bin:
        ls_chr.append(chr(int(item, 2)))  # 将列表中的二进制转换为具体的ASCII码后转换为字符，并存储到列表中
    str_chr = ''.join(ls_chr)  # 将存储字符的列表转换成字符串
    f = open(ImageManage.get_path() + '\decode_text.txt', 'w')  # 以覆盖写模式创建一个文件
    f.write(str_chr[:LSB_encode.length_output])  # 将文件的length_output位(即加密时更改的像素RGB二进制值个数)写入到文件中


# os库获取路径
trace_img = str(ImageManage.get_path()) + "\decode_image.png"  # 通过ImageManage.py中的get_path方法得到上级路径，并赋值文件路径
trace_txt = str(ImageManage.get_path()) + '\decode_text.txt'  # 通过ImageManage.py中的get_path方法得到上级路径，并赋值文件路径

img = ImageManage.imgInput(trace_img)  # 通过ImageManage.py的imgInput方法，读取图片
img.convert("RGB")  # 以RGB模式读取图片
img_item = {}  # 创建空字典，用于储存图片的像素宽高数
RGB_Bin, img_item = ImageManage.imgAnalyse(img, img_item)  # 通过ImageManage.py中的imgAnalyse方法分析图片，得到存储RGB信息的数组

# 执行解密函数
lsb_decode(RGB_Bin)
