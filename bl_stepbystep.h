#ifndef BL_STEPBYSTEP_H
#define BL_STEPBYSTEP_H

#include "bl_interface.h"
#include "DHT.h"

#include "Arduino.h"
#include "ArduinoJson.h"

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef DHT_DEBUG
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

class BL_StepByStep:public BL_Interface {
public:
	BL_StepByStep(int p_id,int p_period);
	
	void setup(const JsonVariant p_config);
	
	void push(JsonObject& data);
	void get(JsonObject& data);	
	void set(const JsonVariant& data);
	void saveConfig(JsonObject& data);
private:
	void doSteps(bool inc,int number);

	void doStep(bool inc);

	int step=0;

	int pin1;
	int pin2;
	int pin3;
	int pin4;
  
	bool steps1[8] = {0,0,0,0,0,1,1,1};
	bool steps2[8] = {0,0,0,1,1,1,0,0};
	bool steps3[8] = {0,1,1,1,0,0,0,0};
	bool steps4[8] = {1,1,0,0,0,0,0,1};
};
#endif

  