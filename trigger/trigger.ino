int inPin0 = 8;
int inPin1 = 9;
int inPin2 = 10;

int val0 = 0;
int val1 = 0;
int val2 = 0;
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 13
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
//const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
int Signal;



void setup()
{
  pinMode(inPin0 ,INPUT);
  pinMode(inPin1 ,INPUT);
  pinMode(inPin2 ,INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
  //lcd.print("beFit!");
  // start serial port
  
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();   

  //Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
//  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    
    //Serial.println("pulseObject created !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
      
  }
}




void loop()
{
  val0 = digitalRead(inPin0);
  val1 = digitalRead(inPin1);
  val2 = digitalRead(inPin2);
  if(val0==HIGH && val1==LOW && val2==LOW)
  {
    //lcd.print("place your finger");
    //delay(2000);
    //lcd.clear();
    //delay(5000);
    int myBPM = pulseSensor.getBeatsPerMinute(); 
    if (pulseSensor.sawStartOfBeat()){
    //int myBPM = pulseSensor.getBeatsPerMinute();  
    lcd.print("BPM:");
    lcd.println(myBPM);
    
    delay(5000);
    lcd.clear();
    }

    
  }
  else if(val0==LOW && val1==HIGH && val2==LOW)
  {
    sensors.requestTemperatures();
    lcd.print("Temp is: ");
    lcd.print(sensors.getTempFByIndex(0));
    delay(5000);
    lcd.clear();


  }
 /* if(val2==0)
  {

    
  }*/
  else
  {
    lcd.print("beFit");
    delay(5000);
    lcd.clear();
    //delay(5000);
    
  }



}

