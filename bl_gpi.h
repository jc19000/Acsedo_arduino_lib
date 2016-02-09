#ifndef BL_GPI_H
#define BL_GPI_H

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

class BL_GPI:public BL_Interface {
public:
	BL_GPI(int p_id,int p_period);
	
	void setup(const JsonVariant p_config);
	
	void push(JsonObject& data);
	void get(JsonObject& data);	
	void set(const JsonVariant& data);
	void saveConfig(JsonObject& data);
private:
	void compute();
	int pin;
	int state;
};
#endif

  