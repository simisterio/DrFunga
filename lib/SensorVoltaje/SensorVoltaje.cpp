#include "SensorVoltaje.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>

extern Controller mcu;
extern NTPClient timeClient;
extern uint64_t ipoc;
extern uint64_t ipoc_exception;

/*__________Clase Sensor Voltaje__________*/  

SensorVoltaje::SensorVoltaje(float factorAjuste, int pin, String tipoDato, String tipoPin):
			Sensor(pin, tipoDato, tipoPin){
	this->factorAjuste = factorAjuste;
	this->pin = pin;
	this->tipoDato = tipoDato;
	this->tipoPin = tipoPin;
}
SensorVoltaje::SensorVoltaje(){}
void SensorVoltaje::setConfig(){
	Enable();
}
float SensorVoltaje::getfactorAjuste(){
	return this->factorAjuste;
}
float SensorVoltaje::getVout(){
	this->Vout=(readSensorDataAnalog()*3.3)/4095;
	return this->Vout;
}
float SensorVoltaje::getVoltage(){
	this->Voltage = (getVout()/(this->R2/(this->R1 + this->R2))) + factorAjuste;
	return this->Voltage;
}	
float SensorVoltaje::getR1(){
	return this->R1;
}
float SensorVoltaje::getR2(){
	return this->R2;
}
float SensorVoltaje::getlastVout(){return this->lastVout;}
String SensorVoltaje::getInfoAddr()
{
	return this->Addr_Volt;
}
void SensorVoltaje::setlastVout(float Vout){this->lastVout=Vout;}
void SensorVoltaje::setInfoAddr(String Addr_Volt)
{
	this->Addr_Volt = Addr_Volt;
}
void SensorVoltaje::setfactorAjuste(float factorAjuste){
	this->factorAjuste = factorAjuste;
}
void SensorVoltaje::debug(){
	DEBUG_SENSORVOLT_PRINT("Sensor Voltaje");
	DEBUG_SENSORVOLT_PRINT(": ");
	DEBUG_SENSORVOLT_PRINT(getVoltage());
	DEBUG_SENSORVOLT_PRINTLN("[V]");
}
void SensorVoltaje::reportSystem(String type)
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
	content["infoValue"] = getVoltage();
	content["infoAddr"] = getInfoAddr();
	if (type == "0004")
	{
		content["time"] = ipoc_exception*1000;	
	}
	
	String output;
	serializeJson(doc, output);

    int httpResponseCode1 = http.POST(output);

    DEBUG_SENSORVOLT_PRINT("HTTP Response code: ");
    DEBUG_SENSORVOLT_PRINTLN(httpResponseCode1);
    if (httpResponseCode1 != 200)
    {
    	setintervaloReporte(MINUTOS_3);
    }
    else{
    	setintervaloReporte(MINUTOS_30);
    }
    //String payload = http.getString();

    //DEBUG_SENSORVOLT_PRINT("payload Exception: ");
    //DEBUG_SENSORVOLT_PRINTln(payload);
    // Free resources
    http.end();
}

void SensorVoltaje::periodicReport()
{
	if ((millis() - getlastTimeReport()) > getintervaloReporte()) 
	{	
		DEBUG_SENSORVOLT_PRINT("Reporte periodico: ");
		DEBUG_SENSORVOLT_PRINTLN(getNombre());
		reportSystem("0003");
		setlastTimeReport();
	}
}

void SensorVoltaje::exceptionReport()
{
	if(abs(getlastVout() - getVoltage()) >= 0.2)
	{
		DEBUG_SENSORVOLT_PRINT("Reporte Exception: ");
		DEBUG_SENSORVOLT_PRINTLN(getNombre());
		ipoc_exception = timeClient.getEpochTime();
		reportSystem("0004");
		setlastVout(getVoltage());
	}
}
unsigned long SensorVoltaje::getintervaloReporte(){
	return this->intervaloReporte;
}
void SensorVoltaje::setintervaloReporte(unsigned long intervaloReporte){
	this->intervaloReporte = intervaloReporte;
}