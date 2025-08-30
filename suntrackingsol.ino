#include <Servo.h>

Servo myServo;

int LDR_Left = A0;   // Left LDR connected to A0
int LDR_Right = A1;  // Right LDR connected to A1

int pos = 90;        // Initial position of the servo (middle)
int tolerance = 10;  // Sensitivity for movement

void setup() {
  myServo.attach(9);   // Servo signal pin on D9
  myServo.write(pos);  // Move servo to start position
  delay(1000);
  
  Serial.begin(9600);
}

void loop() {
  int leftValue = analogRead(LDR_Left);   // Read left LDR
  int rightValue = analogRead(LDR_Right); // Read right LDR

  int error = leftValue - rightValue;     // Difference between LDRs

  // Debugging
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" | Right: ");
  Serial.print(rightValue);
  Serial.print(" | Error: ");
  Serial.println(error);

  if (abs(error) > tolerance) {
    if (error > 0) {
      pos += 2;  // Move right faster
    } 
    else if (error < 0) {
      pos -= 2;  // Move left faster
    }
    pos = constrain(pos, 0, 180); // Ensure pos stays within bounds
    myServo.write(pos);
    delay(10); // Servo speed control
  }
}