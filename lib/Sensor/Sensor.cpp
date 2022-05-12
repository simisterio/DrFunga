#include "Sensor.hpp"
#include "Controller.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>


extern Controller mcu;
extern NTPClient timeClient;
extern uint64_t ipoc;
extern uint64_t ipoc_exception;

/*__________Clase Sensor__________*/
//Constructor y Destructor
/*Sensor::Sensor(int pin, uint8_t _DHT22):_dht(pin, _DHT22){
	//this->pin = pin;
}*/


Sensor::Sensor(int pin, String tipoDato, String tipoPin){
	this->pin=pin;
	this->tipoDato=tipoDato;
	this->tipoPin=tipoPin;
}
Sensor::Sensor(){}
//Sensor::~Sensor(){};

//Metodos:
int Sensor::getData(){return this->data;}
float Sensor::getDataAnalog(){return this->dataAnalog;}
int Sensor::getlastData(){return this->lastData;}
float Sensor::getlastDataAnalog(){return this->lastDataAnalog;}
int Sensor::getSensorPin(){return this->pin;}
String  Sensor::getSensorTipoDato(){	return this->tipoDato;}
String  Sensor::getSensorTipoPin(){return this->tipoPin;}
String  Sensor::getNombre()
{
	if(this->nombre == NULL) {return "Sin Nombre";}
	else {return this->nombre;} 
}
String Sensor::getInfoAddr(){return this->InfoAddr;}
unsigned long Sensor::getlastTimeReport(){return this->lastTimeReport;}
void Sensor::setData(int data){this->data = data;}
void Sensor::setlastData(int data){this->lastData = data;}
void Sensor::setlastDataAnalog(float dataAnalog){this->lastDataAnalog = dataAnalog;}
void Sensor::setlastTimeReport(){this->lastTimeReport = millis();}
void Sensor::setInfoAddr(String InfoAddr){this->InfoAddr = InfoAddr;}
void Sensor::setSensorPin(int pin){this->pin=pin;}
void Sensor::setSensorTipoDato(String tipoDato){	this->tipoDato=tipoDato;}
void Sensor::setSensorTipoPin(String TipoPin){this->tipoPin=tipoPin;}
void Sensor::setConfig(String pulltype)
{
	if (tipoDato == "DIGITAL")
	{
		if(this->tipoPin == "INPUT") {
			if (pulltype == "PULLUP")
			{
				pinMode(this->pin, INPUT_PULLUP);
			}
			else if (pulltype == "PULLDOWN")
			{
				pinMode(this->pin, INPUT);
			}
		}
	 	else {pinMode(this->pin, OUTPUT);}
	}
	Enable();	
}
void Sensor::setNombre(String  nombre){this->nombre = nombre;}
int Sensor::readSensorData()
{
	if (tipoDato == "DIGITAL") {this->data = digitalRead(this->pin);}
	return this->data;
}
float Sensor::readSensorDataAnalog()
{
	if(tipoDato == "ANALOGICO")	{this->dataAnalog = analogRead(this->pin);}
	return this->dataAnalog;
}
void Sensor::Enable()
{
	this->enable = 1;
}
void Sensor::Disable()
{
	this->enable = 0;
}
int Sensor::isEnabled()
{
	return this->enable;
}
float Sensor::getUmbral(){
	return this->umbral;
}
void Sensor::setUmbral(float umbral){
	this->umbral = umbral;
}
void Sensor::debug(){
	DEBUG_SENSORPRINT(this->getNombre());
	DEBUG_SENSORPRINT(": ");
	if (getSensorTipoDato() == "ANALOGICO")
	{
		DEBUG_SENSORPRINTLN(this->readSensorDataAnalog());
	}
	else if (getSensorTipoDato() == "DIGITAL")
	{
		DEBUG_SENSORPRINTLN(this->readSensorData());
	}
}

