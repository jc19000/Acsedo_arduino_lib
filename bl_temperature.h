#ifndef BL_TEMPERATURE_H
#define BL_TEMPERATURE_H

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

class BL_Temperature:public BL_Interface {
public:
	BL_Temperature(int p_id,int p_period);
	
	void setup(const JsonVariant p_config);
	
	void push(JsonObject& data);
	void get(JsonObject& data);	
	void set(const JsonVariant& data);
	void saveConfig(JsonObject& data);
private:

	void compute();
	float h;
	float t;
	int pin;
	int type;
	
	DHT *dht;
};
#endif

  