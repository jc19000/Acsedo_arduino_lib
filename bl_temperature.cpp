#include "bl_temperature.h"
#include "ArduinoJson.h"

BL_Temperature::BL_Temperature(int p_id,int p_period):
BL_Interface(p_id,p_period)
{}

void BL_Temperature::setup(const JsonVariant  p_config)
{  
	DEBUG_PRINT("Start bl to DHT sensor!");
	pin=p_config["pin"];
	type=p_config["type"];
	
	dht=new DHT(pin,type);
}

void BL_Temperature::compute(){
	// Reading temperature or humidity takes about 250 milliseconds!--> secured by period
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	h = dht->readHumidity();
	// Read temperature as Celsius (the default)
	t = dht->readTemperature();

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) ) {
		DEBUG_PRINT("Failed to read from DHT sensor!");
		return;
	}
}
	
void BL_Temperature::push(JsonObject& data){	
	compute();
	data["Humidity"] = h;
	data["Temperature"] = t;
}

void BL_Temperature::get(JsonObject& data){
	compute();
	data["Humidity"] = h;
	data["Temperature"] = t;
}	

void BL_Temperature::set(const JsonVariant& data){

}
	
void BL_Temperature::saveConfig(JsonObject& data){
	// {"bl":"DHT","period":2,"type":22,"pin":2}
	data["bl"]="DHT";
	data["period"]=period;
	data["type"]=type;
	data["pin"]=pin;
}

  
