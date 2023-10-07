import requests
import os

def download_image(url, filename):
    response = requests.get(url, stream=True)
    response.raise_for_status()

    with open(filename, 'wb') as file:
        for chunk in response.iter_content(chunk_size=8192):
            file.write(chunk)

# 替换为你想要下载的图片的url
image_url = "http://192.168.8.1:8083/?action=snapshot"

# 获取桌面路径
desktop = os.path.join(os.path.expanduser("~"), "Desktop")

# 图像保存的路径和名称
image_path = os.path.join(desktop, "downloaded_image.jpg")

# 下载图像
download_image(image_url, image_path)