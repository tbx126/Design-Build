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
    # Send a GET request to the url
    response = requests.get(url, stream=True)
    # Raise an exception in case of HTTP errors
    response.raise_for_status()

    # Open a file and write the content of the response into it
    with open(filename, 'wb') as file:
        for chunk in response.iter_content(chunk_size=8192):
            file.write(chunk)


ser = serial.Serial('COM6')  # replace 'COM6' with your actual serial port name
# Check if the file to store the integer exists
print("1")
if not os.path.exists("C:\\Users\\tbx12\\Desktop\\Code\\number.txt"):
    with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "w") as file:
        file.write("0")
print("2")
# Read the integer value from the file
with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "r") as file:
    number = int(file.read())
print("3")

while True:  # replace with your own condition for when to stop
    data = ser.readline().decode('utf-8').strip()
    print("4")
    try:
        # Try to parse the JSON data
        sensor_data = json.loads(data)
    except json.JSONDecodeError:
        continue  # skip if data is not valid JSON

    # Create a connection to the MySQL server
    cnx = mysql.connector.connect(user='root', password='123456', host='localhost', database='javawebdb')
    print("5")

    # Create a new cursor object
    cursor = cnx.cursor()

    # SQL statement to insert data
    add_data = ("INSERT INTO robotinfo "
                "(robotID, time, path, result) "
                "VALUES (%s, %s, %s, %s)")

    print("6")

    target_dir = 'C:\\Users\\tbx12\\Desktop\\Code\\target'
    predict_dir = 'C:\\Users\\tbx12\\Desktop\\Code\\predict'
    image_path = os.path.join(target_dir, f'target_{number}.jpg')

    # Check the status code, if it is 404, it means that the cart has already exited the maze, 
    # we can stop recording the path and display the image
    print("7")

    while sensor_data.get("statusCode", 0) == 1:
        print("8")

        # Run getImage.py
        # Replace with the url of the image you want to download
        image_url = "http://192.168.8.1:8083/?action=snapshot"

        # Download the image
        download_image(image_url, image_path)
        print("9")

        # Run 123.py
        # Load a pretrained YOLOv8n model
        model = YOLO('C:\\Users\\tbx12\\Desktop\\Code\\train45\\weights\\best.pt')
        # Run inference on 'bus.jpg'
        results = model(image_path)
        # Show the results
        for r in results:
            im_array = r.plot()  # plot a BGR numpy array of predictions
            im = Image.fromarray(im_array[..., ::-1])  # RGB PIL image
            im.show()  # show image
            predict_path = os.path.join(predict_dir, f'predict_{number}.jpg')
            im.save(predict_path)  # save image

        # Read into the database
        print("10")
        data = (number, sensor_data.get("timeElapsed", 0) / 1000, "1", predict_path)
        # Execute the SQL statement
        cursor.execute(add_data, data)

        # Commit the transaction, so the data will be written to the database
        cnx.commit()

        # Finally, close the cursor and connection
        cursor.close()
        cnx.close()

        # Update the number in "number.txt"
        with open("C:\\Users\\tbx12\\Desktop\\Code\\number.txt", "w") as file:
            file.write(str(number + 1))

        # Run "gui.py"
        gui.run_gui()

        # Exit
        sys.exit()