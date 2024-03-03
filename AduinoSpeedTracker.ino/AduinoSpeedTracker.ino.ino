#define trigPin 11
#define echoPin 12

float calc_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long t = pulseIn(echoPin, HIGH);
  float distance=t/57.0;//Distance = (Speed of Sound * Time/2) = t/(1/((350*0.0001)/2))

  return distance;
}

float calc_speed() {
  float d1 = calc_distance();
  delay(50);
  float d2 = calc_distance();
  float speed = abs(d1 - d2) / (50 * 0.001); // Calculate speed in cm/s
  
  return speed;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  Serial.println(calc_speed());
  
    delay(50);


}
