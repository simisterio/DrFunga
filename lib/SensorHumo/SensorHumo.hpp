#ifndef Sensor_Humo_h

#define SensorHumo_h
#include "Sensor.hpp"
#include "MQ2/MQ2.h"

/*__________Clase Sensor Humo__________*/
class SensorHumo: public Sensor{
    public:
    //CONSTRUCTOR Y DESTRUCTOR
        SensorHumo(int pin, String tipoDato, String tipoPin);
        SensorHumo();
        //~SensorHumo();
    // Metodos
        float getPPM();
        void  setConfig();
        void  exceptionReport();
        void periodicReport();
        void  reportSystem(String type);
        void  debug();
        void  calibrar();       
        void  setlastPPM(float valuePPM);
        float getlastPPM();
    private:
        float valuePPM;
        float lastvaluePPM; 
        MQ2 mq2;
};
#endif