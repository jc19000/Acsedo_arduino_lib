#include "bl_stepbystep.h"
#include "ArduinoJson.h"

BL_StepByStep::BL_StepByStep(int p_id,int p_period):
BL_Interface(p_id,p_period)
{}

void BL_StepByStep::doStep(bool inc){
    digitalWrite(pin1, steps1[step]); 
    digitalWrite(pin2, steps2[step]); 
    digitalWrite(pin3, steps3[step]); 
    digitalWrite(pin4, steps4[step]); 
    if(inc){
      step++;
    }else{
      step--;
    }
    
   
    if(step>8){
       step=0;
    }else if(step<0){
      step=8;
    }
}

void BL_StepByStep::doSteps(bool inc,int number){
   for(int i=0;i<number;i++){
    doStep(inc);
    delay(1);
   }
}

void BL_StepByStep::setup(const JsonVariant  p_config)
{  
	DEBUG_PRINT("Start bl to stepbystep!");
	pin1=p_config["pin1"];
	pin2=p_config["pin2"];
	pin3=p_config["pin3"];
	pin4=p_config["pin4"];
	
	pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}



void BL_StepByStep::push(JsonObject& data){	
	data["step"]=step;
}

void BL_StepByStep::get(JsonObject& data){
	data["step"]=step;
}	

void BL_StepByStep::set(const JsonVariant& data){
	if(data["action"]=="inc"){
		int steps= data["steps"];
		doSteps(true,steps);
	}else if(data["action"]=="dec"){
		int steps= data["steps"];
		doSteps(false,steps);
	}
	
}
	
void BL_StepByStep::saveConfig(JsonObject& data){
	// {"bl":"SBS","period":30,"pin1":5,"pin2":4,"pin3":0,"pin4":2,"step":2}
	data["bl"]="SBS";
	data["period"]=period;
	data["pin1"]=pin1;
	data["pin2"]=pin2;
	data["pin3"]=pin3;
	data["pin4"]=pin4;
	data["step"]=step;
}
  
