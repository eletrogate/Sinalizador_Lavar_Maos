#define Sensor1 A0
#define Sensor2 A1
#define Laser1 2
#define Laser2 3

void setup() {
  Serial.begin(9600);
  pinMode(Laser1, OUTPUT);
  pinMode(Laser2, OUTPUT);
  digitalWrite(Laser1, HIGH);
  digitalWrite(Laser2, HIGH);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
}

void loop() {
Serial.print("LDR 1: ");Serial.println(analogRead(Sensor1);
Serial.print("LDR 2: ");Serial.println(analogRead(Sensor2);
}