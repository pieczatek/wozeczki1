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
static const int rxPin = 16; // reveive pin
static const int txPin = 17; // transmit pin

BluetoothSerial SerialBT;
HardwareSerial DaisyChain(UART_VERSION);
//Servo servo360;

void handleCommand(int command);

void setup()
{
  Serial.begin(115200);
  SerialBT.begin(BT_DEVICE_NAME);
  DaisyChain.begin(9600, SERIAL_8N1, rxPin, txPin);
  //servo360.attach(servo360Pin);
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
    handleCommand(serialBTRead);
  }
  delay(20);
}

void handleCommand(int command)
{
  Serial.print("Handling command: ");
  Serial.println(command);
  switch (command)
  {
  case '1':
    DaisyChain.print(command);
    break;

  case '0':
    DaisyChain.print(command);
    break;

  default:
    break;
  }
}