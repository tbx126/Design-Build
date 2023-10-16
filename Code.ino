// Arduino code for robot car with Bluetooth and sensors

#include <SoftwareSerial.h> 
#include <ArduinoJson.h>

// Define motion states 
#define STOP      0
#define FORWARD   1
#define BACK      2  
#define LEFT      3
#define RIGHT     4

// Motor pins
const int leftMotor1 = 4;  
const int leftMotor2 = 5;
const int rightMotor1 = 6;
const int rightMotor2 = 7;

// Ultrasonic sensor pins
const int trigFront = 41;  // Trigger pin for front sensor
const int echoFront = 40;  
const int trigLeft = 39;   
const int echoLeft = 38;
const int trigRight = 43;  
const int echoRight = 42;

// Color sensor pins
const int S0 = 46;
const int S1 = 44; 
const int S2 = 45;
const int S3 = 47;

// Other variables
int statusCode = 200; 
bool alreadyStopped = false;

StaticJsonDocument<200> doc; 

// Color sensor variables
int out=2;
int flag=0;
byte counter=0;
byte Red=0,Green=0,Blue=0;  
String colour;
int red = 0;   
int green = 0;
int blue = 0;

// Bluetooth serial 
SoftwareSerial BT(19, 18); 

void setup() {

  Serial.begin(9600);
  
  // Set color sensor pins as output
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);

  // Start Bluetooth serial
  BT.begin(9600);  
  
  // Set motor pins as output
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  
}

void loop() {

  // Call color detection
  //Due to the accuracy and error issues of color recognition, we have ultimately decided to abandon color recognition and instead use an ultrasonic sensor to obtain the distances of the front, left, and right sides of the car in order to determine whether the treasure has been detected.
  //TCS();

  // Get distance values
  int Front = distanceFront();
  int Left = distanceLeft();
  int Right = distanceRight();

  // Create JSON doc
  unsigned long currentTime = millis();  
  doc["timeElapsed"] = currentTime;
  doc["Colour Detected"] = colour;
  doc["statusCode"] = statusCode;
  doc["Distance front"] = Front;
  doc["Distance left"] = Left;  
  doc["Distance right"] = Right;

  // Add color values
  doc["Red"] = Red;
  doc["Green"] = Green;
  doc["Blue"] = Blue;

  // Check for incoming Bluetooth data
  if (Serial.available()) {
    char val = Serial.read();
    BT.println(val);  
  }

  // Check front distance
  if(Front <= 22) {
    
    // If close on all sides, stop
    if(Left <= 16 && Right <= 16 && !alreadyStopped) {
      
      statusCode = 1;  
      doc["statusCode"] = statusCode;
      
      String output;
      serializeJson(doc, output);
      BT.println(output);

      if (Serial.available()) {
        char val = Serial.read();
        BT.println(val);  
      }

      // Stop sequence
      motorRun(2, 30); delay(300);
      motorRun(0, 0);  delay(16000);
      motorRun(4, 50); delay(300);
      motorRun(2, 40); delay(300);
      motorRun(4, 50); delay(500);

      statusCode = 200;
      alreadyStopped = true;

    }
    
    // If not already stopped, turn left/right
    else if(!alreadyStopped){
      
      if(Left >= Right + 2) {
        motorRun(3,50); 
        delay(120);
      }
      else {
        motorRun(4,50);
        delay(120);
      }
      
    }
    
  }
  
  // If stopped previously, reset flag
  else {
    if(alreadyStopped) {
      alreadyStopped = false; 
    }
    motorRun(1, 30); 
  }

  // Send JSON output
  String output;
  serializeJson(doc, output);
  BT.println(output);

  delay(10);

}

// Front distance function
int distanceFront() {
  
  long durationFront, distanceFront;

  pinMode(trigFront, OUTPUT);
  digitalWrite(trigFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFront, LOW);

  pinMode(echoFront, INPUT);
  durationFront = pulseIn(echoFront, HIGH);

  distanceFront = durationFront / 58;

  return distanceFront;
}

// Left distance function 
int distanceLeft() {
  
  long durationLeft, distanceLeft;

  pinMode(trigLeft, OUTPUT);
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);

  pinMode(echoLeft, INPUT);
  durationLeft = pulseIn(echoLeft, HIGH);

  distanceLeft = durationLeft / 58;

  return distanceLeft;
}

// Right distance function
int distanceRight() {

  long durationRight, distanceRight;

  pinMode(trigRight, OUTPUT);
  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW);

  pinMode(echoRight, INPUT);
  durationRight = pulseIn(echoRight, HIGH);

  distanceRight = durationRight / 58;

  return distanceRight;
}

// Motor control function 
void motorRun(int direction, int speed) {
  
  int pwmValue = map(speed, 0, 100, 0, 255);

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

// Color detection function
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

// Interrupt service routine
void ISR_INTO() {
  counter++; 
}

// Timer initialization
void timer0_init(void) {
  
  TCCR2A = 0x00;
  TCCR2B = 0x07;   
  TCNT2 = 100;     
  TIMSK2 = 0x01;   

}

// Timer interrupt service routine  
ISR(TIMER2_OVF_vect) {

  TCNT2 = 100;
  flag++;
  
  if(flag==1) {

    Red=counter;

    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);

  } else if(flag==2){

    Green=counter;

    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);

  } else if(flag==3){

    Blue=counter;

    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);

  } else if(flag==4){

    flag=0;

  }

  counter=0;

}

// Color determination function
void determineColor(int red, int green, int blue) {

  // Color centroids
  float whiteCenter[] = {105.32727273, 126.58181818, 123.63636364};
  float redCenter[] = {131.75, 61.5, 76.07142857};
  float blueCenter[] = {115.8, 101.02857143, 168.37142857};
  float greenCenter[] = {76.07142857, 131.75, 61.5};

  float distanceToWhite = sqrt(pow(red - whiteCenter[0], 2) + pow(green - whiteCenter[1], 2) + pow(blue - whiteCenter[2], 2));
  float distance