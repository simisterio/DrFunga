#ifndef Rele_h
#define Rele_h
#include "Arduino.h"

class Rele {
	public:
		Rele(int pin, String especificacion);
		Rele();
		int getPin();
		String getEsp();//retorna especificacion
		void setEsp(String especificacion);
		void setConfig();
		void operarApertura();
		void operarCierre();
		void operarAbrirCerrar(unsigned long tiempoOperacion);
		void operarCerrarAbrir(unsigned long tiempoOperacion);
		int isEnabled();
		void Disable();
    	void Enable();
    	unsigned long getlasttimeOP();
    	void setlasttimeOP(unsigned long lasttimeOP);
		
		//Operadores
	    //friend const void operator+( Sensor& s1, Sensor& s2);

	protected:
		int pin;
		String especificacion;// NA o NC
		int enable = 1;
		unsigned long lasttimeOP= 0;
  };
  #endif