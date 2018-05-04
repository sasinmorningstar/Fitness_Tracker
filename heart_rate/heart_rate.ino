#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
//const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value.
//int PulseSensorPurplePin = 0;                                    
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
//int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore. 


void setup() {   

  Serial.begin(9600);          // For Serial Monitor
  //pinMode(LED13,OUTPUT); 

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  //pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  if (pulseSensor.begin()) {
    //Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
   //Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.

   //Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

   
   /*if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.  
     digitalWrite(LED13,HIGH);          
   } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   } */                                            

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 //Serial.print("BPM: ");                        // Print phrase "BPM: " 
 lcd.print("BPM: ");
 //Serial.println(myBPM);                        // Print the value inside of myBPM. 
 lcd.print(myBPM);
}
  

  delay(20000);                    // considered best practice in a simple sketch.
  lcd.clear();

}

  
