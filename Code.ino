#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//定义五种运动状态
#define STOP      0
#define FORWARD   1
#define BACK      2
#define LEFT      3
#define RIGHT     4

const int leftMotor1 = 10;
const int leftMotor2 = 11;
const int rightMotor1 = 12;
const int rightMotor2 = 13;

// 定义超声波传感器的引脚
const int trigFront = 41; // 前方超声波传感器的触发引脚
const int echoFront = 40; // 前方超声波传感器的回波引脚
const int trigLeft = 39; // 左侧超声波传感器的触发引脚
const int echoLeft = 38; // 左侧超声波传感器的回波引脚
const int trigRight = 43; // 右侧超声波传感器的触发引脚
const int echoRight = 42; // 右侧超声波传感器的回波引脚

// 定义色彩传感器的引脚
const int S0 = 46;
const int S1 = 44;
const int S2 = 45;
const int S3 = 47;
const int out = 33;

SoftwareSerial BT(19, 18); // 19为TX引脚，18为RX引脚
char val; 

// 初始化颜色值
String colour; // 用于存储颜色代码的变量
int red = 0; // 红色强度值
int green = 0; // 绿色强度值
int blue = 0; // 蓝色强度值

void setup() {
  // 设置串口通信的波特率为9600
  Serial.begin(9600);

  BT.begin(9600);  //设置HC-06兼容模块波特率
  
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
    // 在主循环中，首先调用颜色LED检测函数
    String colour = colorLED();
    
    // 然后调用超声波传感器测距函数，测量前、左、右三个方向的距离
    int Front = distanceFront();
    int Left = distanceLeft();
    int Right = distanceRight();
    
    StaticJsonDocument<200> doc;

    // Get the current time
    unsigned long currentTime = millis();

    // Store the current time in the JSON document
    doc["timeElapsed"] = currentTime;

    // Add the detected colour to the JSON document
    doc["Colour Detected"] = colour;

    // If less than 10 seconds have passed since the program started, send statusCode 200
    if (currentTime < 10000) {
        doc["statusCode"] = 200;
        doc["Distance front"] = Front;
        doc["Distance left"] = Left;
        doc["Distance right"] = Right;
    } else { // After 10 seconds, send statusCode 404
        doc["statusCode"] = 404;
        doc["message"] = "The car has exited the maze.";
    }

    // Serialize JSON document
    String output;
    serializeJson(doc, output);

    // Now you can print or send this output string
    BT.println(output);
    if (Serial.available()) {
        val = Serial.read();
        BT.print(val);
    }
    
    if(Front <= 10) {
        if(Left <= 15 && Right <= 15) {
            motorRun(1,30);
            /* 
            motorRun(0, 0); delay(3000);        //静止3秒
            motorRun(3, 40); delay(100);   //右转
            motorRun(2, 50); delay(1000);      //后退
            motorRun(3, 40); delay(100);   //右转
            */
        }
        else {
            if(Left >= Right + 5) {
                motorRun(3,30);
                delay(50);
            }
            else {
                motorRun(4,30);
                delay(50);
            }
        }      
    }
    else {
        motorRun(1,30);
    }

    delay(10);
}

// 前方超声波传感器测距函数
int distanceFront() {
  long durationFront, distanceFront;

  // 设置超声波传感器为发送模式，发送超声波
  pinMode(trigFront, OUTPUT);
  digitalWrite(trigFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFront, LOW);

  // 设置超声波传感器为接收模式，接收回波
  pinMode(echoFront, INPUT);
  durationFront = pulseIn(echoFront, HIGH);

  // 计算并返回距离
  distanceFront = durationFront / 58;
  /*
  Serial.print("Distance front: ");
  Serial.print(distanceFront);
  Serial.print("cm");
  Serial.println();*/
  return distanceFront;
}

// 左侧超声波传感器测距函数
int distanceLeft() {
  long durationLeft, distanceLeft;

  // 设置超声波传感器为发送模式，发送超声波
  pinMode(trigLeft, OUTPUT);
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);

  // 设置超声波传感器为接收模式，接收回波
  pinMode(echoLeft, INPUT);
  durationLeft = pulseIn(echoLeft, HIGH);

  // 计算并返回距离
  distanceLeft = durationLeft / 58;
  /*
  Serial.print("Distance Left: ");
  Serial.print(distanceLeft);
  Serial.print("cm");
  Serial.println();*/
  return distanceLeft;
}

// 右侧超声波传感器测距函数
int distanceRight() {
  long durationRight, distanceRight;

  // 设置超声波传感器为发送模式，发送超声波
  pinMode(trigRight, OUTPUT);
  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW);

  // 设置超声波传感器为接收模式，接收回波
  pinMode(echoRight, INPUT);
  durationRight = pulseIn(echoRight, HIGH);

  // 计算并返回距离
  distanceRight = durationRight / 58;
  /*
  Serial.print("Distance Right: ");
  Serial.print(distanceRight);
  Serial.print("cm");
  Serial.println();*/
  return distanceRight;
}

// 颜色LED检测函数
String colorLED() {
  // 检测红色
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 

  // 检测蓝色
  digitalWrite(S3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // 检测绿色
  digitalWrite(S2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);

  // 根据RGB值判断颜色，并打印
  if (red > green && red > blue) {
    Serial.println("Red");
    colour = "Red";
  } else if (green > red && green > blue) {
    Serial.println("Green");
    colour = "Green";
  } else if (blue > red && blue > green) {
    Serial.println("Blue");
    colour = "Blue";
    // ... 省略部分代码 ...
  } else if (red < 5 && green < 5 && blue < 5) {
    Serial.println("White");
    colour = "White";
  } else {
    Serial.println("Unknown");
    colour = "Unknown";
  }

  return colour;
}

void motorRun(int direction, int speed) {
  int pwmValue = map(speed, 0, 100, 0, 255); // 将速度映射为合适的PWM值

  switch (direction) {
    case RIGHT:
      digitalWrite(leftMotor1, LOW);
      analogWrite(leftMotor2, pwmValue);
      digitalWrite(rightMotor1, LOW);
      analogWrite(rightMotor2, pwmValue);
      break;
    case LEFT:
      analogWrite(leftMotor1, pwmValue);
      digitalWrite(leftMotor2, LOW);
      analogWrite(rightMotor1, pwmValue);
      digitalWrite(rightMotor2, LOW);
      break;
    case FORWARD:
      analogWrite(leftMotor1, pwmValue);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      analogWrite(rightMotor2, pwmValue);
      break;
    case BACK:
      digitalWrite(leftMotor1, LOW);
      analogWrite(leftMotor2, pwmValue);
      analogWrite(rightMotor1, pwmValue);
      digitalWrite(rightMotor2, LOW);
      
      break;
    default:
      digitalWrite(leftMotor1, LOW);
      analogWrite(leftMotor2, 0);
      digitalWrite(rightMotor1, LOW);
      analogWrite(rightMotor2, 0);
  }
}