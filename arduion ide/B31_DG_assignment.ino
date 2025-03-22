/*
   The code is for the assignment1 of embedded software
   My name is Wenbin Lin, my surname is Lin. 
   For the parameter a, the value maps to 12; 
   For the parameter b, the value maps to 9;
   For the parameter c, the value maps to 13;
   For the parameter d, the value maps to 13;
   For the alternative data output bahavior, the option is 2. The style is gnerating a reversed form of the data waveform (from the largest pulse to the shortest) until the Output Select push button is pressed again.
*/
//Define a debug mode, if in the production mode, the line can be commented out
#define _DEBUG_MODE
//Define different timing values and some other parameters in the debug mode
#ifdef _DEBUG_MODE
  #define SYNC_ON (50*1000)
  #define A (12*100*1000)
  #define ON_INCREMENT (50*1000)
  #define B (9*100*1000)
  #define C (13+4)
  #define D (13*500*1000)
//Define different timing values and some other parameters in the production mode
#else
  #define SYNC_ON 50
  #define A (12*100)
  #define ON_INCREMENT (50)
  #define B (9*100)
  #define C (13+4)
  #define D (13*500)
#endif

// define the enable button pin
#define ENABLE_PIN 16
// define the select button pin
#define SELECT_PIN 17
//define the led pin for the enable signal
#define ENABLE_LED_PIN 27
// define the led pin for the select signal
#define SELECT_LED_PIN 26
// define the debounce time in millisecond for the enable button and select button
#define DEBOUNCE_DELAY 100

//set the starting state of the enable signal to be true
volatile bool enable_state = true;
// set the starting state of the select signal to be true
volatile bool select_state = true;
// set the initial value of the last interrupt time to 0 for deboucing
volatile unsigned long lastEnableInterruptTime = 0;
volatile unsigned long lastSelectInterruptTime = 0;

// Interrupt handler for enable button press
void IRAM_ATTR enable_pressed_handle();
// Interrupt handler for select button press
void IRAM_ATTR select_pressed_handle();

void IRAM_ATTR enable_pressed_handle() {
  unsigned long currentTime = millis();
  if (currentTime - lastEnableInterruptTime > DEBOUNCE_DELAY) {
    // toggle the enable state when the enable button is pressed
    enable_state = !enable_state;
    //update the lastEnableInterruptTime value
    lastEnableInterruptTime = currentTime;
  }
}

void IRAM_ATTR select_pressed_handle() {

  unsigned long currentTime = millis();
  if (currentTime - lastSelectInterruptTime > DEBOUNCE_DELAY) {
    // toggle the enable state when the select button is pressed
    select_state = !select_state;
    //update the lastSelectInterruptTime value
    lastSelectInterruptTime = currentTime;
  }
}


void setup() {
   // Start serial communication, set the baud rate to 115200
  Serial.begin(115200);  
  // Configure enable button as input with pull-down resistor
  pinMode(ENABLE_PIN, INPUT_PULLDOWN);
  // Configure select button as input with pull-down resistor
  pinMode(SELECT_PIN, INPUT_PULLDOWN);
  // Attach interrupt to enable button
  attachInterrupt(digitalPinToInterrupt(ENABLE_PIN), enable_pressed_handle, RISING);
  // Attach interrupt to select button
  attachInterrupt(digitalPinToInterrupt(SELECT_PIN), select_pressed_handle, RISING);
  // Set enable signal LED pin as output
  pinMode(ENABLE_LED_PIN, OUTPUT);
  // set select signal LED pin as output
  pinMode(SELECT_LED_PIN, OUTPUT);
  // Set enable signal LED close at the beginning
  digitalWrite(SELECT_LED_PIN, LOW);
  // Set select signal LED close at the beginning
  digitalWrite(ENABLE_LED_PIN, LOW);
}

void loop() {
  // Condition 1: Both select and enable are ON
  
  if (select_state==true && enable_state == true){
    Serial.println("into condition 1");
    digitalWrite(SELECT_LED_PIN, HIGH);
    delayMicroseconds(SYNC_ON); 
    digitalWrite(SELECT_LED_PIN, LOW);
    for (int i=C;i>0;i--){
      digitalWrite(ENABLE_LED_PIN, HIGH);
      delayMicroseconds(A + ((i-1)*ON_INCREMENT));
      digitalWrite(ENABLE_LED_PIN,LOW);
      delayMicroseconds(B);
    }
    delayMicroseconds(D);
  }
  // Condition 2: Select is false, Enable is true
  else if (select_state == false and enable_state == true){
    Serial.println("into condition 2");
    digitalWrite(SELECT_LED_PIN, LOW);
    for (int i=0;i<C;i++){
      digitalWrite(ENABLE_LED_PIN, HIGH);
      delayMicroseconds(A + (i*ON_INCREMENT));
      digitalWrite(ENABLE_LED_PIN,LOW);
      delayMicroseconds(B);
    }
    delayMicroseconds(D);
  }
  // Condition 3: Select is false, Enable is false
  else if (select_state == false and enable_state == false){
    Serial.println("into condition 3");
    digitalWrite(SELECT_LED_PIN, LOW);
    digitalWrite(ENABLE_LED_PIN, LOW);
    delayMicroseconds(D);
  }
   // Condition 4: Select is true, Enable is false
    else if (select_state == true and enable_state == false){
    Serial.println("into condition 4");
    digitalWrite(SELECT_LED_PIN, HIGH);
    delayMicroseconds(SYNC_ON); 
    digitalWrite(SELECT_LED_PIN, LOW);
    for (int i=0;i<C;i++){
      delayMicroseconds(A + (i*ON_INCREMENT));
      delayMicroseconds(B);
    }
    delayMicroseconds(D);
  }
}

 


