import os
import cv2
import numpy as np

# 定义目标尺寸
target_width = 116
target_height = 116

# 定义输入文件夹和输出文件夹的路径
input_folder = "src\\scripts\\source_directory"
output_folder = "src\\scripts\\destination_directory"


# 遍历输入文件夹中的所有文件
# 遍历输入文件夹中的所有文件
for filename in os.listdir(input_folder):
    # 构建输入文件的完整路径
    input_path = os.path.join(input_folder, filename)
    
    # 仅处理图片文件
    if not os.path.isfile(input_path) or not filename.lower().endswith((".png", ".jpg", ".jpeg")):
        continue
    
    # 读取图片
    image = cv2.imread(input_path, cv2.IMREAD_UNCHANGED)
    
    # 调整图片大小
    resized_image = cv2.resize(image[:, :, :3], (target_width, target_height))
    
    # 创建一个与调整后图像尺寸相同的透明背景图像
    alpha_channel = np.ones((target_height, target_width, 1), dtype=np.uint8) * 255
    
    # 如果原始图像有透明通道，则调整透明通道的大小并复制到调整后图像
    if image.shape[2] == 4:  # 假设透明通道在第三个通道
        alpha_channel_resized = cv2.resize(image[:, :, 3:4], (target_width, target_height), interpolation=cv2.INTER_NEAREST)
        alpha_channel = alpha_channel_resized
    
    # 在深度维度上堆叠调整后的图像和透明背景图像
    resized_image_with_alpha = np.dstack((resized_image, alpha_channel))
    
    # 构建输出文件的完整路径，并替换扩展名为 png
    output_path = os.path.join(output_folder, os.path.splitext(filename)[0] + ".png")
    
    # 保存调整大小后的图片为 PNG 格式
    cv2.imwrite(output_path, resized_image_with_alpha)

print("图片调整大小并保存完成。")