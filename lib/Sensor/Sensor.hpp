#ifndef Sensor_h
#define Sensor_h
#include <WiFi.h>
#include <HTTPClient.h>
#include "Controller.hpp"
#include <NTPClient.h>

#define MINUTOS_30 1800000
#define MINUTOS_3  180000

/*__________Clase Sensor__________*/
class Sensor {
  public:
// CONSTRUCTOR Y DESTRUCTOR
    Sensor(int pin, String tipoDato, String tipoPin);
    Sensor();
    //~Sensor();
// METODOS
    int getData();
    float getDataAnalog();
    int getlastData();
    float getlastDataAnalog();
    int getSensorPin();
    String getSensorTipoDato();
    String getSensorTipoPin();
    String getNombre();
    String getInfoAddr();
    unsigned long getlastTimeReport();
    void Disable();
    void Enable();
    void setData(int data);
    void setlastData(int data);
    void setlastDataAnalog(float dataAnalog);
    void setlastTimeReport();
    void setInfoAddr(String InfoAddr);
    void setSensorPin(int pin);
    void setSensorTipoDato(String tipoDato);
    void setSensorTipoPin(String tipoPin);
    void setNombre(String nombre);
    void setConfig(String pulltype);

    void debug();
    int readSensorData();
    float readSensorDataAnalog();
    void reportSystem(String type);
    void periodicReport();
    void exceptionReport();
    int isEnabled();
    float getUmbral();
    void setUmbral(float umbral);
    unsigned long getintervaloReporte();
    void setintervaloReporte(unsigned long intervaloReporte);
    int antiRebote(int data);

//Op
  protected:
    int pin;
    String nombre="";
    String tipoDato; //Analogico o Digital
    String tipoPin;  //Input o Output
    String InfoAddr;
    unsigned long lastTimeReport=0;
    int data;
    float dataAnalog;
    int lastData = 0;
    float lastDataAnalog = 0; 
    int enable = 0;
    float umbral = 0;
    unsigned long intervaloReporte= 120000;//MINUTOS_30;//cada 30 minutos
    int lastReportOk = 200;
    int lastState = 1;
  };

#endif
