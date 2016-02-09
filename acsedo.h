#ifndef BL_ACSEDO_H
#define BL_ACSEDO_H

#include "ArduinoJson.h"
#include "Arduino.h"

#include "DHT.h"
#include "bl_temperature.h"
#include "bl_gpi.h"
#include "bl_gpo.h"
#include "bl_pwm.h"
#include "bl_stepbystep.h"
#include "FS.h"


#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>


// Define where debug output will be printed.
#define DEBUG_PRINTER Serial
#define WebSocketClientEvent Acsedo::webSocketEvent

// Setup debug printing macros.
#ifdef DHT_DEBUG
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

class Acsedo: public WebSocketsClient{

public:
	void setup();
	void loop();
private:
	void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght);
	
	void saveConfig();
	void sendData(const String& data);
	String encrypt(String data);
	String decrypt(String data);
	
	ESP8266WiFiMulti WiFiMulti;
	WebSocketsClient webSocket;
	
	const char* ssid;
	const char* password;

	String startOfFrame;
	String endOfFrame;

	int pushingPeriod;
	int serialSpeed;

	const char* websocketUrl;
	int websocketPort;
	const char* websocketPath;

	BL_Interface* bls[4];
	int bl_number=0;

	int id=0;
	const char* type="";
	
	int cpt=0;
	
	const char* privateKey;
	const char* publicKey;
};
#endif
