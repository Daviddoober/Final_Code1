int L_CAL = 88;       //the midpoint value that will give a stop
int R_CAL = 89;       //the midpoint value that will give a stop
int SERVO_OFFSET = 5; // USE A SMALL/SLOW VALUE HERE!
int reverse_time = 5000; //tune as needed for 180 turn
int spin_time = 25; //tune as needed
int go_time = 200; //tune as needed
#include <SR04.h>

int TRIG_PIN1 = 2;
int ECHO_PIN1 = 6;
SR04 sr041 = SR04(ECHO_PIN1, TRIG_PIN1);
long VALUE_DIST1;
int TRIG_PIN2 = 8;
int ECHO_PIN2 = 3;
SR04 sr042 = SR04(ECHO_PIN2, TRIG_PIN2);
long VALUE_DIST2;


// Get all your motors declared and the speed commands
#include <Servo.h>     // This calls the Servo library to convert a value to a pulse width
Servo RIGHTservo;      // Right Servo is identified by servo library as variable RIGHTservo
Servo LEFTservo; 
Servo gateservo;
int g_servo_pin = 10;      // Left Servo is identified by servo library as variable LEFTservo
int L_servo_pin = 11;   // HAVE LEFT SERVO SIGNAL FROM DIGITAL 9
int R_servo_pin = 9;  // HAVE RIGHT SERVO SIGNAL FROM DIGITAL 10

// CORRECT THIS TO WHAT YOU HAVE WIRED
        // Declares the RIGHT LED attached to Digital Pin

// CORRECT THIS TO WHAT YOU HAVE WIRED
int QRE_L = A0;     // pin the LEFT QRE is attached to
int QRE_C = A1;     // pin the CENTER QRE is attached to
int QRE_R = A2;     // pin the RIGHT QRE is attached to

// JUST INITIALIZING, NOTHING TO DO HERE
int VALUE_L;       //value for left QRE reading
int VALUE_C;       //value for center QRE reading
int VALUE_R;       //value for right QRE reading

// UPDATE THESE AS NEEDED
int CUTOFF_L = 850; // Value for left QRE cutoff of white vs black
int CUTOFF_C = 900; // Value for center QRE cutoff of white vs black
int CUTOFF_R = 850; // Value for right QRE cutoff of white vs black

void setup() {
  RIGHTservo.attach(R_servo_pin);
  LEFTservo.attach(L_servo_pin);
  gateservo.attach(g_servo_pin);
  gateservo.write(0);
  RIGHTservo.write(R_CAL);  // stop right servo
  LEFTservo.write(L_CAL);   // stop left servo
     // Switch Digital Pin 4 from the default INPUT to OUTPUT (makes LED brighter)
  Serial.begin(9600);            // Begin communciations with the serial monitor
  Serial.println("THIS CLASS SUCKS!");
  int button = digitalRead(13);
  while (button == LOW) {
    button = digitalRead(13);
  }
  delay(1000);
}

