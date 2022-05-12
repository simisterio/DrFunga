#include "Sensor.hpp"
#include "LED.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>

//CONSTRUCTOR
LED::LED(int pin, String color)
{
	this->pin = pin;
	this->color = color;
}
LED::LED(){}
//METODOS
int LED::getPin()
{
	return this->pin;
}
String  LED::getColor()
{
	return this->color;
}
void LED::setColor(String color)
{
	this->color = color;
}
void LED::setConfig()
{
	pinMode(this->pin, OUTPUT);
	/*nos aseguramos que comienza en el estado normal del LED*/
	//if (this->especificacion == "NA"){digitalWrite(this->pin,HIGH);}
	//else{digitalWrite(this->pin, LOW);}// NC
	digitalWrite(this->pin, LOW);
	
}
void LED::encender()
{
	digitalWrite(this->pin, HIGH);
	DEBUG_LED_PRINT("Se realiza encendido LED en pin ");
	DEBUG_LED_PRINTLN(getPin());
}
void LED::apagar()
{
	digitalWrite(this->pin, LOW);
	DEBUG_LED_PRINT("Se realiza apagado en pin ");
	DEBUG_LED_PRINTLN(getPin());
}

void LED::intermitenteFinito(unsigned long tiempoOperacion)
{
	setlasttimeOP(millis());
	DEBUG_LED_PRINTLN("LED operando modo Intermitente Finito");
    startOperacion = millis();
    while(millis() < startOperacion + tiempoOperacion)
    {
        if (millis() < (previousMillis + on + off)){flag = true;}
        else {
            flag = false;
            previousMillis = millis();
        }
        if (flag){
            if (millis() > (previousMillis + on)){digitalWrite(pin, LOW);}
            else{digitalWrite(pin, HIGH);}
        }
    }
}

void LED::intermitente()
{
	DEBUG_LED_PRINTLN("LED operando modo Intermitente");
    if (millis() < (previousMillis + on + off)){flag = true;}
    else {
        flag = false;
        previousMillis = millis();
    }
    if (flag){
        if (millis() > (previousMillis + on)){digitalWrite(pin, LOW);}
        else{digitalWrite(pin, HIGH);}
    }

}
int LED::isEnabled(){return this->enable;}
void LED::Disable(){this->enable = 0;}
void LED::Enable(){	this->enable = 1;}
unsigned long LED::getlasttimeOP(){	return this->lasttimeOP;}
void LED::setlasttimeOP(unsigned long lasttimeOP){this->lasttimeOP=lasttimeOP;}
