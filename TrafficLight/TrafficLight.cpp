#include "TrafficLight.h"

void TrafficLight::init() {
   for(int i=0; i<3; i++) {     
     pinMode(this->pins[i], OUTPUT);
   }
 }

TrafficLight::TrafficLight(byte redPin, byte yellowPin, byte greenPin) {
   this->pins[RED] = redPin;
   this->pins[YELLOW] = yellowPin;
   this->pins[GREEN] = greenPin;
   this->init();
 }
 
bool TrafficLight::GetState(int color) {
   return this->states[color];
 }

bool* TrafficLight::GetStates() {
   return this->states;
 }
 
void TrafficLight::Toggle(int color) {
   this->states[color] = !this->states[color];
   if(this->states[color]) {
     digitalWrite(this->pins[color], HIGH);
   } else {
     digitalWrite(this->pins[color], LOW);
   }
 }
 
void TrafficLight::TurnOn(int color) {
   if(!this->states[color]) {
     this->Toggle(color);
   }
 }
 
void TrafficLight::TurnOff(int color) {
   if(this->states[color]) {
     this->Toggle(color);
   }
 }
 
void TrafficLight::Go() {
   this->TurnOff(YELLOW);
   this->TurnOff(RED);
   this->TurnOn(GREEN);
 }
 
void TrafficLight::Careful() {
   this->TurnOff(RED);
   this->TurnOff(GREEN);
   this->TurnOn(YELLOW);
 }
 
void TrafficLight::Stop() {
   this->TurnOff(YELLOW);
   this->TurnOff(GREEN);
   this->TurnOn(RED);
 }

 void TrafficLight::Down()
 {
   this->TurnOff(YELLOW);
   this->TurnOff(GREEN);
   this->TurnOff(RED);
 }

 void TrafficLight::AllUp(){
   this->TurnOn(YELLOW);
   this->TurnOn(GREEN);
   this->TurnOn(RED);
 }
