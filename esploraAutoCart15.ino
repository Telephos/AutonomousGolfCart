const int stepPin = 11; // OUT-B, middle pin
const int speedPin = 3; // OUT-A, middle pin
const int dirPin = 15; //right side, 3rd from top
const int enablePin = 16; //right side, 4th from top
const int regPin1 = 8; //right side, 6th from the top
const int regPin2 = 0; //right side, 7th from the top
const int regPin3 = 1; //right side, 8th from the top

#include <Esplora.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(enablePin, OUTPUT); // Stepper motor driver enable
  pinMode(dirPin, OUTPUT);  // Stepper motor direction
  pinMode(stepPin, OUTPUT); // PWM signal for stepper motor speed
  pinMode(stepPin, OUTPUT); // PWM signal for throttle
  pinMode(regPin1, OUTPUT); // Regulator 1 pin, switch 1, down
  pinMode(regPin2, OUTPUT); // Regulator 2 pin, switch 4, right
  pinMode(regPin3, OUTPUT); // Regulator 3 pin, switch 3, up
  
  digitalWrite(enablePin, HIGH); //Set HIGH for broken wire circuit
  digitalWrite(dirPin, HIGH);  // One direction
}

void loop()
{
  int xValue = Esplora.readJoystickX(); // read the joystick's X position
  int yValue = Esplora.readJoystickY(); //read the joystick's Y position
  int L = map(xValue, -512, 512, -125, 125); //Remapping joystick range of values to pwm signal range of values
  int T = map(yValue, 0, 512, 0, 255);
  int bt_1 = Esplora.readButton(SWITCH_DOWN); //Down button to regulator 1
  int bt_2 = Esplora.readButton(SWITCH_RIGHT); //Right button to regulator 2
  int bt_3 = Esplora.readButton(SWITCH_UP); //Up button to regulator 3

  if (xValue > 20){
    digitalWrite(dirPin, LOW);
    analogWrite(stepPin,abs(L)); //Absolute value so correct pwm signal is given if joytsick x axis is negative or postive
    //Esplora.writeRGB(0,0,abs(R));
  }
  else if (xValue < -20){
    digitalWrite(dirPin, HIGH);
    analogWrite(stepPin,abs(L));
    //Esplora.writeRGB(abs(L),0,0);
  }
  else {
    digitalWrite(stepPin, HIGH);
    //analogWrite(stepPin, 5);
    Esplora.writeRGB(0,0,0);
  }

  //Just testing to see if I get the speed here
  if (yValue > 20 || yValue < -20){
    analogWrite(speedPin, abs(T));
    Serial.println(T);
  }

  if(bt_1 == LOW){
    Esplora.writeRGB(0,255,0);
    digitalWrite(regPin1, HIGH);
    delay(1000); //One second of breaking
    digitalWrite(regPin1, LOW);
  }

  if(bt_2 == LOW){
    Esplora.writeRGB(0,255,0);
    digitalWrite(regPin2, HIGH);
    delay(1000); //One second of breaking
    digitalWrite(regPin2, LOW);
  }

  if(bt_3 == LOW){
    Esplora.writeRGB(0,255,0);
    digitalWrite(regPin3, HIGH);
    delay(1000); //One second of breaking
    digitalWrite(regPin3, LOW);
  }
}
