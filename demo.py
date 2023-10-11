
import subprocess
import json
import sys
import os
import serial
import mysql.connector
import requests
import gui
from PIL import Image
from ultralytics import YOLO

def download_image(url, filename):
    response = requests.get(url, stream=True)
    response.raise_for_status()

    with open(filename, 'wb') as file:
        for chunk in response.iter_content(chunk_size=8192):
            file.write(chunk)

ser = serial.Serial('COM6')  # replace 'COM6' with your actual serial port name
# 检查保存整数的文件是否存在
print("1")
if not os.path.exists("C:\\Users\\tbx12\\Desktop\\Code\\number.txt"):
    with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "w") as file:
        file.write("0")
print("2")
# 读取文件中的整数值
with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "r") as file:
    number = int(file.read())
print("3")
while True:  # replace with your own condition for when to stop
    data = ser.readline().decode('utf-8').strip()
    print("4")
    try:
        # 尝试解析JSON数据
        sensor_data = json.loads(data)
    except json.JSONDecodeError:
        continue  # skip if data is not valid JSON

        # 创建到MySQL服务器的连接
    cnx = mysql.connector.connect(user='root', password='123456',
                                      host='localhost',
                                      database='javawebdb')
    print("5")
    # 创建一个新的cursor对象
    cursor = cnx.cursor()

    # 插入数据的SQL语句
    add_data = ("INSERT INTO robotinfo "
                "(robotID, time, path, result) "
                "VALUES (%s, %s, %s, %s)")

    print("6")
    target_dir = 'C:\\Users\\tbx12\\Desktop\\Code\\target'
    predict_dir = 'C:\\Users\\tbx12\\Desktop\\Code\\predict'
    image_path = os.path.join(target_dir, f'target_{number}.jpg')
        # 检查状态码，如果是404，说明小车已经退出迷宫，我们可以停止记录路径并显示图像
    print("7")
    while sensor_data.get("statusCode", 0) == 1:
        print("8")
     # 运行getImage.py
        # 替换为你想要下载的图片的url
        image_url = "http://192.168.8.1:8083/?action=snapshot"

        # 下载图像
        download_image(image_url, image_path)
        print("9")
    # 运行123.py
        # Load a pretrained YOLOv8n model
        model = YOLO('C:\\Users\\tbx12\\Desktop\\Code\\train45\\weights\\best.pt')
        # Run inference on 'bus.jpg'
        results = model(image_path)
        # Show the results
        for r in results:
            im_array = r.plot()  # plot a BGR numpy array of predictions
            im = Image.fromarray(im_array[..., ::-1])  # RGB PIL image
            im.show()  # show image
            predict_path = os.path.join(predict_dir , f'predict_{number}.jpg')
            im.save(predict_path)  # save imag



        #读入数据库
        print("10")
        data = (number, sensor_data.get("timeElapsed", 0)/1000, "1", predict_path)
        # 执行SQL语句
        cursor.execute(add_data, data)

        # 提交事务，这样数据就会被写入到数据库中
        cnx.commit()

        # 最后，关闭cursor和connection
        cursor.close()
        cnx.close()

        # 更新"number.txt"中的数字
        with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "w") as file:
            file.write(str(number + 1))

        # 运行"gui.py"
        gui.run_gui()

        # exit
        sys.exit()

