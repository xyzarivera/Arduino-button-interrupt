/* Single Press and Double Press Button Interrupts
   Xyza Rivera
   20180223

   This code performs Single Press and Double Press Button Interrupts.

   Hardware:
   - Arduino (I used Uno for my setup)
   - 2 LEDs
   - push button
   - 1000 ohm resistor

   Pseudocode:
    
   Single Press:
    - Turns on/off LEDs
   Double Press:
    - Executes double press function
   
   Uses ISR (Interrupts) when button in pressed
   Reg1,Reg2            <- Used as condition flags
   flag                 <- Used as state flag
   time1, time2         <- Used as time variables

   switch(flag)
   case 0 : turns off LEDs, basically to turn off a separate system
   case 1 : turns on LEDS, basically to turn on a separate sytem
   case 2 : conditions for single press or double press
   case 3 : executes double press function
      for this code, it turns on LED1 and turns off LED2

   EXECUTION:
   
   At bootup
    - LEDs off
    - Reg 1, Reg 2 = 0
    - time1, time2 = 0
    - executes loop()
   
   At first single button press:
    - ISR executes
    - satisfies first if condition
    -- flag = 1
    - returns to loop ()
    -- satisfies case 1 in switch(flag) function
    --- 2 LEDs will turn ON
    --- Reg 1 = 1
    - returns to loop ()
   
   When flag = 1 and pressed twice within 1 second interval
    - ISR executes on 1st press
    - satisfies 2nd if condition
    -- gets time1 = current time of execution in micro sec
    -- flag = 2
    - returns to loop()
    -- satisfies case 2 in switch(flag) function
    --- Reg2 = 1
    --- does not satisfies if statement (current time must be time1 +2 sec)
    - returns to loop
    - ISR executes on 2nd press
    - satisfies 3rd if condition
    -- time2 =  current time of execution in microsec
    -- flag = 3
    - returns to loop()
    -- satisfies case 3 in switch(flag) function
    --- satisfies if condtion
    ---- LED1 on, LED2 off
    ---- Reg1, flag = 1
    ---- Reg2, time1, time2 = 0
    ---- INSERT DOUBLE PRESS FUNCTION YOU WISH TO EXECUTE
    ---- delays for 1.5 sec
    - returns to loop()
    - satisfies case 1 in switch(flag) function
    -- executes case 1 until next interrupt
    
   When pressed once after 1st single button press
    - ISR executes
    - satisfies 2nd if condition
    -- gets time1 = current time of execution in micro sec
    -- flag = 2
    - returns to loop()
    -- satisfies case 2 in switch(flag) function
    --- Reg2 = 1
    --- does not satisfies if statement (current time must be time1 +2 sec)
    - returns to loop
    - no interrupt occured (2nd press specifically)
    -- satisfies case 2 in switch(flag) function
    --- Reg2 = 1
    --- satisfies if statement (current time must be time1 +2 sec)
    ---- Reg1, Reg2, flag= 0 
    - returns to loop    
    - satisfies case 0 in switch(flag) function
    -- Reg1, Reg2, time1 time2 = 0
    -- executes case 0 until next interrupt

*/

