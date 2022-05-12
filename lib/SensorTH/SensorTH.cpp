#include "SensorTH.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>

extern Controller mcu;
extern NTPClient timeClient;
extern uint64_t ipoc;
extern uint64_t ipoc_exception;

/*__________Clase Sensor TH__________*/  

SensorTH::SensorTH(uint8_t type, int pin, String tipoDato, String tipoPin):
		Sensor(pin, tipoDato, tipoPin),dht(pin, type){}

//SensorTH::SensorTH(){}
String SensorTH::getAddrTemp()
{
	return this->Addr_T;
}
String SensorTH::getAddrHum()
{
	return this->Addr_H;
}
void SensorTH::init(){
	(this->dht).begin();
	Enable();
}
float SensorTH::getTemp(){
	this->temp=(this->dht).readTemperature();
	//return this->temp;
	return this->temp;
}
float SensorTH::getHum(){
	this->hum=(this->dht).readHumidity();
	//return this->hum;
	return this->hum;
}
void SensorTH::debug(){
	DEBUG_SENSORTH_PRINT("Temperatura: ");
  	DEBUG_SENSORTH_PRINT(getTemp());
  	DEBUG_SENSORTH_PRINTLN("°C");
  	DEBUG_SENSORTH_PRINT("Humedad Relativa: ");
  	DEBUG_SENSORTH_PRINT(getHum());
  	DEBUG_SENSORTH_PRINTLN("%");
}

void SensorTH::reportSystem(String type, String nombre)
{
	HTTPClient http;
	WiFiClient client;
    // Your Domain name with URL path or IP address with path
    http.begin(client, mcu.getServer());

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
      
    // Data to send with HTTP POST
    // Send HTTP POST request
    	
    StaticJsonDocument<256> doc;
	doc["type"] = type;
	doc["addr"] = mcu.getID();
	doc["time"] = ipoc*1000;

	//JsonArray content = doc.createNestedArray("content");
	if (nombre == "Temperatura")
	{
		JsonObject content_0 = doc["content"].createNestedObject();
		content_0["infoValue"] = getTemp();
		content_0["infoAddr"] = getAddrTemp();
		if (type == "0004")
		{
			content_0["time"] = ipoc_exception*1000;	
		}
	}
	else if (nombre == "Humedad")
	{
		JsonObject content_0 = doc["content"].createNestedObject();
		content_0["infoValue"] = getHum();
		content_0["infoAddr"] = getAddrHum();
		if (type == "0004")
		{
			content_0["time"] = ipoc_exception*1000;	
		}	
	}
	else{
		JsonArray content = doc.createNestedArray("content");
		JsonObject content_0 = content.createNestedObject();
		content_0["infoValue"] = getTemp();
		content_0["infoAddr"] = getAddrTemp();
		
		JsonObject content_1 = content.createNestedObject();
		content_1["infoValue"] = getHum();
		content_1["infoAddr"] = getAddrHum();
	}


	
	String output;
	serializeJson(doc, output);
      
    int httpResponseCode1 = http.POST(output);

    DEBUG_SENSORTH_PRINT("HTTP Response code: ");
    DEBUG_SENSORTH_PRINTLN(httpResponseCode1);
    if (httpResponseCode1 != 200)
    {
    	setintervaloReporte(MINUTOS_3);
    }
    else{
    	setintervaloReporte(MINUTOS_30);
    }
    //String payload = http.getString();

    //SENSORTH_PRINT("payload Exception: ");
    //SENSORTH_PRINTLNln(payload);
    // Free resources
    http.end();
}
void SensorTH::periodicReport()
{
	if ((unsigned long)(millis() - getlastTimeReport()) > getintervaloReporte()) 
	{	
		DEBUG_SENSORTH_PRINT("Reporte periodico: ");
		DEBUG_SENSORTH_PRINTLN(getNombre());
        DEBUG_SENSORTH_PRINT("Temperatura ");
        DEBUG_SENSORTH_PRINTLN(getTemp());
		reportSystem("0003", "Periodico"); 
		setlastTimeReport();
	}
}

void SensorTH::exceptionReport()
{
	if (isnan(getTemp()) || isnan(getHum()))
	{
		return;
	}
	else{
		if(abs(getlastTemp() - getTemp()) > 3){
			DEBUG_SENSORTH_PRINT("Reporte Exception: ");
			DEBUG_SENSORTH_PRINT("Temperatura ");
            DEBUG_SENSORTH_PRINTLN(getTemp());
			ipoc_exception = timeClient.getEpochTime();
			reportSystem("0004", "Temperatura");
			setlastTemp(getTemp());
		}
		else if(abs(getlastHum() - getHum()) > 10){
			DEBUG_SENSORTH_PRINT("Reporte Exception: ");
			DEBUG_SENSORTH_PRINTLN("Humedad");
			ipoc_exception = timeClient.getEpochTime();
			reportSystem("0004", "Humedad");
			setlastHum(getHum());
		}
	}
}

void SensorTH::setlastTemp(float temp){
	this->lastTemp = temp;
}
void SensorTH::setlastHum(float hum){
	this->lastHum = hum;
}
float SensorTH::getlastTemp(){
	return this->lastTemp;
}
float SensorTH::getlastHum(){
	return this->lastHum;
}
unsigned long SensorTH::getintervaloReporte(){
	return this->intervaloReporte;
}
void SensorTH::setintervaloReporte(unsigned long intervaloReporte){
	this->intervaloReporte = intervaloReporte;
}
void SensorTH::setInfoAddr(String InfoAddr, String Nombre){
	if (Nombre == getNombreHum())
	{
		this->Addr_H = InfoAddr;
	}
	else if (Nombre == getNombreTemp())
	{
		this->Addr_T = InfoAddr;
	}
}

String SensorTH::getNombreHum(){
	return this->nombreHumedad;
}
String  SensorTH::getNombreTemp(){
	return this->nombreTemp;
}
String SensorTH::getInfoAddr(String Nombre){
	if (Nombre == getNombreHum())
	{
		return this->Addr_H;
	}
	else if (Nombre == getNombreTemp())
	{
		return this->Addr_T;
	}
	return "";
}