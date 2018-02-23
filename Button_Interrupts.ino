/* Single Press and Double Press Button Interrupts
 * Xyza Rivera
 * 20180223
 */

const int buttonPin = 2;     // pushbutton pin
const int ledPin1 =  5;      // LED pin 1
const int ledPin2 =  6;      // LED pin 2

// variables will change:
volatile byte Reg1 = 0;        // variable for 1st Condition
volatile byte Reg2 = 0;        // variable for 2nd Condition
volatile byte flag = 0;        // variable for state flagging 
unsigned long time1, time2;    // variable for time

void setup() {
  Serial.begin (9600);

  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, CHANGE);
}

void loop() {
  // print commands can be disregarded
  Serial.print("Reg1 = ");
  Serial.println(Reg1);
  Serial.print("Reg2 = ");
  Serial.println(Reg2);
  Serial.print("time1 = ");
  Serial.println(time1);
  Serial.print("time2 = ");
  Serial.println(time2);
  Serial.println("----------------- ");

  switch (flag) {
    case 0:
    // Turns off both LEDs and Resets conditions and time var
      Serial.println("Flag 0");
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      Reg1, Reg2 = 0;
      time1, time2 = 0;
      break;
    case 1:
    // Turns on both LEDs and toggles Reg1 to active
      Serial.println("Flag 1");
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      Reg1 = 1;
      Reg2 = 0;
      break;
    case 2:
    // Toggles Reg2 to active
    // Turns off both LEDs and resets conditions and time var if no button interrupt occurs within 2 seconds
      Serial.println("Flag 2");
      Reg2 = 1;
      if (micros() - time1 >= 2000000) {
        Reg1 = 0;
        Reg2 = 0;
        flag  = 0;
        Serial.println("Shutting Down");
      }
      break;
    case 3:
    // Executes code for double press function if 2nd press is executed within 1 second
    // Else, returns flag = 1 / returns to case 1
      if ((time2 - time1) < 1005000) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        flag = 1;
        Reg1 = 1;
        Reg2 = 0;
        time1, time2 = 0;
        Serial.println("Double Press Function");
        // INSERT Double Press CODE
        delay(1500);
      }
      break;
  }
  delay(500);
}

void pin_ISR() {
  // ISR code: Follows the following conditions to execute single press and double press functions
  if (Reg1 == 0 && Reg2 == 0) {
    flag = 1;
  }
  else if (Reg1 == 1 && Reg2 == 0) {
    time1 = micros();
    flag = 2;
  }
  else if (Reg1 == 1 && Reg2 == 1) {
    time2 = micros();
    flag = 3;
  }
}
