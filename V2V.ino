#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

// MOSFET
#define HA 25
#define LA 26
#define HB 27
#define LB 14

// RELAY
#define RELAY_A 19
#define RELAY_B 18

#define RELAY_ON LOW
#define RELAY_OFF HIGH

// ADC
#define VA_PIN 34
#define VB_PIN 35

#define VOLT_SCALE 5.6

// SWITCHING
#define HALF_PERIOD 25
#define DEADTIME 2

// SETTINGS
const float DIFF_THRESHOLD = 0.2;
const float ZERO_THRESHOLD = 1.0;

// STATE MACHINE
int state = 0;

unsigned long stateTimer = 0;

const unsigned long WAIT_TIME = 10000;   // 10 sec
const unsigned long CHARGE_TIME = 300000; // 5 min

float VA = 0;
float VB = 0;

String direction="STOP";

// -------------------------------------------------

float readVoltage(int pin)
{
 float sum=0;

 for(int i=0;i<20;i++)
 {
  sum+=analogRead(pin);
  delayMicroseconds(200);
 }

 return (sum/20.0)*(3.3/4095.0)*VOLT_SCALE;
}

// -------------------------------------------------

int voltageToSOC(float v)
{
 float minV=10.5;
 float maxV=12.6;

 if(v<=minV) return 0;
 if(v>=maxV) return 100;

 return (int)(((v-minV)/(maxV-minV))*100.0);
}

// -------------------------------------------------

void setup()
{
 Serial.begin(115200);

 pinMode(HA,OUTPUT);
 pinMode(LA,OUTPUT);
 pinMode(HB,OUTPUT);
 pinMode(LB,OUTPUT);

 pinMode(RELAY_A,OUTPUT);
 pinMode(RELAY_B,OUTPUT);

 digitalWrite(RELAY_A,RELAY_OFF);
 digitalWrite(RELAY_B,RELAY_OFF);

 stopAll();

 lcd.init();
 lcd.backlight();

 lcd.print("DAB BALANCER");

 stateTimer = millis();
}

// -------------------------------------------------

void loop()
{

// ---------------- STATE 0 (WAIT 10 SEC) ----------------

if(state==0)
{

 digitalWrite(RELAY_A,RELAY_OFF);
 digitalWrite(RELAY_B,RELAY_OFF);

 stopAll();

 if(millis()-stateTimer>WAIT_TIME)
 {
   state=1;
   stateTimer=millis();
 }

}

// ---------------- STATE 1 (CHECK VOLTAGE) ----------------

else if(state==1)
{

 VA = readVoltage(VA_PIN);
 VB = readVoltage(VB_PIN);

 digitalWrite(RELAY_A,RELAY_ON);
 digitalWrite(RELAY_B,RELAY_ON);

 if(VA > VB + DIFF_THRESHOLD)
 direction="A>B";

 else if(VB > VA + DIFF_THRESHOLD)
 direction="B>A";

 else
 direction="STOP";

 state=2;
 stateTimer=millis();
}

// ---------------- STATE 2 (CHARGING) ----------------

else if(state==2)
{

 if(direction=="A>B")
 runBridgeA();

 else if(direction=="B>A")
 runBridgeB();

 else
 stopAll();

 // refresh voltage display
 VA = readVoltage(VA_PIN);
 VB = readVoltage(VB_PIN);

 // after 5 minutes restart check
 if(millis()-stateTimer>CHARGE_TIME)
 {
   state=1;
   stateTimer=millis();
 }

}

// LCD update
updateLCD();

}

// -------------------------------------------------

void runBridgeA()
{

 digitalWrite(HB,LOW);
 digitalWrite(LB,LOW);

 digitalWrite(HA,HIGH);
 digitalWrite(LA,LOW);
 delayMicroseconds(HALF_PERIOD-DEADTIME);

 digitalWrite(HA,LOW);
 delayMicroseconds(DEADTIME);

 digitalWrite(LA,HIGH);
 delayMicroseconds(HALF_PERIOD-DEADTIME);

 digitalWrite(LA,LOW);
 delayMicroseconds(DEADTIME);
}

// -------------------------------------------------

void runBridgeB()
{

 digitalWrite(HA,LOW);
 digitalWrite(LA,LOW);

 digitalWrite(HB,HIGH);
 digitalWrite(LB,LOW);
 delayMicroseconds(HALF_PERIOD-DEADTIME);

 digitalWrite(HB,LOW);
 delayMicroseconds(DEADTIME);

 digitalWrite(LB,HIGH);
 delayMicroseconds(HALF_PERIOD-DEADTIME);

 digitalWrite(LB,LOW);
 delayMicroseconds(DEADTIME);
}

// -------------------------------------------------

void stopAll()
{

 digitalWrite(HA,LOW);
 digitalWrite(LA,LOW);
 digitalWrite(HB,LOW);
 digitalWrite(LB,LOW);

}

// -------------------------------------------------

void updateLCD()
{

 lcd.clear();

 lcd.setCursor(0,0);
 lcd.print("A:");
 lcd.print(VA,2);
 lcd.print("V ");
 lcd.print(voltageToSOC(VA));
 lcd.print("%");

 lcd.setCursor(0,1);
 lcd.print("B:");
 lcd.print(VB,2);
 lcd.print("V ");
 lcd.print(voltageToSOC(VB));
 lcd.print("%");

 lcd.setCursor(0,2);

 if(state==0)
 lcd.print("MODE: WAIT");

 else if(state==1)
 lcd.print("MODE: CHECK");

 else
 lcd.print("MODE: CHARGE");

 lcd.setCursor(0,3);
 lcd.print("DIR: ");
 lcd.print(direction);
}