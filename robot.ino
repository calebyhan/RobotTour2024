// define IO pin
#define PWMA 5    // Controls power to right motor
#define PWMB 6    // Controls power to left motor
#define AIN 7     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN 8     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define STBY 3    // Place H-Bridge in standby if LOW, Run if HIGH

const int trigPin = 13;
const int echoPin = 12;
float duration, distance;

//init the car
void setup() {
  pinMode(PWMA, OUTPUT);     //set IO pin mode OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  //Enable Motors to run
  digitalWrite(PWMA, LOW);  // Fully on 
 // digitalWrite(PWMA, HIGH);  // Fully on
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance = 6;
  digitalWrite(STBY, LOW);
  Serial.begin(9600);
}

//main loop
void loop() {
  Serial.println(distance);
  while (distance > 5){  // wait for mode switch to be pressed (go to 0)
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

  // 45 degrees: 187.5
  // 90 degrees: 375
  // 180 degrees: 750

  // 50 cm: 800

  delay(1000);

  go(1600);

  while(1);
}

void turnLeft(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, HIGH);    // Forward direction
  digitalWrite(PWMA, HIGH);   // Full power
  digitalWrite(BIN, LOW);    // Forward direction
  digitalWrite(PWMB, HIGH);   // Full power
  delay(mS);
  digitalWrite(STBY, LOW);
}

void turnRight(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, LOW);    // Forward direction
  digitalWrite(PWMA, HIGH);   // Full power
  digitalWrite(BIN, HIGH);    // Forward direction
  digitalWrite(PWMB, HIGH);   // Full power
  delay(mS);
  digitalWrite(STBY, LOW);
}

void go(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, LOW);    // Forward direction
  digitalWrite(PWMA, LOW);   // Full power
  digitalWrite(BIN, LOW);    // Forward direction
  digitalWrite(PWMB, LOW);   // Full power
  delay(mS);
  digitalWrite(STBY, LOW);
}

void back(int mS) {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN, HIGH);    // Forward direction
  digitalWrite(PWMA, HIGH);   // Full power
  digitalWrite(BIN, HIGH);    // Forward direction
  digitalWrite(PWMB, HIGH);   // Full power
  delay(mS);
  digitalWrite(STBY, LOW);
}

// Function - accepts the time in milli-Seconds to go into standby for
void stopTime(int mS){
  digitalWrite(STBY, LOW);   // Go into standby
  delay(mS);                //  Wait defined time
  digitalWrite(STBY, HIGH);  //  Come out of standby
}