void loop() {
  VALUE_DIST1 = sr041.Distance();
  Serial.println(VALUE_DIST1);
  VALUE_DIST2 = sr042.Distance();
  Serial.println(VALUE_DIST2);
  // Need to determine if QRE sensors are detecting a reflectance or not and then automate robot functions
  VALUE_L = analogRead(QRE_L);     // Records the value of the Left QRE sensor
  Serial.print("Left: ");         // Display to serial monitor the value of the Right QRE sensor
  Serial.print(VALUE_L);
  VALUE_C = analogRead(QRE_C);     // Records the value of the Center QRE sensor
  Serial.print("   Center: ");         // Display to serial monitor the value of the Right QRE sensor
  Serial.print(VALUE_C);
  VALUE_R = analogRead(QRE_R);     // Records the value of the Right QRE sensor
  Serial.print("   Right: ");         // Display to serial monitor the value of the Right QRE sensor
  Serial.print(VALUE_R);

  //RIGHT SIDE DARK
  // right sensor high (black) other sensors low (white)
  if (VALUE_DIST1 < 10 && VALUE_DIST1 > 4 && VALUE_DIST2 < 15)
  {
    //Serial.println("Stop");
    //RIGHTservo.write(R_CAL);
    //LEFTservo.write(L_CAL);
    gateservo.write(25);
    delay(100);
    gateservo.write(0);
    if (VALUE_C > CUTOFF_C & VALUE_L < CUTOFF_L)
  {
    // #ROBOTGOALS
    Serial.println("   TURNING RIGHT");
    LEFTservo.write(L_CAL + SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL + SERVO_OFFSET); // turn right wheel

    // let the motors receive the command and move a bit
    delay(spin_time);
  } // end of right side dark

  //LEFT SIDE DARK
  // left sensor high (black) other sensors low (white)
  else if (VALUE_L > CUTOFF_L & VALUE_C < CUTOFF_C)
  {
    // #ROBOTGOALS
    Serial.println("   TURNING LEFT");
    LEFTservo.write(L_CAL - SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL - SERVO_OFFSET); // turn right wheel
    // Turn on LEDs

    // let the motors receive the command and move a bit
    delay(spin_time);
  } // end of left side dark


  //else if (VALUE_L > CUTOFF_L & VALUE_C > CUTOFF_C)
  //{
    
    //Serial.println("   TURNING LEFT 90 degrees");
    //LEFTservo.write(L_CAL - SERVO_OFFSET); //  turn left wheel
    //RIGHTservo.write(R_CAL - SERVO_OFFSET); // turn right wheel

    //delay(1400);
  //} 

  //ALL DARK
  // all sensors high (black)
  else if (VALUE_R > CUTOFF_R & VALUE_L > CUTOFF_L & VALUE_C > CUTOFF_C)
  {
    // #ROBOTGOALS
    Serial.println("   STOP");
    LEFTservo.write(L_CAL); //  turn left wheel
    RIGHTservo.write(R_CAL); // turn right wheel
    // Turn on LEDs
   
    // let the motors receive the command and move a bit
    delay(1500);
  } // end of all dark

  //DRIVE FORWARD
  else if (VALUE_R > CUTOFF_R & VALUE_L < CUTOFF_L & VALUE_C < CUTOFF_C)
  {

    Serial.println("Turn right");
    LEFTservo.write(L_CAL + SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL + SERVO_OFFSET); // turn right wheel

    delay(spin_time);
  } 
  else
  {
    Serial.println("GO STRAIGHT");
    LEFTservo.write(L_CAL + SERVO_OFFSET);
    RIGHTservo.write(R_CAL - SERVO_OFFSET);
    delay(spin_time);
  }
   

  }
  else
  {
  if (VALUE_C > CUTOFF_C & VALUE_L < CUTOFF_L)
  {
    // #ROBOTGOALS
    Serial.println("   TURNING RIGHT");
    LEFTservo.write(L_CAL + SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL + SERVO_OFFSET); // turn right wheel

    // let the motors receive the command and move a bit
    delay(spin_time);
  } // end of right side dark

  //LEFT SIDE DARK
  // left sensor high (black) other sensors low (white)
  else if (VALUE_L > CUTOFF_L & VALUE_C < CUTOFF_C)
  {
    // #ROBOTGOALS
    Serial.println("   TURNING LEFT");
    LEFTservo.write(L_CAL - SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL - SERVO_OFFSET); // turn right wheel
    // Turn on LEDs

    // let the motors receive the command and move a bit
    delay(spin_time);
  } // end of left side dark


  //else if (VALUE_L > CUTOFF_L & VALUE_C > CUTOFF_C)
  //{
    
    //Serial.println("   TURNING LEFT 90 degrees");
    //LEFTservo.write(L_CAL - SERVO_OFFSET); //  turn left wheel
    //RIGHTservo.write(R_CAL - SERVO_OFFSET); // turn right wheel

    //delay(1400);
  //} 

  //ALL DARK
  // all sensors high (black)
  else if (VALUE_R > CUTOFF_R & VALUE_L > CUTOFF_L & VALUE_C > CUTOFF_C)
  {
    // #ROBOTGOALS
    Serial.println("   STOP");
    LEFTservo.write(L_CAL); //  turn left wheel
    RIGHTservo.write(R_CAL); // turn right wheel
    // Turn on LEDs
   
    // let the motors receive the command and move a bit
    delay(1500);
  } // end of all dark

  //DRIVE FORWARD
  else if (VALUE_R > CUTOFF_R & VALUE_L < CUTOFF_L & VALUE_C < CUTOFF_C)
  {

    Serial.println("Turn right");
    LEFTservo.write(L_CAL + SERVO_OFFSET); //  turn left wheel
    RIGHTservo.write(R_CAL + SERVO_OFFSET); // turn right wheel

    delay(spin_time);
  } 
  else
  {
    Serial.println("GO STRAIGHT");
    LEFTservo.write(L_CAL + SERVO_OFFSET);
    RIGHTservo.write(R_CAL - SERVO_OFFSET);
    delay(spin_time);
  }
  }

} //end of main loop
