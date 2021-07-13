#include <Servo.h>
Servo myservo;

#define VCC_PIN         13
#define TRIGGER_PIN     12    
#define ECHO_PIN        11    
#define GROUND_PIN      10 
#define outputPinMotor  9
#define MAX_DISTANCE    150

// int motorAngle;
int distance;
int shift = 0;
int pos = 0;
boolean spinClockwise = true;

void setup() {
  pinMode(ECHO_PIN,         INPUT) ;  
  pinMode(TRIGGER_PIN,      OUTPUT) ;
  pinMode(GROUND_PIN,       OUTPUT);    
  pinMode(VCC_PIN,          OUTPUT);    
  pinMode(outputPinMotor,   OUTPUT) ;
  
  myservo.attach(outputPinMotor);

  digitalWrite(GROUND_PIN,  LOW) ;
  digitalWrite(VCC_PIN,     HIGH);

}

void loop() {
  distance = getDistance();

  // motorAngle = map(distance, 0, 50, 0, 180);

  shift = 30 - (map(distance, 0, 150, 0, 30));
  
  if(spinClockwise == true && pos + shift > 180)
  {
    spinClockwise = false;
  }
  else if (spinClockwise == false && pos - shift < 0)
  {
    spinClockwise = true;
  }

  if(spinClockwise == true)
  {
    pos += shift;
  }
  else if(spinClockwise == false)
  {
    pos -= shift;
  }
  
  myservo.write(pos);
  delay(50);
}

int getDistance()
{
  int duration;
  float measuredDistance;
  
  digitalWrite(TRIGGER_PIN, LOW);   // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(20);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 12000);
  measuredDistance= duration*0.034/2;       // Calculating the distance

  // if the distance measurement becomes extremely high, it is likely an error.  
  // Default to a maximum value of MAX_DISTANCE to identify this condition.
  if (measuredDistance > MAX_DISTANCE)   
  {
    measuredDistance = MAX_DISTANCE;
  }

  return measuredDistance;
}
