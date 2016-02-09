#include "bl_pwm.h"
#include "ArduinoJson.h"

BL_PWM::BL_PWM(int p_id,int p_period):
BL_Interface(p_id,p_period)
{}

void BL_PWM::setup(const JsonVariant  p_config)
{  
	DEBUG_PRINT("Start bl to PWM!");
	pin=p_config["pin"];
	analogWriteFreq(500);
	pinMode(pin, OUTPUT);
	
	pwm=p_config["pwm"];
	analogWrite(pin, pwm);
}



void BL_PWM::push(JsonObject& data){	
	data["State"] = pwm;
}

void BL_PWM::get(JsonObject& data){

}	

void BL_PWM::set(const JsonVariant& data){
	int tmp=data["pwm"];
	if(min<=tmp && max>=tmp){
		pwm=tmp;
		analogWrite(pin, pwm);
	}
}
	
void BL_PWM::saveConfig(JsonObject& data){
	// {"bl":"PWM","period":30,"pin":4,"pwm":500,"max":1024,"min":360},
	data["bl"]="PWM";
	data["period"]=period;
	data["pin"]=pin;
	data["pwm"]=pwm;
	data["max"]=max;
	data["min"]=min;
}
  
