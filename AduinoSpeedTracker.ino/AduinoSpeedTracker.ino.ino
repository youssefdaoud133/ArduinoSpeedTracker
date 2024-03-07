#define trigPin 11 // Declate Trig Pin for Ultrasonic Sensor //
#define echoPin 12 // Declate Trig Pin for Ultrasonic Sensor //
#include <LiquidCrystal_I2C.h> // Include LCD Display I2C Library //
#include <Wire.h> // Include library allows communication with I2C devices //

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display //

float calc_distance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long t = pulseIn(echoPin, HIGH);
  float distance=t/5700.0;//Distance = (Speed of Sound * Time/2) = t/(1/((350*0.0001)/2))

  return distance;
}

float calc_speed() {
  float d1 = calc_distance();         // Measure Distance 1 at time zero //
  delay(50);                          // wait for 50 ms to measure the other distance
  float d2 = calc_distance();             // Measure Distance 2 at time 50 ms //
  float speed = abs((d1 - d2) / (50 * 0.001);      // Calculate speed in m/s using formula v=d/t //
  return speed;
}

void lcd_output(float v){
      lcd.setCursor(7, 0);             // set the cursor to column 7, line 0 //
      lcd.print(v);                     // Print speed on lcd //
      lcd.setCursor(11, 0);              // set the cursor to column 11, line 0  //
      lcd.print(" m/s");                // Print m/s unit on screen //
      lcd.setCursor(7, 1);              // set the cursor to column 7, line 1 //
      lcd.print(v*3.6);                 // print speed on lcd after converting its unit //
      lcd.setCursor(11, 1);             // set the cursor to column 11, line 1 //
      lcd.print(" km/h");               // print unit km/h after this value //
  
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);           // Set the pin specified by trigPin as an output //
  pinMode(echoPin, INPUT);          // Set the pin specified by trigPin as an input //
  lcd.init();                       // initialize the LCD //
  lcd.backlight();                  // Turn on the blacklight and print a message. //
  
}

void loop() {
  float x= calc_speed();
  lcd.setCursor(0, 0);          // set the cursor to column 0, line 0 //
  lcd.print("Speed: ");            // Write a title of  Speed //
  if(x>0.5)                      // Initialize a minimum value to read to a void input errors form the enviroment //
   lcd_output(x)  ;      // Call Function lcd_output to show the results on screen //

  delay(150);                     // Wait 150 ms to do another read //
    }