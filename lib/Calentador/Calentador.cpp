#include "Calentador.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>

extern LED ledRojo;
extern LED ledVerde;

Calentador::Calentador(int pin, int pinEstado, String especificacion):
		Rele(pin, especificacion)
{
	this->pin = pin;
    this->pinEstado =pinEstado;
	this->especificacion = especificacion;
}
Calentador::Calentador(){}
int Calentador::getCalentadorState(){ return digitalRead(this->pinEstado); }
void Calentador::setStandby(boolean standby){this->standby = standby;}
boolean Calentador::isStandby(){return this->standby;}
boolean isStandby();
unsigned long Calentador::getIntervaloStandby(){return this->intervaloStandby;}
void Calentador::setIntervaloStandby(unsigned long intervaloStandby){this->intervaloStandby = intervaloStandby;}
unsigned long Calentador::getStartStandby(){return this->startStandby;}
void Calentador::setStartStandby(unsigned long startStandby){this->startStandby = startStandby;}
void Calentador::setConfig(){
	pinMode(this->pin, OUTPUT);
    pinMode(this->pinEstado, INPUT_PULLUP);
	/*nos aseguramos que comienza en el estado normal del Rele*/
	if (this->especificacion == "NA"){digitalWrite(this->pin,LOW);}
	else{digitalWrite(this->pin, HIGH);}// NC
}

void Calentador::operarCerrarAbrir(unsigned long tiempoOperacion)
{
    //DEBUG_RELE_PRINTLN("Operando Cierre");
    if(!isStandby())
    {
        ledRojo.intermitente();
        ledVerde.intermitente();
        if(getCalentadorState() == 0)
        {
            setlasttimeOP(millis());
            operarCierre();
        }
        else
        {
            if ((millis()-getlasttimeOP()) < tiempoOperacion){ operarCierre();}
            else
            {
                operarApertura();
                ledRojo.apagar();
                ledVerde.apagar();
                setStandby(true);
            }
        }   
    }
    else{if (millis() > getStartStandby() + getIntervaloStandby()){setStandby(false);}}

}

