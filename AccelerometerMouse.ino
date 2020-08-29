#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int button1 = 6;
int button2 = 7;
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = -(gz + 400) / 200; // "-400" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy = -(gx + 1500) / 200; // same here about "-200"
  
  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gy = ");
  Serial.print(gy);
  Serial.print(" | gz = ");
  Serial.print(gz);

  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);

  Mouse.move(vx, vy);

  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);

  if (buttonState1 == LOW) {
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.release(MOUSE_LEFT);
    delay(200);
  }
  else if (buttonState2 == LOW) {
    Mouse.press(MOUSE_RIGHT);
    delay(100);
    Mouse.release(MOUSE_RIGHT);
    delay(200);
  }
  delay(80);
}

