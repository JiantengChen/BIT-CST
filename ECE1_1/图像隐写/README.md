# 基于python的图像隐写项目

> **特别注意，本项目中解密图片导出字符的位数在由LSB_encode.py导入，如需解密其他通过LSB隐写加密的图片，需要重新设定导出时的字符串切片范围(LSB_decode.py的第21行)！**

## 项目介绍

> - LSB 隐写术是一种图像隐写术技术，其中通过将每个像素的最低有效位替换为要隐藏的消息位来将消息隐藏在图像中。
>- 可以使用将消息转换为十进制值，然后再转换为二进制。然后，我们逐个迭代像素值，将它们转换为二进制后，我们将每个最低有效位替换为序列中的消息位。
>- 要解码编码图像，我们只需反转该过程，收集并存储每个像素的最后一位，然后将它们分成 8 组，并将其转换回 ASCII 字符以获取隐藏消息

## 文件介绍

### ImageManage.py

> - 引入了第三方库numpy与PIL库中的类image，将图像解码为各个像素点，再将每个像素点转为二进制编码。

### encode_image.png

> - 项目提供图片，用于加密文本。

### encode_text.txt

> - 项目提供文本信息，用于加密至图片decode_image.png中。

### decode_image.png

> - 通过LSB_encode.py加密处理产生的图像。

### decode_text.txt

> - 通过LSB_decode.py解密处理decode_image.png得到的文本信息。

### LSB_encode.py

> - 本项目中加密程序，对encode_image.png和encode_text.txt按照项目要求进行加密

### LSB_decode.py

> - 本项目中解密程序，对decode_image.png按照项目要求进行解密

### README.md

> - 项目说明文件

### requirement.txt

> - 项目依赖包及其版本号

## 项目文件功能介绍

### ImageManage.py

> - get_path用于获得图片保存目录
>- imgInput通过PIL库中类Image创建对象img
>- imgAnalyse通过numpy将img的每一像素以RGB形式表示并转换为二进制创建为数组RGB_Bin，同时将不满8位的RGB编码自动补齐八位

### LSB_encode.py

> - getBin将需要加密的文本转换为ASCII码后转换为二进制，并返回一个列表ls_Bin
>- lsb_encode即为加密算法，通过遍历ls_Bin对RGB_Bin列表的最后一位进行替换，剩余部分用RGB_Bin自身补齐。返回一个新列表RGB_encode_Bin后，通过numpy对列表进行处理，变为一个
   图片高像素个数\*图片宽像素个数\*3 的数组,再通过PIL库中类Image在同一目录导出为图片decode_image.png

### LSB_decode.py

>- lsb_decode即为解密算法，遍历img中以二进制表示RGB的每一像素中的值的最后一位并导入到新列表ls_Bin后转换位字符串str_chr，而后将字符串的前12位，即本次加密位数以覆盖写模式导出为文件decode_text.txt。
>- 需要注意的是，导出字符的位数在本文件中由LSB_encode.py导入，如需解密其他通过LSB隐写加密的图片，需要重新设定导出时的字符串切片范围！