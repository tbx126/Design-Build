#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//定义五种运动状态
#define STOP      0
#define FORWARD   1
#define BACK      2
#define LEFT      3
#define RIGHT     4

const int leftMotor1 = 4;
const int leftMotor2 = 5;
const int rightMotor1 = 6;
const int rightMotor2 = 7;

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

int out=2;
int flag=0;
byte counter=0;
byte Red=0,Green=0,Blue=0;

// 初始化颜色值
String colour; // 用于存储颜色代码的变量
int red = 0; // 红色强度值
int green = 0; // 绿色强度值
int blue = 0; // 蓝色强度值

SoftwareSerial BT(19, 18); // 19为TX引脚，18为RX引脚
char val; 

void setup() {
  // 设置串口通信的波特率为9600
  Serial.begin(9600);
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);

  BT.begin(9600);  //设置HC-06兼容模块波特率
  
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
    // 在主循环中，首先调用颜色LED检测函数

    TCS();
    
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
        doc["statusCode"] = 1;
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

void TCS() {
  flag = 0;
  digitalWrite(S1,HIGH);
  digitalWrite(S0,HIGH);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  attachInterrupt(0, ISR_INTO, LOW);
  timer0_init();
  determineColor(Red, Green, Blue);
}

void ISR_INTO() {
  counter++;
}

void timer0_init(void) {
  TCCR2A = 0x00;
  TCCR2B = 0x07;   // the clock frequency source 1024 points
  TCNT2 = 100;     // 10 ms overflow again
  TIMSK2 = 0x01;   // allow interrupt
}


ISR(TIMER2_OVF_vect) { // the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
  TCNT2 = 100;
  flag++;
  
  if(flag==1) {
    Red=counter;
    //Serial.print("red=");
    //Serial.println(Red);
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
  } else if(flag==2){
    Green=counter;
    //Serial.print("green=");
    //Serial.println(Green);
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
  } else if(flag==3){
    Blue=counter;
    //Serial.print("blue=");
    //Serial.println(Blue);
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
  } else if(flag==4){
    flag=0;
  }
  counter=0;
}

void determineColor(int red, int green, int blue) {
  String colour;

  float whiteCenter[] = {105.32727273, 126.58181818, 123.63636364};
  float redCenter[] = {131.75, 61.5, 76.07142857};
  float blueCenter[] = {115.8, 101.02857143, 168.37142857};
  float greenCenter[] = {76.07142857, 131.75, 61.5}; // Replace with your actual green centroid

  float distanceToWhite = sqrt(pow(red - whiteCenter[0], 2) + pow(green - whiteCenter[1], 2) + pow(blue - whiteCenter[2], 2));
  float distanceToRed = sqrt(pow(red - redCenter[0], 2) + pow(green - redCenter[1], 2) + pow(blue - redCenter[2], 2));
  float distanceToBlue = sqrt(pow(red - blueCenter[0], 2) + pow(green - blueCenter[1], 2) + pow(blue - blueCenter[2], 2));
  float distanceToGreen = sqrt(pow(red - greenCenter[0], 2) + pow(green - greenCenter[1], 2) + pow(blue - greenCenter[2], 2)); // Green distance

  if (distanceToWhite < distanceToRed && distanceToWhite < distanceToBlue && distanceToWhite < distanceToGreen) {
    colour = "White";
    Serial.println("White");
  } else if (distanceToRed < distanceToWhite && distanceToRed < distanceToBlue && distanceToRed < distanceToGreen) {
    colour = "Red";
    Serial.println("Red");
  } else if (distanceToBlue < distanceToWhite && distanceToBlue < distanceToRed && distanceToBlue < distanceToGreen) {
    colour = "Blue";
    Serial.println("Blue");
  } else if (distanceToGreen < distanceToWhite && distanceToGreen < distanceToRed && distanceToGreen < distanceToBlue) { // Green condition
    colour = "Green";
    Serial.println("Green");
  } else {
    colour = "Unknown";
    Serial.println("Unknown");
  }
}