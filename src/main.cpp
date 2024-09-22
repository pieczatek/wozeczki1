#include <Arduino.h>
#include "BluetoothSerial.h"
#include <ESP32Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

static const int servoPin = 13;

Servo servo1;

void setup()
{
  Serial.begin(115200);
  servo1.attach(servoPin);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void rotateForward()
{
  for (int posDegrees = 0; posDegrees <= 90; posDegrees++)
  {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}

void rotateBack()
{
  for (int posDegrees = 90; posDegrees >= 0; posDegrees--)
  {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}

void handleCommand(int command)
{
  Serial.print("Handling command: ");
  Serial.println(command);
  switch (command)
  {
  case 49: // ASCII "1"
    rotateForward();
    break;

  case 48: // ASCII "0"
    rotateBack();
    break;

  default:
    break;
  }
}

void loop()
{
  if (Serial.available())
  {
    int serialRead = Serial.read();
    Serial.print("UNO ");
    Serial.println(serialRead);
    SerialBT.write(serialRead);
  }
  if (SerialBT.available())
  {
    int serialBTRead = SerialBT.read();
    // Serial.print("DOS ");
    // Serial.println(serialBTRead);
    //Serial.write(serialBTRead);
    handleCommand(serialBTRead);
    
  }
  delay(20);
}