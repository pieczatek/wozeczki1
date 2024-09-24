
/*


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


*/