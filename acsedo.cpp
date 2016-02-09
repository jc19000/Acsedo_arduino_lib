#include "acsedo.h"

void Acsedo::webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {
    switch(type) {
        case WStype_DISCONNECTED:
            DEBUG_PRINT("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            {
                DEBUG_PRINT("[WSc] Connected to url: %s\n",  payload);
            }
            break;
        case WStype_TEXT:{
            DEBUG_PRINT("[WSc] get text: %s\n", payload);
            
            String data;
            for ( size_t i = 0; i < lenght; ++i ){
              data+=(char)payload[ i ];
            }

           DEBUG_PRINT("Data receive: "); DEBUG_PRINT(data);
           
           StaticJsonBuffer<1000> jsonBuffer;
           JsonObject &root = jsonBuffer.parseObject(data);
		   
		   int l_id=root["id"];
		   String l_decrypted_data_string=decrypt(root["encryptedData"]);
		   JsonObject &l_decrypted_data = jsonBuffer.parseObject(l_decrypted_data_string);
		   
		   if(l_decrypted_data.containsKey("GET")){
				StaticJsonBuffer<200> blBuffer;
				JsonObject& json = blBuffer.createObject();
			
				int l_subid=root["GET"];
				json["subid"]=l_subid;
				
				bls[l_subid]->get(json);
				String data;
				json.prettyPrintTo(data);
		  
				sendData(data);
		   }else if(l_decrypted_data.containsKey("SET")){
			   
		   }

        }
            break;
        case WStype_BIN:
            //shall noot happened
            break;
    }
}

void Acsedo::setup() { 
  
  DEBUG_PRINT("Acsedo VP starting");

  // this opens the file "f.txt" in read-mode
  File f = SPIFFS.open("/config.json", "r");
  if (!f) {
    DEBUG_PRINT("File doesn't exist yet. Error ");
    f = SPIFFS.open("/config.json", "r");
  } 
  
  if (f) {
    DEBUG_PRINT("File exist yet");
    // we could open the file
    if(f.available()) {
      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject &root = jsonBuffer.parseObject(f.readString());

      if (!root.success()) {
        DEBUG_PRINT("parseObject() failed");
        return;
      }

      for(uint8_t t = 4; t > 0; t--) {
          DEBUG_PRINT("[SETUP] BOOT WAIT %d...\n", t);
          delay(1000);
      }

      ssid=root.get<const char*>("ssid");
      password=root.get<const char*>("password");
      
      WiFiMulti.addAP(ssid, password);

      while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
      }
      
      DEBUG_PRINT("conf file:");
      root.printTo(Serial);
      
      //start websocket
      websocketUrl=root["websocketUrl"];
      websocketPort= root["websocketPort"];
      websocketPath= root["websocketPath"];
      
      begin(websocketUrl,websocketPort);
      
      DEBUG_PRINT("start BL(s)");
      int i=0;
      int period=root["bls"][i]["period"];
      for(i;i!=root["bls"][i]["bl"].size();i++){
        if(root["bls"][i]["bl"]=="DHT"){
          bls[i]=new BL_Temperature(i,period);
          bls[i]->setup(root["bls"][i]); 
        }else if("GPI"){
          bls[i]=new BL_GPI(i,period);
          bls[i]->setup(root["bls"][i]); 
        }else if("GPO"){
          bls[i]=new BL_GPO(i,period);
          bls[i]->setup(root["bls"][i]); 
        }else if("PWM"){
          bls[i]=new BL_PWM(i,period);
          bls[i]->setup(root["bls"][i]); 
        }else if("SBS"){
          bls[i]=new BL_StepByStep(i,period);
          bls[i]->setup(root["bls"][i]); 
        }
      }
      bl_number=i;
      pushingPeriod=root["pushingPeriod"];
	  
      id=root["id"];
      const char* type=root["type"];
	  
	  privateKey=root["privateKey"];
	  publicKey=root["publicKey"];
	  
      DEBUG_PRINT("setup finished");
    }else{
      DEBUG_PRINT("file not available");
      
    }
  }else{
      DEBUG_PRINT("couldn't open the file");
      
    }
  f.close();  
}


void Acsedo::saveConfig(){
    // open the file in write mode
    File f = SPIFFS.open("/config.json", "w");
    if (!f ) {
      DEBUG_PRINT("file creation failed");
    }
    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["id"] = id;
    root["type"] = type;
	
    root["ssid"] = ssid;
    root["password"] = password;

    root["startOfFrame"] = startOfFrame;
    root["endOfFrame"] = endOfFrame;

    root["pushingPeriod"] = pushingPeriod;
    root["serialSpeed"] = serialSpeed;

    root["websocketUrl"] = websocketUrl;
    root["websocketPort"] = websocketPort; 
    root["websocketPath"] = websocketPath;

	root["privateKey"]=privateKey;
	root["publicKey"]=publicKey;
	  
    JsonArray& blsArray=root.createNestedArray("bls");

    for(int i=0;i!=bl_number;i++){
        JsonObject& config = jsonBuffer.createObject();
          bls[i]->saveConfig( config ); 
          blsArray.add(config);
    }
      
    root.printTo(f);
    f.close();  
}
void Acsedo::sendData(const String& p_data){ 
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();
		  
	json["id"]=id;
	json["encryptedData"]=encrypt(p_data);
	
	String l_data;
	json.prettyPrintTo(l_data);	
	webSocket.sendTXT(l_data.c_str(), l_data.length());
}

void Acsedo::loop() {
    delay(pushingPeriod);
    for(int i=0;i!=bl_number;i++){
        if(bls[i]->execute(cpt)){
			StaticJsonBuffer<200> blBuffer;
			JsonObject& json = blBuffer.createObject();
			
			json["subid"]=i;
	
			bls[i]->push( json );
		  
			String data;
			json.prettyPrintTo(data);
		  
			sendData(data);
        }
      }
    cpt++;
    webSocket.loop();
}