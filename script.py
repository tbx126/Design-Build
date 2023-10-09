import serial
import matplotlib.pyplot as plt
import json

ser = serial.Serial('COM5')  # replace with your serial port name

# 初始化位置和方向
x, y, direction = 0, 0, 0  # direction in degrees, 0=East, 90=North, etc.

# 记录小车的路径
path = [(x, y)]

while True:  # replace with your own condition for when to stop
    data = ser.readline().decode('utf-8').strip()

    try:
        # 尝试解析JSON数据
        sensor_data = json.loads(data)
    except json.JSONDecodeError:
        continue  # skip if data is not valid JSON

    # 检查状态码，如果是404，说明小车已经退出迷宫，我们可以停止记录路径并显示图像
    if sensor_data.get("statusCode", 0) == 404:
        print(sensor_data.get("message", ""))
        break  # break the while loop

    # 解析数据
    front = sensor_data.get("Distance front", 0)
    left = sensor_data.get("Distance left", 0)
    right = sensor_data.get("Distance right", 0)

    # 假设小车总是尽可能向前移动，当不能向前时向右转，当不能向右时向左转
    if front > 40:  # can move forward
        if direction == 0:  # facing East
            x += 40
        elif direction == 90:  # facing North
            y += 40
        elif direction == 180:  # facing West
            x -= 40
        else:  # facing South
            y -= 40
    elif right > 40:  # can't move forward, but can move right
        direction = (direction - 90) % 360
    else:  # can't move forward or right, so move left
        direction = (direction + 90) % 360

    # 记录新的位置
    path.append((x, y))

# 生成轨迹图
xs, ys = zip(*path)
plt.plot(xs, ys)
plt.show()