#define trigPin 11
#define echoPin 12
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
String home = "APA AI Assistant";

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

// return home 
    void returnhome(void)
    {
      lcd.clear();
      for (int i = 0; i<16; i++)
      {
        lcd.setCursor(i,0);
        lcd.write(home.charAt(i));
        delay(250);
      }
    };

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   // initialize the LCD
  lcd.init();
   // Turn on the blacklight and print a message.
  lcd.backlight();
  returnhome();
}

void loop() {
  Serial.println(calc_speed());
  
    delay(50);


}
