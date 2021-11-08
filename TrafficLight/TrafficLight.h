#include "Arduino.h"
#ifndef TrafficLights_h
#define TrafficLights_h
#define byte uint8_t
// enumerate the color names to be more readable
enum color {GREEN, YELLOW, RED};

class TrafficLight {
  public:
    TrafficLight(byte redPin, byte yellowPin, byte greenPin);
    void Toggle(int color);
    void TurnOff(int color);
    void TurnOn(int color);
    void Go();
    void Careful();
    void Stop();
    void Down();
    void AllUp();
    bool GetState(int color);
    bool* GetStates();
  private:
    byte pins[3];
    bool states[3]={0}; 
    void init();
};
#endif
