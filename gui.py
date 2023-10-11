import tkinter as tk
import os
import subprocess
from PIL import Image, ImageTk


class ImageGUI(tk.Tk):
    def __init__(nihao, sourceLeft, sourceRight):
        tk.Tk.__init__(nihao)
        nihao.title("Display")
        # 创建标签
        nihao.lLable = tk.Label(nihao, text="Examples")
        nihao.lLable.grid(row=0, column=0)

        nihao.RLable = tk.Label(nihao, text="Answer")
        nihao.RLable.grid(row=0, column=1)

        # 创建画布
        nihao.LCan = tk.Canvas(nihao, width=400, height=400)
        nihao.LCan.grid(row=1, column=0, padx=10, pady=10)

        nihao.RCan = tk.Canvas(nihao, width=400, height=400)
        nihao.RCan.grid(row=1, column=1, padx=10, pady=10)
        
        # 放入图片
        nihao.LImage = nihao.load_images_from_folder(sourceLeft)
        nihao.LIT = [ImageTk.PhotoImage(image) for image in nihao.LImage]

        nihao.RImage = nihao.load_images_from_folder(sourceRight)
        nihao.RIT = [ImageTk.PhotoImage(image) for image in nihao.RImage]

        nihao.LIdex = 0  # 左边第几个
        nihao.RIdex = 0  # 右边第几个

        nihao.emergeLeft()
        nihao.emergeRight()

        # 按钮
        nihao.lftButton = tk.Button(nihao, text="previous", command=nihao.displayPreImg)
        nihao.lftButton.grid(row=2, column=0, pady=10)

        nihao.rgtButton = tk.Button(nihao, text="next", command=nihao.displayNxtImg)
        nihao.rgtButton.grid(row=2, column=1, pady=10)



    def load_images_from_folder(nihao, folder):
        images = []
        for filename in os.listdir(folder):
            if filename.endswith(".jpg") or filename.endswith(".png"):
                imgPath = os.path.join(folder, filename)
                image = Image.open(imgPath)
                imgSize = image.resize((400, 400))
                images.append(imgSize)
        return images

    def displayPreImg(nihao):
        # 展示上张图片
        nihao.LIdex = (nihao.LIdex - 1) % len(nihao.LImage)
        nihao.emergeLeft()
        nihao.RIdex = (nihao.RIdex - 1) % len(nihao.RImage)
        nihao.emergeRight()

    def displayNxtImg(nihao):
        # 展示下张图片
        nihao.LIdex = (nihao.LIdex + 1) % len(nihao.LImage)
        nihao.emergeLeft()
        nihao.RIdex = (nihao.RIdex + 1) % len(nihao.RImage)
        nihao.emergeRight()

    def emergeLeft(nihao):
        nihao.LCan.delete("all")
        nihao.LCan.create_image(0, 0, anchor=tk.NW, image=nihao.LIT[nihao.LIdex])

    def emergeRight(nihao):
        nihao.RCan.delete("all")
        nihao.RCan.create_image(0, 0, anchor=tk.NW, image=nihao.RIT[nihao.RIdex])




# Your existing code

def run_gui():
    sourceLeft = "C:\\Users\\tbx12\\Desktop\\Code\\target"  # example路径
    sourceRight = "C:\\Users\\tbx12\\Desktop\\Code\\predict"  # answer路径
    app = ImageGUI(sourceLeft, sourceRight)
    app.mainloop()