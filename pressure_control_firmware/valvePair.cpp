#include "valvePair.h"
#include <Arduino.h>
#include "allSettings.h"


valvePair::valvePair(int pin1, int pin2){
  pinPressure=pin1;
  pinVent=pin2;
}




void valvePair::initialize(int pin1, int pin2){
  pinPressure=pin1;
  pinVent=pin2;
  pinMode(pinPressure, OUTPUT);
  digitalWrite(pinPressure, LOW);
  pinMode(pinVent, OUTPUT);
  digitalWrite(pinVent, LOW);
}



void valvePair::initialize(){
  pinMode(pinPressure, OUTPUT);
  digitalWrite(pinPressure, LOW);
  pinMode(pinVent, OUTPUT);
  digitalWrite(pinVent, LOW);
}


void valvePair::setSettings(valveSettings &newSettings){

  offset_p = newSettings.valveOffset[0];
  offset_v = newSettings.valveOffset[1];
  outMax_p = newSettings.valveMax[0];
  outMax_v = newSettings.valveMax[1];
  

  outRange_p=outMax_p-offset_p;
  outRange_v=outMax_v-offset_v;
}


//Digital valves

void valvePair::pressureValveOn(){
  digitalWrite(pinPressure, HIGH);  
}

void valvePair::pressureValveOff(){
  digitalWrite(pinPressure, LOW);  
}

void valvePair::ventValveOn(){
  digitalWrite(pinVent, HIGH);  
}

void valvePair::ventValveOff(){
  digitalWrite(pinVent, LOW);  
}


//Analog valves
void valvePair::pressureValveAnalog(int val){
  analogWrite(pinPressure, val);
}

void valvePair::ventValveAnalog(int val){
  analogWrite(pinVent, val);
}


void valvePair::pressurize(){
  ventValveOff();
  pressureValveOn();
}

void valvePair::pressurizeProportional(float val){
  ventValveAnalog(0);
  float set1=mapFloat(val,0.0,1.0,0.0,float(outRange_p));
  int set = constrain(set1+ offset_p, 0, 255);
  pressureValveAnalog(set);
}


void valvePair::vent(){
  pressureValveOff();
  ventValveOn(); 
}

void valvePair::ventProportional(float val){
  pressureValveAnalog(0);
  float set1=mapFloat(val,0.0,1.0,0.0,float(outRange_v));
  int set = constrain(set1+ offset_v, 0, 255);
  ventValveAnalog(set);
}





void valvePair::idle(){
  pressureValveAnalog(0);
  ventValveAnalog(0);
}



float valvePair::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




//Update controller settings
void valvePair::go(float act_in){
  //Serial.print(act_in);
  //Serial.print('\t');

  //Check for saturation
 /* if (act_in == 0.0 || act_in == -1.0){
    vent();
  }
  else if (act_in == 1.0){
    pressurize();
  }
  //Otherwise, vent proportionally
  else{
  */
  //Serial.print(act_in);
  //Serial.print('\t');
    if (act_in <0.0){
      ventProportional(abs(act_in));
    }
    else if(act_in ==0.0){
      idle();
    }
    else{
      pressurizeProportional(abs(act_in));
    }
}
