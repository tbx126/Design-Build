const int trigFront = 41;
const int echoFront = 40;
const int trigLeft = 39;
const int echoLeft = 38;
const int trigRight = 43;
const int echoRight = 42;

const int S0 = 46;
const int S1 = 44;
const int S2 = 45;
const int S3 = 47;
const int out = 33;

char colour;
int red = 0; 
int green = 0; 
int blue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  colorLED();
  
  // 超声波传感器测距代码
  int Front = distanceFront();
  int Left = distanceLeft();
  int Right = distanceRight();

}


int distanceFront(){
  
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

  Serial.print("Distance front: ");
  Serial.print(distanceFront);
  Serial.print("cm");
  Serial.println();

  return distanceFront;
}

int distanceLeft(){

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

  Serial.print("Distance Left: ");
  Serial.print(distanceLeft);
  Serial.print("cm");
  Serial.println();

  return distanceLeft;
}

int distanceRight(){
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

  Serial.print("Distance Right: ");
  Serial.print(distanceRight);
  Serial.print("cm");
  Serial.println();

  return distanceRight;
}

void colorLED(){
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 

    digitalWrite(S3, HIGH);
    blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

    digitalWrite(S2, HIGH);
    green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

    if (blue < red && blue < green){ 
        Serial.println('B');
        colour = 'B';
        /*
        motorRun(0, 0); delay(3000);      
        motorRun(3, 60); delay(60);  
        motorRun(2, 50); delay(120);
        motorRun(3, 60); delay(60);*/

    } else if (red < 5 && green < 5 && blue < 5){ 
        Serial.println('W');
        colour = 'W';

    } else if (green < red && green < blue) { 
        colour = 'G';
        Serial.println('G');

    } else if (red < blue && red < green && red < 20){
        colour = 'R';
        Serial.println('R');

    } else if (red < green && green < blue && green < 20) { 
        colour = 'Y';
        Serial.println('Y');
    }
}