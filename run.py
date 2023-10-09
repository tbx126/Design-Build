import os
import serial
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
        im.save(os.path.join(predict_dir, f'predict_{count}.jpg'))  # save image

ser = serial.Serial('COM6')  # replace 'COM6' with your actual serial port name
image_url = "http://192.168.8.1:8083/?action=snapshot"
target_dir = 'C:\\Users\\tbx12\\Desktop\\Code\\target'
predict_dir = 'C:\\Users\\tbx12\\Desktop\\Cdoe\\predict'
model = YOLO('C:\\Users\\tbx12\\Desktop\\Code\\train45\\weights\\best.pt')

counter = 1
while True:
    data = ser.readline().decode('utf-8').strip()  # read data from serial port and strip end of line
    if data == "1":
        image_path = os.path.join(target_dir, f'target_{counter}.jpg')
        download_image(image_url, image_path)
        process_image(model, image_path, counter)
        counter += 1