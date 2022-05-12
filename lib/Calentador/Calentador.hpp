#ifndef Calentador_h
#define Calentador_h

#include "Arduino.h"
#include "LED.hpp"
#include "../Rele/Rele.hpp"

class Calentador : public Rele {
	public:
		Calentador(int pin, int pinEstado, String especificacion);
		Calentador();
		
		void setConfig();
		void operarCerrarAbrir(unsigned long tiempoOperacion);
		int getCalentadorState();
        void setStandby(boolean standby);
        unsigned long getIntervaloStandby();
        void setIntervaloStandby(unsigned long intervaloStandby);
        unsigned long getStartStandby();
        void setStartStandby(unsigned long startStandby);
        boolean isStandby();
	
	private:
        int pinEstado;
		int estadoRele;
		int lastState;
        boolean standby = false;
		int counter = 0;
        unsigned long intervaloStandby = 600000; //10 minutos
        unsigned long startStandby = 0;
        unsigned long lasttimeOP = 0;
		unsigned long intervaloReporte = 3000000;

};
#endif
