#include <Arduino.h>
#include <ESP32Servo.h>
#include "HardwareSerial.h"

static const int UART_VERSION = 2; // Using UART2
static const int servo180Pin = 13; // motor pin
static const int rxPin = 16; // reveive pin
static const int txPin = 17; // transmit pin

HardwareSerial DaisyChain(UART_VERSION);
Servo servo180;

void handleCommand(String command);
void rotateForward();
void rotateBack();

void setup()
{
  Serial.begin(115200);
  DaisyChain.begin(9600, SERIAL_8N1, rxPin, txPin);
  servo180.attach(servo180Pin);
}

void loop()
{
  if (DaisyChain.available()) {
    String command = DaisyChain.readStringUntil('\n');
    Serial.println("Received on wozeczek: " + command);
    handleCommand(command);
  }
  delay(100);  // Small delay to avoid overwhelming serial buffer
}

void handleCommand(String command)
{
  command.trim(); // workaround
  Serial.println("Handling command: " + command + ".");
  command.length();
  if (command == "Hello jedyneczka") {
    DaisyChain.println(command);
    rotateForward();
  } else if (command == "Siema zeroweczka") {
    DaisyChain.println(command);
    rotateBack();
  } else {
    Serial.println("Command not recognised");
  }
}

void rotateForward()
{
  for (int posDegrees = 0; posDegrees <= 90; posDegrees++)
  {
    servo180.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}

void rotateBack()
{
  for (int posDegrees = 90; posDegrees >= 0; posDegrees--)
  {
    servo180.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}