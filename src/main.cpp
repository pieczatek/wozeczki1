#include <Arduino.h>
#include "BluetoothSerial.h"
#include <ESP32Servo.h>
#include "HardwareSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

static const String BT_DEVICE_NAME = "ESP32_Baza1";
static const int UART_VERSION = 2; // Using UART2
static const int servo360Pin = 13; // motor pin
static const int rxPin = 16;       // reveive pin
static const int txPin = 17;       // transmit pin

int neutralPWM = 1500;
int speedPWM = 300;

BluetoothSerial SerialBT;
HardwareSerial DaisyChain(UART_VERSION);
Servo servo360;

void handleBTCommand(int command);
void rotateForward();
void rotateBack();
void rotate(int direction, uint32_t ms);

void setup()
{
  Serial.begin(115200);
  SerialBT.begin(BT_DEVICE_NAME);
  DaisyChain.begin(9600, SERIAL_8N1, rxPin, txPin);
  servo360.attach(servo360Pin);
  Serial.println("Baza setup completed");
}

void loop()
{
  if (Serial.available())
  {
    int serialRead = Serial.read();
    SerialBT.write(serialRead);
  }
  if (SerialBT.available())
  {
    int serialBTRead = SerialBT.read();
    handleBTCommand(serialBTRead);
  }
  delay(20);
}

void handleBTCommand(int command)
{
  Serial.print("Handling command: ");
  Serial.println(command);
  switch (command)
  {

  case '3':
    rotateBack();
    break;

  case '2':
    rotateForward();
    break;

  case '1':
    DaisyChain.println("Hello jedyneczka");
    break;

  case '0':
    DaisyChain.println("Siema zeroweczka");
    break;

  default:
    break;
  }
}

void rotateForward()
{
  rotate(1, 5000);
}

void rotateBack()
{
  rotate(-1, 5000);
}

void rotate(int direction, uint32_t ms)
{
  servo360.writeMicroseconds(neutralPWM + direction * speedPWM);
  delay(ms);
  servo360.writeMicroseconds(neutralPWM);
}