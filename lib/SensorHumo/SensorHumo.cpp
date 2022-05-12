#include "SensorHumo.hpp"
#include "math.h"
#include "../../include/debug.hpp"
#include <TelnetStream.h>
extern Controller mcu;
extern NTPClient timeClient;
extern uint64_t ipoc;
extern uint64_t ipoc_exception;

SensorHumo::SensorHumo(int pin, String tipoDato,String tipoPin):
    Sensor(pin , tipoDato , tipoPin) , mq2(pin){}

float SensorHumo::getPPM(){
   this->valuePPM= mq2.readSmoke();
   return this->valuePPM;
}
void  SensorHumo::setlastPPM(float valuePPM){
    this->lastvaluePPM = valuePPM;
}
float SensorHumo::getlastPPM(){
    return this->lastvaluePPM;    
}
void SensorHumo::calibrar(){
    mq2.begin();
}

void SensorHumo::debug(){
	DEBUG_SHUMO_PRINT("Sensor Humo");
	DEBUG_SHUMO_PRINT(": ");
	DEBUG_SHUMO_PRINT(getPPM());
	DEBUG_SHUMO_PRINTLN("[ppm]");
}

void SensorHumo::reportSystem(String type)
{
	HTTPClient http;
    WiFiClient client;
    // Your Domain name with URL path or IP address with path
    http.begin(client, mcu.getServer());

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
      
    // Data to send with HTTP POST
    // Send HTTP POST request

    StaticJsonDocument<192> doc;

	doc["type"] = type;
	doc["addr"] = mcu.getID();
	doc["time"] = ipoc*1000;

	JsonObject content = doc["content"].createNestedObject();
	content["infoValue"] = getPPM();
	content["infoAddr"] = getInfoAddr();
	if (type == "0004")
	{
		content["time"] = ipoc_exception*1000;	
	}
	
	String output;
	serializeJson(doc, output);

    int httpResponseCode1 = http.POST(output);

    DEBUG_SHUMO_PRINT("HTTP Response code: ");
    DEBUG_SHUMO_PRINTLN(httpResponseCode1);
    if (httpResponseCode1 != 200)
    {
    	setintervaloReporte(MINUTOS_3);
    }
    else{
    	setintervaloReporte(MINUTOS_30);
    }
    //String payload = http.getString();

    //DEBUG_SHUMO_PRINT("payload Exception: ");
    //DEBUG_SHUMO_PRINTLN(payload);
    // Free resources
    http.end();
}
void SensorHumo::setConfig(){
	Enable();
}
void SensorHumo::exceptionReport()
{
	if(abs(getlastPPM() - getPPM()) >= 0.5)
	{
		DEBUG_SHUMO_PRINT("Reporte Exception: ");
		DEBUG_SHUMO_PRINTLN(getNombre());
		ipoc_exception = timeClient.getEpochTime();
		reportSystem("0004");
		setlastPPM(getPPM());
	}
}
void SensorHumo::periodicReport()
{
	if ((millis() - getlastTimeReport()) > getintervaloReporte()) 
	{	
		DEBUG_SHUMO_PRINT("Reporte periodico: ");
		DEBUG_SHUMO_PRINT(getNombre());
		DEBUG_SHUMO_PRINT(" : ");
        DEBUG_SHUMO_PRINT("gpio: ");
        DEBUG_SHUMO_PRINTLN(getSensorPin());
		if (getSensorTipoDato() == "ANALOGICO"){
			DEBUG_SHUMO_PRINT(getPPM());
			reportSystem("0003");
		}
		else if (getSensorTipoDato() == "DIGITAL"){
			DEBUG_SHUMO_PRINTLN(getPPM()); 
			reportSystem("0001");
		}
		setlastTimeReport();
	}
}