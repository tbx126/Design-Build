import tkinter as tk
import os
from PIL import Image, ImageTk


class ImageGUI(tk.Tk):
    def __init__(self, sourceLeft, sourceRight):
        tk.Tk.__init__(self)
        self.title("Display")

        # Create labels
        self.lLable = tk.Label(self, text="Examples")
        self.lLable.grid(row=0, column=0)

        self.RLable = tk.Label(self, text="Answer")
        self.RLable.grid(row=0, column=1)

        # Create canvases
        self.LCan = tk.Canvas(self, width=400, height=400)
        self.LCan.grid(row=1, column=0, padx=10, pady=10)

        self.RCan = tk.Canvas(self, width=400, height=400)
        self.RCan.grid(row=1, column=1, padx=10, pady=10)

        # Load images
        self.LImage = self.load_images_from_folder(sourceLeft)
        self.LIT = [ImageTk.PhotoImage(image) for image in self.LImage]

        self.RImage = self.load_images_from_folder(sourceRight)
        self.RIT = [ImageTk.PhotoImage(image) for image in self.RImage]

        self.LIdex = 0  # Index for left side
        self.RIdex = 0  # Index for right side

        self.emergeLeft()
        self.emergeRight()

        # Buttons
        self.lftButton = tk.Button(self, text="previous", command=self.displayPreImg)
        self.lftButton.grid(row=2, column=0, pady=10)

        self.rgtButton = tk.Button(self, text="next", command=self.displayNxtImg)
        self.rgtButton.grid(row=2, column=1, pady=10)

    def load_images_from_folder(self, folder):
        images = []
        for filename in os.listdir(folder):
            if filename.endswith(".jpg") or filename.endswith(".png"):
                imgPath = os.path.join(folder, filename)
                image = Image.open(imgPath)
                imgSize = image.resize((400, 400))
                images.append(imgSize)
        return images

    def displayPreImg(self):
        # Display previous image
        self.LIdex = (self.LIdex - 1) % len(self.LImage)
        self.emergeLeft()
        self.RIdex = (self.RIdex - 1) % len(self.RImage)
        self.emergeRight()

    def displayNxtImg(self):
        # Display next image
        self.LIdex = (self.LIdex + 1) % len(self.LImage)
        self.emergeLeft()
        self.RIdex = (self.RIdex + 1) % len(self.RImage)
        self.emergeRight()

    def emergeLeft(self):
        self.LCan.delete("all")
        self.LCan.create_image(0, 0, anchor=tk.NW, image=self.LIT[self.LIdex])

    def emergeRight(self):
        self.RCan.delete("all")
        self.RCan.create_image(0, 0, anchor=tk.NW, image=self.RIT[self.RIdex])


def run_gui():
    sourceLeft = "C:\\Users\\tbx12\\Desktop\\Code\\target"  # path for examples
    sourceRight = "C:\\Users\\tbx12\\Desktop\\Code\\predict"  # path for answers
    app = ImageGUI(sourceLeft, sourceRight)
    app.mainloop()