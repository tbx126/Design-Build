import serial
import mysql.connector

ser = serial.Serial('COM3')  # replace '/dev/ttyS0' with your serial port name

# 创建到MySQL服务器的连接
cnx = mysql.connector.connect(user='root', password='ckn12345',
                              host='localhost',
                              database='javawebdb')

# 创建一个新的cursor对象
cursor = cnx.cursor()

# 插入数据的SQL语句
add_data = ("INSERT INTO info "
               "(idinfo, abb) "
               "VALUES (%s, %s)")

data = ('1', ser.readline().decode('utf-8').strip())

# 执行SQL语句
cursor.execute(add_data, data)

# 提交事务，这样数据就会被写入到数据库中
cnx.commit()

# 最后，关闭cursor和connection
cursor.close()
cnx.close()