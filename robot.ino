// define IO pin
#define PWMA 5    // Controls power to right motor
#define PWMB 6    // Controls power to left motor
#define AIN 7
#define BIN 8
#define STBY 3

const int trigPin = 13;
const int echoPin = 12;
float duration, distance;

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  digitalWrite(PWMA, LOW);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance = 10000;
  
  digitalWrite(STBY, LOW);
  Serial.begin(9600);
}

void loop() {
  while (distance > 7){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(100);
  }

  // 90 degree turns: 270
  
  delay(1000);

  start();

  // CHANGE HERE


  // CHANGE HERE
  endRun();

  delay(10000000);
}

void start() {
  back(385);
  delay(500);
  turnRight(540);
  delay(500);
}

void endRun() {
  back(195);
}

void moveBlock() {
  for (int i = 0; i < 4; i++) {
    go(195);
    delay(300);
  }
  turnLeft(50);
  delay(300);
}

void turnLeft(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, HIGH);
  digitalWrite(PWMA, HIGH);
  digitalWrite(BIN, LOW);
  digitalWrite(PWMB, HIGH);
  delay(mS);
  digitalWrite(STBY, LOW);
}

void turnRight(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, LOW);
  digitalWrite(PWMA, HIGH);
  digitalWrite(BIN, HIGH);
  digitalWrite(PWMB, HIGH);
  delay(mS);
  digitalWrite(STBY, LOW);
}

void go(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, LOW);
  digitalWrite(PWMA, HIGH);
  digitalWrite(BIN, LOW);
  digitalWrite(PWMB, HIGH);
  delay(mS);
  digitalWrite(STBY, LOW);
}

void back(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, HIGH);
  digitalWrite(PWMA, HIGH);
  digitalWrite(BIN, HIGH);
  digitalWrite(PWMB, HIGH);
  delay(mS);
  digitalWrite(STBY, LOW);
}
