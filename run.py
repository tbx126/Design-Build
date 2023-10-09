import os
import serial
import subprocess
import requests
from PIL import Image
from ultralytics import YOLO

def download_image(url, filename):
    response = requests.get(url, stream=True)
    response.raise_for_status()

    with open(filename, 'wb') as file:
        for chunk in response.iter_content(chunk_size=8192):
            file.write(chunk)

def process_image(model, image_path, count):
    results = model(image_path)  # results list

    for r in results:
        im_array = r.plot()  # plot a BGR numpy array of predictions
        im = Image.fromarray(im_array[..., ::-1])  # RGB PIL image
        im.show()  # show image
        im.save(os.path.join(desktop, f'results_{count}.jpg'))  # save image

ser = serial.Serial('COM6')  # replace 'COM6' with your actual serial port name
image_url = "http://192.168.8.1:8083/?action=snapshot"
desktop = os.path.join(os.path.expanduser("~"), "Desktop")
image_path = os.path.join(desktop, "downloaded_image.jpg")
model = YOLO('C:\\Users\\tbx12\\Desktop\\train45\\weights\\best.pt')

counter = 1
while True:
    data = ser.readline().decode('utf-8').strip()  # read data from serial port and strip end of line
    if data == "1":
        download_image(image_url, image_path)
        process_image(model, image_path, counter)
        counter += 1