#include "Boton.hpp"
#include "Acceso.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>


volatile int abierto = 0;

Boton::Boton(int pin, String tipoDato, String tipoPin):
	Sensor(pin, tipoDato, tipoPin){
    
  }

boolean Boton::antiRebote(){

	//boolean state = digitalRead(btnEmergencia);
	boolean state = readSensorData();
	if(this->lastState != state){
		delayMicroseconds(16383);
		state = readSensorData();
	}
	return state;
}

