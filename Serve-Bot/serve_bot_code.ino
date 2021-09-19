#define STOP_COUNT 5
#define STOP_TIME 15000
#define FORWARD_SPEED 120 //160
#define TURNING_SPEED 95 //100,80
#define INVALID_PATH_SPEED 70 //80 

// Dont change threshold value unless required

#define THRESHOLD 910

// Dont change any code from here

#define echoPin 23
#define trigPin 10
#define buzzerPin 11


const int sensorPins[] = {A5, A4, A3, A2, A1, A0, A11, A10, A9, A8, A7, A6};
const int dir_pins[2] = {28, 30};
const int pwm_pins[2] = {8, 9};


int station_count = 0;
long duration;
int distance;
int statusSensor[12] = {0};
bool reached_destination = false;

int check(int a[], int b[]) {
  int ar_count = 0;
  for (int i = 0; i < 12; i++) {
    if (a[i] == b[i]) ar_count++;
  }
  if (ar_count == 12) return 1;
  return 0;
}

// prints ultra sonic and line following sensor

void print_sensor_values() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("\n");

  for (int i = 0; i < 12; i++) {
    Serial.print(statusSensor[i]);
    Serial.print(" ");
  }
  Serial.print(" \n");
}

int IR_status(int ar[]) {

  int stop[12]      =        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  int noPath[12]    =        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int forward1[12]  =        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
  int forward2[12]  =        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0};
  int forward3[12]  =        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0};
  int forward4[12]  =        {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0};
  int forward5[12]  =        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0};
  int forward6[12]  =        {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0};

  int right1[12]    =        {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
  int right2[12]    =        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
  int right3[12]    =        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  int right4[12]    =        {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
  int right5[12]    =        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
  int right6[12]    =        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
  int right7[12]    =        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

  int left1[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0};
  int left2[12]     =        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0};
  int left3[12]     =        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
  int left4[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0};
  int left5[12]     =        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
  int left6[12]     =        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0};
  int left7[12]     =        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};


  if (check(ar, stop)) return 0;

  if (check(ar, forward1)) return 1;
  if (check(ar, forward2)) return 1;
  if (check(ar, forward3)) return 1;
  if (check(ar, forward4)) return 1;
  if (check(ar, forward5)) return 1;
  if (check(ar, forward6)) return 1;

  if (check(ar, left1)) return 2;
  if (check(ar, left2)) return 2;
  if (check(ar, left3)) return 2;
  if (check(ar, left4)) return 2;
  if (check(ar, left5)) return 2;
  if (check(ar, left6)) return 2;
  if (check(ar, left7)) return 2;

  if (check(ar, right1)) return 3;
  if (check(ar, right2)) return 3;
  if (check(ar, right3)) return 3;
  if (check(ar, right4)) return 3;
  if (check(ar, right5)) return 3;
  if (check(ar, right6)) return 3;
  if (check(ar, right7)) return 3;

  if (check(ar, noPath)) return 4;

  return -1;
}


void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode (dir_pins[0], OUTPUT);
  pinMode (dir_pins[1], OUTPUT);

  pinMode(dir_pins[0], OUTPUT);
  pinMode(dir_pins[1], OUTPUT);

  for (int i = 0; i < 12; i++) pinMode(sensorPins[i], INPUT);

}

void loop()
{
  for (int i = 0; i < 12; i++) {
    statusSensor[i] = (analogRead(sensorPins[i]) >= THRESHOLD);
    Serial.print(analogRead(sensorPins[i]));
    Serial.print(" ");
  }
  Serial.print("\n");
  print_sensor_values();

    if (distance >= 24) {//20

        if (IR_status(statusSensor) == 0) {
            station_count++;

            if (station_count < STOP_COUNT) {

                digitalWrite(dir_pins[0], LOW);
                analogWrite(pwm_pins[0], 0);
                digitalWrite(dir_pins[1], LOW);
                analogWrite(pwm_pins[1], 0);

                Serial.print("Stoping here for the next ");
                Serial.print(STOP_TIME);
                Serial.print(" seconds\n");
                

                digitalWrite(dir_pins[0], LOW);
                analogWrite(pwm_pins[0], 80);
                digitalWrite(dir_pins[1], LOW);
                analogWrite(pwm_pins[1], 80);
                delay(1000);

            }

            else {

                digitalWrite(dir_pins[0], LOW);
                analogWrite(pwm_pins[0], 0);
                digitalWrite(dir_pins[1], LOW);
                analogWrite(pwm_pins[1], 0);
                Serial.print("Reached Destination\n");  
            }
        }

        else if (IR_status(statusSensor) == 1) {
            digitalWrite(dir_pins[0], LOW);
            analogWrite(pwm_pins[0], FORWARD_SPEED);
            digitalWrite(dir_pins[1], LOW);
            analogWrite(pwm_pins[1], FORWARD_SPEED);
            Serial.print("Moving Forward\n");
        }

        else if (IR_status(statusSensor) == 2) {
            digitalWrite(dir_pins[0], LOW);
            analogWrite(pwm_pins[0], TURNING_SPEED);
            digitalWrite(dir_pins[1], LOW);
            analogWrite(pwm_pins[1], 0);
            Serial.print("Moving Left\n");
        }

        else if (IR_status(statusSensor) == 3) {
            digitalWrite(dir_pins[0], LOW);
            analogWrite(pwm_pins[0], 0);
            digitalWrite(dir_pins[1], LOW);
            analogWrite(pwm_pins[1], TURNING_SPEED);
            Serial.print("Moving Right\n");
        }

        else if (IR_status(statusSensor) == 4) {
            digitalWrite(dir_pins[0], LOW);
            analogWrite(pwm_pins[0], 0);
            digitalWrite(dir_pins[1], LOW);
            analogWrite(pwm_pins[1], 0);
            Serial.print("Out of Track\n");

        }

        else {
            digitalWrite(dir_pins[0], LOW);
            analogWrite(pwm_pins[0], INVALID_PATH_SPEED);
            digitalWrite(dir_pins[1], LOW);
            analogWrite(pwm_pins[1], INVALID_PATH_SPEED);
            Serial.print("Invalid path\n");
        }
    }

    else {
    Serial.print("Obstacle detected\n");
    digitalWrite(dir_pins[0], LOW);
    analogWrite(pwm_pins[0], 0);
    digitalWrite(dir_pins[1], LOW);
    analogWrite(pwm_pins[1], 0);
    
    }
}
