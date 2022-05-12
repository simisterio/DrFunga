#ifndef Boton_h
#define Boton_h
#include "Sensor.hpp"

/*__________Clase Boton__________*/
class Boton : public Sensor{
  public:
//CONSTRUCTOR Y DESTRUCTOR
    Boton(int pin, String tipoDato, String tipoPin);
    Boton();

//METODOS 
    
    boolean antiRebote();
  private:
    boolean lastState=0;
};
#endif
