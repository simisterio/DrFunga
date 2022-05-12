#ifndef SensorTH_h
#define SensorTH_h

#include "DHT.h"
#include <math.h>
#include "Sensor.hpp"
#include "Controller.hpp"
         
#define MINUTOS_30 1800000
#define MINUTOS_3  180000

/*__________Clase Sensor TH__________*/
class SensorTH : public Sensor{
  public:
//CONSTRUCTOR Y DESTRUCTOR
    SensorTH(uint8_t type, int pin, String tipoDato, String tipoPin);
    //SensorTH();
//METODOS    
    String getAddrTemp();
    String getAddrHum();
    float getTemp();
    float getHum();

    void init();
    void setInfoAddr(String InfoAddr, String Nombre);
    String getInfoAddr(String Nombre);
    void debug();  
    void reportSystem(String type, String nombre);
    void periodicReport();
    void exceptionReport();
    void setlastTemp(float temp);
    void setlastHum(float hum);
    float getlastTemp();
    float getlastHum();
    unsigned long getintervaloReporte();
    void setintervaloReporte(unsigned long intervaloReporte);
    String getNombreHum();
    String  getNombreTemp();

  private:
    uint8_t type;
    float temp;
    float hum;
    float lastTemp=0;
    float lastHum=0;
    DHT dht;
    String Addr_T = "0012";
    String Addr_H = "0013";
    unsigned long intervaloReporte= 120000;
    String nombreHumedad = "Sensor Hudedad";
    String  nombreTemp = "Sensor Temperatura";
};
#endif