void Sensor::reportSystem(String type)
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
	if (getSensorTipoDato() == "ANALOGICO"){
		content["infoValue"] = readSensorDataAnalog();
		content["infoAddr"] = getInfoAddr();
	}
	else if (getSensorTipoDato() == "ID USER"){
		content["infoValue"] = mcu.getidUser();
		content["infoAddr"] = "9999";
	}
	else if (getSensorTipoDato() == "DIGITAL"){
		content["infoValue"] = readSensorData();
		content["infoAddr"] = getInfoAddr();
	}
	
	if (type == "0002" || type == "0004")
	{
		content["time"] = ipoc_exception*1000;	
	}
	
	String output;
	serializeJson(doc, output);
      
    int httpResponseCode1 = http.POST(output);

    DEBUG_SENSORPRINT("HTTP Response code: ");
    DEBUG_SENSORPRINTLN(httpResponseCode1);
    if (httpResponseCode1 != 200)
    {
    	if (getSensorTipoDato() == "ID USER")
    	{
    		setintervaloReporte(90000);//minuto y medio
    	}
    	setintervaloReporte(MINUTOS_3);

    }
    else{
    	setintervaloReporte(MINUTOS_30);
    }
    this->lastReportOk = httpResponseCode1;
    setlastTimeReport();

   /* if (getSensorTipoDato() == "ID USER")
    {
    	String payload = http.getString();
    	DEBUG_SENSORPRINT("idIdUser: ");
    	DEBUG_SENSORPRINTLN(mcu.getidUser());
    	DEBUG_SENSORPRINT("payload Exception: ");
    	DEBUG_SENSORPRINTLN(payload);
    }*/
    //String payload = http.getString();

    DEBUG_SENSORPRINT("payload Exception: ");
    //DEBUG_SENSORPRINTLN(payload);
    // Free resources
    http.end();
}

void Sensor::periodicReport()
{
	if ((millis() - getlastTimeReport()) > getintervaloReporte()) 
	{	
		DEBUG_SENSORPRINT("Reporte periodico: ");
		DEBUG_SENSORPRINT(getNombre());
		DEBUG_SENSORPRINT(" : ");
        DEBUG_SENSORPRINT("gpio: ");
        DEBUG_SENSORPRINTLN(getSensorPin());
		if (getSensorTipoDato() == "ANALOGICO"){
			DEBUG_SENSORPRINT(readSensorDataAnalog());
			reportSystem("0003");
		}
		else if (getSensorTipoDato() == "DIGITAL"){
			DEBUG_SENSORPRINTLN(readSensorData()); 
			reportSystem("0001");
		}
		setlastTimeReport();
	}
}

void Sensor::exceptionReport()
{
	if (getSensorTipoDato() == "ANALOGICO")
	{
		if(abs(getlastDataAnalog() - readSensorDataAnalog()) >= getUmbral())
		{	
			DEBUG_SENSORPRINT("Reporte Exception: ");
			DEBUG_SENSORPRINTLN(getNombre());
			DEBUG_SENSORPRINT(" : ");
			DEBUG_SENSORPRINT(readSensorDataAnalog());
            DEBUG_SENSORPRINT("gpio: ");
            DEBUG_SENSORPRINTLN(getSensorPin());
			ipoc_exception = timeClient.getEpochTime();
			reportSystem("0004");
			setlastDataAnalog(getDataAnalog());
		}
	}

	else if (getSensorTipoDato() == "DIGITAL")
	{
		if(getlastData() != readSensorData())
		{
			DEBUG_SENSORPRINT("Reporte Exception: ");
			DEBUG_SENSORPRINTLN(getNombre());
			DEBUG_SENSORPRINT(" : ");
			DEBUG_SENSORPRINTLN(readSensorData());
            DEBUG_SENSORPRINT("gpio: ");
            DEBUG_SENSORPRINTLN(getSensorPin());
			ipoc_exception = timeClient.getEpochTime();
			reportSystem("0002");
			setlastData(getData());
		}
	}
	else if (getSensorTipoDato() == "ID USER")
	{
		if(getlastData() != getData())
		{
			DEBUG_SENSORPRINT("Reporte ");
			DEBUG_SENSORPRINTLN(getNombre());
			DEBUG_SENSORPRINT(" : ");
			DEBUG_SENSORPRINTLN(mcu.getidUser());
			ipoc_exception = timeClient.getEpochTime();
			reportSystem("0004");
			setlastData(getData());
		}
		else if((this->lastReportOk != 200) && ((millis() - getlastTimeReport()) > getintervaloReporte())) {
			reportSystem("0004");
			//setlastData(getData());
		}
	}
}

unsigned long Sensor::getintervaloReporte(){
	return this->intervaloReporte;
}
void Sensor::setintervaloReporte(unsigned long intervaloReporte){
	this->intervaloReporte = intervaloReporte;
}
