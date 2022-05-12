#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED {
	public:
		LED(int pin, String color);
		LED();
		int getPin();
		String getColor();//retorna especificacion
		void setColor(String especificacion);
		void setConfig();
		void encender();
		void apagar();
		void intermitenteFinito(unsigned long tiempoOperacion);
        void intermitente();
		int isEnabled();
		void Disable();
    	void Enable();
    	unsigned long getlasttimeOP();
    	void setlasttimeOP(unsigned long lasttimeOP);
	

	protected:
		int pin;
        String color;
		String especificacion;// NA o NC
		int enable = 1;
		unsigned long lasttimeOP= 0;
        long on = 100;
        long off = 500;
        boolean flag = true;
        long startOperacion = 0;
        long previousMillis = 0;
  };
  #endif











































