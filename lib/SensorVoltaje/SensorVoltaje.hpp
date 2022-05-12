
#ifndef SensorVoltaje_h
#define SensorVoltaje_h
#include <math.h>
#include "Sensor.hpp"
#include "Controller.hpp"

#define MINUTOS_30 1800000
#define MINUTOS_3  180000

/*__________Clase Sensor Voltaje__________*/  
class SensorVoltaje : public Sensor{
  public:
    SensorVoltaje(float factorAjuste, int pin, String tipoDato, String tipoPin);
    SensorVoltaje();
    float getfactorAjuste();
    float getVout();
    float getVoltage();
    float getR1();
    float getR2();
    float getlastVout();
    String getInfoAddr();
    void setlastVout(float Vout);
    void setInfoAddr(String Addr_Volt);
    void setfactorAjuste(float factorAjuste);
    void setConfig();
    void debug();
    void reportSystem(String type);
    void periodicReport();
    void exceptionReport();
    unsigned long getintervaloReporte();
    void setintervaloReporte(unsigned long intervaloReporte);

  private:
    float factorAjuste;
    float R1 = 30000.0;
    float R2 = 7500.0;
    float Voltage;
    float Vout;
    float lastVout=0;
    String Addr_Volt="0011";
    unsigned long intervaloReporte=MINUTOS_30;//cada 30 minutos
};
#endif