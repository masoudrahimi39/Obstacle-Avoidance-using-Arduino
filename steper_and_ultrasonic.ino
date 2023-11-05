// ---------------------------------------------------------------------------
// This example shows how to use NewPing's ping_timer method which uses the Timer2 interrupt to get the
// ping time. The advantage of using this method over the standard ping method is that it permits a more
// event-driven sketch which allows you to appear to do two things at once. An example would be to ping
// an ultrasonic sensor for a possible collision while at the same time navigating. This allows a
// properly developed sketch to multitask. Be aware that because the ping_timer method uses Timer2,
// other features or libraries that also use Timer2 would be effected. For example, the PWM function on
// pins 3 & 11 on Arduino Uno (pins 9 and 10 on Arduino Mega) and the Tone library. Note, only the PWM
// functionality of the pins is lost (as they use Timer2 to do PWM), the pins are still available to use.
// NOTE: For Teensy/Leonardo (ATmega32U4) the library uses Timer4 instead of Timer2.
// ---------------------------------------------------------------------------
#include <NewPing.h>
#include <Unistep2.h>

// Ultrasonic
#define TRIGGER_PIN_1   42 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_1      43 // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN_2   28 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_2      29 // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN_3   9  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN_3      8 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE    100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar_3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned int pingSpeed2 = 50;
unsigned int pingSpeed3 = 50;
unsigned long pingTimer;     // Holds the next ping time.
unsigned long pingTimer2;
unsigned long pingTimer3;

int distance1 = 0;
int distance2 = 0;
int distance3 = 0;

// Steper motor
// Define some steppers and the pins they will use
Unistep2 stepper1(3, 4, 5, 6, 2038, 2000); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)
Unistep2 stepper2(10, 11, 12, 13, 2038, 2000); // left one


void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pingTimer = millis(); // Start now.
}


void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar_1.ping_timer(echoCheck_1);
    int distance1 = sonar_1.ping_result / US_ROUNDTRIP_CM;
  }

  if (millis() >= pingTimer3) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer3 += pingSpeed3;      // Set the next ping time.
    sonar_3.ping_timer(echoCheck_3);
    int distance3 = sonar_3.ping_result / US_ROUNDTRIP_CM;
  }

  // Do other stuff here, really. Think of it as multi-tasking.

  int th1 = 10;
//  drive(3, 2000);

  stepper1.run();
  stepper2.run();


if (distance1 >= th1 && distance3 >= th1) {
  Serial.println("go straight ");
    drive(1, 200);
}
if (distance1 <= th1 && distance3 <= th1) {
  Serial.println("backward ");
    drive(5, 0);
}else {
  Serial.println(" goooo ");
  drive(1, 200);
    // Handle the case when no conditions are met.
}
  
}





void drive(int direction, int step){
  if (direction == 3){      // move left
    stepper1.move(step);
    stepper2.move(step);
    } 
    
    else if(direction == 1){ // move straight
      stepper1.move(step);
      stepper2.move(-1*step);
      }
      
  else if(direction == 2){  // move right
    stepper1.move(-1*step);
    stepper2.move(-1*step);
      }
  if (direction == -3){      // move backward left
    stepper1.move(-1*step);
    stepper2.move(-1*step);
    } 

  if (direction == -2){      // move backward right
    stepper1.move(step);
    stepper2.move(step);
    } 
  else if (direction == -1){  // move backward
    stepper1.move(-1*step);
    stepper2.move(step);
    }
    else if (direction == 5){
     stepper2.stop();
     stepper1.stop();
    }
  else {
    }
  
  }


void echoCheck_1() {
  if (sonar_1.check_timer()) {
    distance1 = sonar_1.ping_result / US_ROUNDTRIP_CM;
    Serial.print("Ping 1: ");
    Serial.print(sonar_1.ping_result / US_ROUNDTRIP_CM);
    Serial.println("cm");
}}

//void echoCheck_2() {
//  if (sonar_2.check_timer()) {
////    distance2 = sonar_2.ping_result / US_ROUNDTRIP_CM;
//    Serial.print("Ping 2: ");
//    Serial.print(sonar_2.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
////    Serial.println("cm");
//  }
//}


void echoCheck_3() {
  if (sonar_3.check_timer()) {
    distance3 = sonar_3.ping_result / US_ROUNDTRIP_CM;
    Serial.print("Ping 3: ");
    Serial.print(sonar_3.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.println("cm");
  }
}
