#include "bl_gpi.h"
#include "ArduinoJson.h"

BL_GPI::BL_GPI(int p_id,int p_period):
BL_Interface(p_id,p_period)
{}

void BL_GPI::setup(const JsonVariant  p_config)
{  
	DEBUG_PRINT("Start bl to gpi");
	pin=p_config["pin"];
	state=p_config["default"];
	pinMode(pin, INPUT);
}

void BL_GPI::compute(){
	state = digitalRead(pin);
}

void BL_GPI::push(JsonObject& data){	
	compute();
	data["State"] = state;
}

void BL_GPI::get(JsonObject& data){
	compute();
	data["State"] = state;
}	

void BL_GPI::set(const JsonVariant& data){

}
	
void BL_GPI::saveConfig(JsonObject& data){
	// {"bl":"GPI","period":4,"pin":3,"default":false}
	data["bl"]="GPI";
	data["period"]=period;
	data["pin"]=pin;
	data["default"]=state;
}
  
