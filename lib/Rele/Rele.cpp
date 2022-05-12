#include "Sensor.hpp"
#include "Rele.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>
// Extern agregado para evitar problema por delay

//CONSTRUCTOR

Rele::Rele(int pin, String especificacion)
{
	this->pin = pin;
	this->especificacion = especificacion;
}
Rele::Rele(){}
//METODOS
int Rele::getPin()
{
	return this->pin;
}
String  Rele::getEsp()
{
	return this->especificacion;
}
void Rele::setEsp(String especificacion)
{
	this->especificacion = especificacion;
}
void Rele::setConfig()
{
	pinMode(this->pin, OUTPUT);
	/*nos aseguramos que comienza en el estado normal del Rele*/
	//if (this->especificacion == "NA"){digitalWrite(this->pin,HIGH);}
	//else{digitalWrite(this->pin, LOW);}// NC
	digitalWrite(this->pin, LOW);
	
}
void Rele::operarApertura()
{
	if(this->especificacion == "NA")
	{
		digitalWrite(this->pin, LOW);
		DEBUG_RELE_PRINT("Se realiza Apertura en pin ");
		DEBUG_RELE_PRINTLN(getPin());
	}//NA se abre sin paso de corriente
	else
	{
		digitalWrite(this->pin, HIGH);
		DEBUG_RELE_PRINT("Se realiza Apertura en pin ");
		DEBUG_RELE_PRINTLN(getPin());
	} //NC se abre con el paso de corriente
}
void Rele::operarCierre()
{
	if(this->especificacion == "NA")
	{
		digitalWrite(this->pin, HIGH);
		DEBUG_RELE_PRINT("Se realiza cierre en pin ");
		DEBUG_RELE_PRINTLN(getPin());
	}//NA se cierra con el paso de corriente
	else{
		digitalWrite(this->pin, LOW);
		DEBUG_RELE_PRINT("Se realiza cierre en pin ");
		DEBUG_RELE_PRINTLN(getPin());
	} //NC se cierra sin el paso de corriente
}
void Rele::operarAbrirCerrar(unsigned long tiempoOperacion)
{
	setlasttimeOP(millis());
	DEBUG_RELE_PRINTLN("Operando Apertura");
	while ((millis()-getlasttimeOP()) < tiempoOperacion)
	{
		operarApertura();
		
		DEBUG_RELE_PRINT("Segundos: ");
		DEBUG_RELE_PRINTLN((millis()-getlasttimeOP()));
	
	}

	operarCierre();
	DEBUG_RELE_PRINTLN("Terminando Apertura");

}

void Rele::operarCerrarAbrir(unsigned long tiempoOperacion)
{
	DEBUG_RELE_PRINTLN("Operando Cierre");
	setlasttimeOP(millis());
	while ((millis()-getlasttimeOP()) < tiempoOperacion)
	{
		operarCierre();
		
		DEBUG_RELE_PRINT("Segundos: ");
		DEBUG_RELE_PRINTLN((millis()-getlasttimeOP()));
	}
	operarApertura();
	DEBUG_RELE_PRINTLN("Terminando Cierre");
}
int Rele::isEnabled()
{
	return this->enable;
}
void Rele::Disable()
{
	this->enable = 0;
}
void Rele::Enable()
{
	this->enable = 1;
}
unsigned long Rele::getlasttimeOP()
{
	return this->lasttimeOP;
}
void Rele::setlasttimeOP(unsigned long lasttimeOP)
{
	this->lasttimeOP=lasttimeOP;
}

//Operadores
/*void operator +(Sensor& s1, Sensor& s2){

	if (s1.getSensorTipoDato() == "DIGITAL" &&  s2.getSensorTipoDato() == "DIGITAL")
	{
		if ((s1.readSensorData() == 1) && (s2.readSensorData() == 1))
		{
			
		}
	}
}*/
