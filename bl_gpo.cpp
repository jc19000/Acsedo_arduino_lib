#include "bl_gpo.h"
#include "ArduinoJson.h"

BL_GPO::BL_GPO(int p_id,int p_period):
BL_Interface(p_id,p_period)
{}

void BL_GPO::setup(const JsonVariant  p_config)
{  
	DEBUG_PRINT("Start bl to gpo!");
	pin=p_config["pin"];
	pinMode(pin, OUTPUT);
	state=p_config["default"];
	digitalWrite(pin, state); 
}



void BL_GPO::push(JsonObject& data){	
	data["State"] = state;
}

void BL_GPO::get(JsonObject& data){
	data["State"] = state;
}	

void BL_GPO::set(const JsonVariant& data){
	state=data["state"];
	digitalWrite(pin, state);
}
	
void BL_GPO::saveConfig(JsonObject& data){
	// {"bl":"GPO","period":30,"pin":4,"default":false}
	data["bl"]="GPO";
	data["period"]=period;
	data["pin"]=pin;
	data["default"]=state;
}
  
