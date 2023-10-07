import serial

ser = serial.Serial('COM6')  # replace '/dev/ttyS0' with your serial port name
with open('C:\\Users\\tbx12\\Desktop\\data.txt', 'w') as f:  # replace 'YourUsername' with your actual username
    while True:
        data = ser.readline().decode('utf-8').strip()  # read data from serial port and strip end of line
        print(data)
        f.write(data + '\n')  # write data to file and append a newline character
        f.flush()  # flush data to disk