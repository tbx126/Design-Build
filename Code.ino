#include <SoftwareSerial.h>

//定义五种运动状态
#define STOP      0
#define FORWARD   1
#define BACK  2
#define LEFT  3
#define RIGHT 4

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

SoftwareSerial BT(19, 18); // 10为TX引脚，11为RX引脚
char val; 
// 初始化颜色值
char colour; // 用于存储颜色代码的变量
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
    colorLED();
    
    // 然后调用超声波传感器测距函数，测量前、左、右三个方向的距离
    int Front = distanceFront();
    int Left = distanceLeft();
    int Right = distanceRight();
    
    BT.println("Distance front: " + String(Front) + " cm, Distance left: " + String(Left) + " cm, Distance right: " + String(Right) + " cm");

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
  Serial.print("Distance front: ");
  Serial.print(distanceFront);
  Serial.print("cm");
  Serial.println();
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
  Serial.print("Distance Left: ");
  Serial.print(distanceLeft);
  Serial.print("cm");
  Serial.println();
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
  Serial.print("Distance Right: ");
  Serial.print(distanceRight);
  Serial.print("cm");
  Serial.println();
  return distanceRight;
}

// 颜色LED检测函数
void colorLED() {
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

  // 根据RGB值判断颜色，并打印
  if (blue < red && blue < green) { 
    Serial.println('B');
    colour = 'B';
    motorRun(0, 0); delay(3000);        //静止3秒
    motorRun(3, 60); delay(60);   //右转
    motorRun(2, 50); delay(120);      //后退
    motorRun(3, 60); delay(60);   //右转
  } else if (red < 5 && green < 5 && blue < 5) { 
    Serial.println('W');
    colour = 'W';
  } else if (green < red && green < blue) { 
    colour = 'G';
    Serial.println('G');
  } else if (red < blue && red < green && red < 20) {
    colour = 'R';
    Serial.println('R');
  } else if (red < green && green < blue && green < 20) { 
    colour = 'Y';
    Serial.println('Y');
  }
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