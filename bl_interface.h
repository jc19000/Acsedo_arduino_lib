#ifndef BL_INTERFACE_H
#define BL_INTERFACE_H

#include "Arduino.h"
#include "ArduinoJson.h"

class BL_Interface {
    public:
		BL_Interface(int p_id,int p_period):
		id(p_id),
		period(p_period)
		{}
		
		virtual void setup(const JsonVariant p_config)=0;
		
		bool execute(int p_cpt){
			if(p_cpt%period){return true;}
			else{return false;}
		}
		
        virtual void push(JsonObject& data)= 0;
		virtual void get(JsonObject& data)= 0;	
		virtual void set(const JsonVariant& data)= 0;
		virtual void saveConfig(JsonObject& data)= 0;
	protected:
		int id;
		int period;
};
#endif