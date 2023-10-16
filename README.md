# Design & Build

This project involves an Arduino-based intelligent robot car, equipped with features such as ultrasonic obstacle avoidance, automatic treasure detection (different colored objects), and real-time data transmission over a wireless network.

## Directory Structure

Here are the key files and folders in this project:

- `target`: A folder storing untreated images captured from the Arduino car's camera, used as input for image recognition.
- `predict`: A folder storing images that have been recognized and marked by the model, showcasing the image recognition results.
- `testWeb1010`: An Eclipse dynamic web site folder configured for Tomcat, used to display the running status and image recognition results of the Arduino car.
- `train45`: A folder storing the pre-trained neural network image recognition model.
- `Code.ino`: The source code file for the Arduino car, containing all instructions for controlling the car's operation and sending data via Wi-Fi and Bluetooth serial ports.
- `demo.py`: The main Python script responsible for reading Wi-Fi and Bluetooth serial port information, invoking the model for image recognition, etc.
- `gui.py`: A Graphical User Interface (GUI) script, showcasing images in the `target` and `predict` folders.
- `number.txt`: A data file storing the current number of car runs.
- `XCOM V2.6.exe`: A third-party tool used for reading and debugging the car's Bluetooth serial port program.

## Hardware Requirements

- **HC-SR04 Ultrasonic Sensor**: Uses three ultrasonic sensors on the left and right sides to determine the car's motion state. By comparing the return values of the three sensors, the car's next motion state is determined.

- **L298N Driver Module**: Controls the motion of the four wheels of the car through the driver module. L298N can directly control the motor and set its control level through the main chip's I/O input. This makes the motor move forward and backward, easy to operate, stable, and can meet the high current driving conditions of the DC motor.

- **TCS3200D Color Sensor**: We use a color sensor to detect the "treasure". By recognizing different colors, we achieve more accurate "treasure" detection.

- **Wi-Fi Module and Camera**: We use the Wi-Fi module to control the camera to take photos. When the car detects the object being tested, it automatically controls the camera to take a picture and proceed to the next step.

- **Bluetooth Module**: Through the Bluetooth module, we connect the car's data with the website database and connect the photography process with the prediction model. Through the Bluetooth module, we achieve a fully automated process.

## System Architecture

- **Arduino Car**: The Arduino car is the core part of the entire system. It uses hardware such as ultrasonic sensors, color sensors, Wi-Fi modules, Bluetooth modules, and cameras to sense the environment, perform actions, and interact with the outside world.

- **Computer End**: The computer end is responsible for receiving and processing data sent by the Arduino car, including running the image recognition script, displaying recognition results, etc. Python environment and related libraries need to be installed.

- **Web End**: The web end is used to display the car's status and image recognition results in real-time. Users can remotely control the car and view the car's operating status and image recognition results through the web interface.

## Required Libraries and Modules

Before running the project, the following libraries and modules need to be installed and included in your Python and Arduino environments:

### Python Libraries

These libraries are required for `demo.py`:

- `subprocess`: Allows the spawning of new processes and interaction with their input/output/error pipes, and obtaining their return codes.
- `json`: Provides functions for processing JSON data.
- `sys`: Provides access to some variables used or maintained by the Python interpreter.
- `os`: Provides a portable way of using operating system dependent functionality.
- `serial`: A Python library for serial communication.
- `mysql.connector`: A driver for connecting to a MySQL database server from Python.
- `requests`: A popular Python library for making HTTP requests.
- `gui`: A custom module for handling the graphical user interface of the application.
- `PIL (Pillow)`: Adds image processing capabilities to your Python interpreter.
- `Ultralytics YOLO`: An implementation of the YOLO (You Only Look Once) real-time object detection algorithm.
### Arduino Libraries

These libraries are required for `Code.ino`:

- `SoftwareSerial.h`: A library for serial communication, which allows digital pins to be used for serial input/output.
- `ArduinoJson.h`: A library for handling JSON objects in Arduino, useful for parsing JSON responses from APIs or serializing data to JSON format.
# Workflow

1. **Ultrasonic Obstacle Avoidance**: After initialization, the car begins by detecting obstacles using its ultrasonic sensors. It compares the return values from the left and right sensors to determine the car's subsequent movement.

2. **Color Recognition**: As the car operates, it continuously scans for "treasure" using its color sensor. Upon identifying an object of a different color, the car halts and prepares for the next step.

3. **Photograph and Data Collection**: Once a potential "treasure" is detected, the car instructs the onboard camera to take a picture via its Wi-Fi module. Simultaneously, it collects relevant data such as run status, run time, distances from the ultrasonic sensors, and color information, which it sends via Bluetooth serial communication.

4. **Data Upload and Image Recognition**: The car sends the captured image to the computer via Wi-Fi. Upon receiving the image and data, the computer runs the image recognition script (`demo.py`) to process and identify the contents of the image.

5. **Data Writing and Result Display**: If the identified object is recognized as a "treasure", `demo.py` writes the relevant data into a MySQL database and sends the recognition results back to the car. The results are also made available to users via a web interface.

This workflow ensures that the car is continuously analyzing its environment, searching for treasures, and responding accordingly. By integrating hardware control, sensor data processing, image recognition, and web display, this project creates a comprehensive system for autonomous treasure hunting.
## Points to Note

- Ensure all hardware devices are correctly connected and all drivers are installed.
- Before running the project, ensure the Arduino car is correctly connected to Wi-Fi and the Bluetooth module is turned on.
- When viewing recognition results, make sure the web end is running normally.

# Troubleshooting & Solutions

## Problem: Arduino car cannot start

**Potential Cause**: The battery is not properly installed or charged.

**Solution**: Check the battery connections and ensure it's adequately charged. If the battery is old, it might need replacement.

## Problem: The car cannot communicate with the computer end

**Potential Cause**: The Wi-Fi or Bluetooth module is not turned on, the Arduino car is not correctly connected to the Wi-Fi network, or the computer end is not correctly set up.

**Solution**: Confirm that the Wi-Fi and Bluetooth modules are active. Ensure that the Arduino car is correctly connected to the Wi-Fi network. Validate the computer end setup, including the correct port and baud rate for serial communication.

## Problem: Image recognition results are not accurate

**Potential Cause**: The model is not well-trained, the image quality is poor, or the model's input data is not correctly processed.

**Solution**: Consider retraining the model with more diverse and high-quality data. Improving the data preprocessing method can also enhance accuracy. Ensure that the camera or image source provides clear and high-quality images.

## Problem: The car cannot avoid obstacles or detect treasures

**Potential Cause**: The ultrasonic or color sensor is not working properly, or the corresponding code has errors.

**Solution**: Verify the functionality of the ultrasonic and color sensors. Inspect the corresponding code for any errors. If the sensors are not functioning as expected, they might need replacement or recalibration.

# Conclusion

This Arduino-based intelligent robot car project is a comprehensive integration of various technologies including Arduino programming, Python scripting, ultrasonic sensing, color recognition, Wi-Fi and Bluetooth communication, image recognition, and web development. It's a fun and educational project that can help students learn about AI, robotics, and IoT.

While the project may encounter some difficulties, such as hardware connection issues, Wi-Fi/Bluetooth communication issues, or image recognition accuracy issues, these can be resolved with proper troubleshooting and perseverance.
