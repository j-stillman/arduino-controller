#include "Keyboard.h"         // Allows for keyboard simulation

#define NUM_BUTTONS 3
#define JOY_X A0
#define JOY_Y A1
#define JOY_BUTTON 2          // NOTE: I think my joystick is defective or something. I can't get the button to work right
#define JOY_MAX 660           // NOTE: I don't know why, but my joystick stopped giving values between 0 and 1023. Here's a workaround...

// These values are the thresholds for whether the potentiometer on the joystick is high or low
// enough to be considered "held" in that direction
const int JOY_LOW = JOY_MAX / 4;
const int JOY_HIGH = 3 * (JOY_MAX / 4);

#define LED_R 9
#define LED_G 10
#define LED_B 11
#define LED_ON 10

// Define arrays that hold button state info and which buttons are mapped to which keys
// Note: J, L, and K are arbitrary choices kind of. For some reason, holding shift to sprint through the Arduino
// doesn't work. But it does for most other keys.
const int buttonKey[] = { 'J', 'L', 'K' };
const int buttonPin[] = { 3, 4, 5 };
bool buttonState[] = { false, false, false };

const int joyKey[] = { KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW };
bool joyStickState[] = { false, false, false, false };
int xVal = 0;
int yVal = 0;
bool joyButtonPressed = false;

bool serialLights = true; // whether we are turning on lights from processing or just whenever we are holding a button
bool buttonLights = false;

void setup() {

  // Set up the push button pins to take in input
  for(int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPin[i], INPUT);
  }

  // The joystick button is treated like a regular button
  pinMode(JOY_BUTTON, INPUT);
  
  // initialize control over the keyboard:
  Keyboard.begin();
    
}

void loop() {

  /* ========================================================================================== */
  /* PERFORM HARDWARE READINGS ================================================================ */

  // Set whether the buttons are being pressed
  setButtonStates();

  // Read the coordinates of the joystick, and see if the button's been pressed
  xVal = analogRead(JOY_X);
  yVal = analogRead(JOY_Y);
  joyButtonPressed = (digitalRead(JOY_BUTTON) == HIGH);

  // Set the array values for joyStickState based on xVal, yVal
  setJoyStickStates();

   
  /* ========================================================================================== */
  /* HANDLE BUTTONS =========================================================================== */

  // Go through for each button and press the keys if the button is pressed
  for(int i = 0; i < NUM_BUTTONS; i++) {

    // Simply hold the corresponding key if the button has been pressed.
    if (buttonState[i] == true) {

      Keyboard.press(buttonKey[i]);

    }else{

      Keyboard.release(buttonKey[i]);
      
    }

  }


  /* ========================================================================================== */
  /* HANDLE JOYSTICK ========================================================================== */

  // Now determine if we should press or release the arrow keys based off the joy directions
  for(int i = 0; i < 4; i++) {

    // Handle just general holding of direction
    if (joyStickState[i] == true) {

      Keyboard.press(joyKey[i]);
      
    }else{

      Keyboard.release(joyKey[i]);
      
    }
    
  }


  /* ========================================================================================== */
  /* TURN ON LEDS ============================================================================= */  

  if (serialLights) {
    
    // Update the LEDs from the serial port
    updateLeds();
  
  }else if (buttonLights) {

    // Just turn on the corresponding light when a button is pressed
    analogWrite(LED_R, LED_ON * buttonState[0]);
    analogWrite(LED_G, LED_ON * buttonState[1]);
    analogWrite(LED_B, LED_ON * buttonState[2]);
      
  }
  
}


// Function that sets all the button states so we can check them for presses later.
void setButtonStates()
{ 
  
  for(int i = 0; i < NUM_BUTTONS; i++) {

    buttonState[i] = (digitalRead(buttonPin[i]) == HIGH);
    
  }
  
}// end setButtonStates()


// Function that sets all the joy stick states. The order of the array goes { left, right, up, down }
// Depending on what orientation the joy stick is set, we'll probably need to recode this part
void setJoyStickStates()
{

  // Set each array element to true based on whether joyX or joyY is above or below a certain threshold
  joyStickState[0] = (yVal > JOY_HIGH);
  joyStickState[1] = (yVal < JOY_LOW);
  joyStickState[2] = (xVal > JOY_HIGH);
  joyStickState[3] = (xVal < JOY_LOW);
  
}// end setJoyStickStates()


// Function that sets the pin values to high or low depending on what's coming through the serial port
void updateLeds()
{

  for(int i = 0; i < 3; i++) {

    int pin = -1;
    char val = ' ';
    
    if (Serial.available()) {
      
      val = Serial.read();

      switch(val) {
        
        case 'R': pin = LED_R; break;
        case 'G': pin = LED_G; break;
        case 'B': pin = LED_B; break; 
        case 'r': pin = LED_R; break;
        case 'g': pin = LED_G; break;
        case 'b': pin = LED_B; break; 
        default: break;
        
      }
      
    }
    
    if (pin != -1) {

      // If it received a capital letter, then turn it on. Lowercase turns it off
      if (isupper(val)) {
        analogWrite(pin, LED_ON);
      }else{
        analogWrite(pin, 0);
      }
      
    }
    
  }
  
}// end updateLeds()
 
