#ifndef DEBUG_h
#define DEBUG_h
#include <TelnetStream.h>
//___________________ DEBUG CONTROLADOR 1 ___________________//
#define DEBUG_VISUAL_CONTROLADOR1
#define DEBUG_CONTROLADOR1
#ifdef DEBUG_VISUAL_CONTROLADOR1
    #ifdef DEBUG_CONTROLADOR1
    #define DEBUG_CONTROLADOR1_PRINT(X) Serial.print(X);
    #define DEBUG_CONTROLADOR1_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_CONTROLADOR1_PRINT(X) TelnetStream.print(X);
    #define DEBUG_CONTROLADOR1_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_CONTROLADOR1_PRINT(X) 
    #define DEBUG_CONTROLADOR1_PRINTLN(X) 
#endif
//___________________ DEBUG ACCESO ___________________//
//#define DEBUG_VISUAL_ACCESO
//#define DEBUG_ACCESO
#ifdef DEBUG_VISUAL_ACCESO
    #ifdef DEBUG_ACCESO
    #define DEBUG_ACCESOPRINT(X) Serial.print(X);
    #define DEBUG_ACCESOPRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_ACCESOPRINT(X) TelnetStream.print(X);
    #define DEBUG_ACCESOPRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_ACCESOPRINT(X) 
    #define DEBUG_ACCESOPRINTLN(X) 
#endif
//___________________ DEBUG ALARMA ___________________//
//#define DEBUG_VISUAL_ALARM
//#define DEBUG_ALARM
#ifdef DEBUG_VISUAL_ALARM
    #ifdef DEBUG_ALARM
    #define DEBUG_ALARM_PRINT(X) Serial.print(X);
    #define DEBUG_ALARM_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_ALARM_PRINT(X) TelnetStream.print(X);
    #define DEBUG_ALARM_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_ALARM_PRINT(X) 
    #define DEBUG_ALARM_PRINTLN(X) 
#endif
//___________________ DEBUG BOTON ___________________//
//#define DEBUG_VISUAL_BOTON
//#define DEBUG_BOTON
#ifdef DEBUG_VISUAL_BOTON
    #ifdef DEBUG_BOTON
    #define DEBUG_BOTONPRINT(X) Serial.print(X);
    #define DEBUG_BOTONPRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_BOTONPRINT(X) TelnetStream.print(X);
    #define DEBUG_BOTONPRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_BOTONPRINT(X) 
    #define DEBUG_BOTONPRINTLN(X) 
#endif
 
//________________ DEBUG CONTROLLER ___________________//
//#define DEBUG_VISUAL_CTRL
//#define DEBUG_CTRL
#ifdef DEBUG_VISUAL_CTRL
    #ifdef DEBUG_CTRL
    #define DEBUG_CTRLPRINT(X) Serial.print(X);
    #define DEBUG_CTRLPRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_CTRLPRINT(X) TelnetStream.print(X);
    #define DEBUG_CTRLPRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_CTRLPRINT(X) 
    #define DEBUG_CTRLPRINTLN(X) 
#endif
//___________________ DEBUG RELE ___________________///
#define DEBUG_VISUAL_RELE
#define DEBUG_RELE
#ifdef DEBUG_VISUAL_RELE
    #ifdef DEBUG_RELE
    #define DEBUG_RELE_PRINT(X) Serial.print(X);
    #define DEBUG_RELE_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_RELE_PRINT(X) TelnetStream.print(X);
    #define DEBUG_RELE_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_RELE_PRINT(X) 
    #define DEBUG_RELE_PRINTLN(X) 
#endif
//____________________DEBUR LED_______________________///
#define DEBUG_VISUAL_LED
#define DEBUG_LED
#ifdef DEBUG_VISUAL_LED
    #ifdef DEBUG_LED
    #define DEBUG_LED_PRINT(X) Serial.print(X);
    #define DEBUG_LED_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_LED_PRINT(X) TelnetStream.print(X);
    #define DEBUG_LED_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_LED_PRINT(X) 
    #define DEBUG_LED_PRINTLN(X) 
#endif
//___________________ DEBUG SENSOR ___________________///
//#define DEBUG_VISUAL_SENSOR
//#define DEBUG_SENSOR
#ifdef DEBUG_VISUAL_SENSOR
    #ifdef DEBUG_SENSOR
    #define DEBUG_SENSORPRINT(X) Serial.print(X);
    #define DEBUG_SENSORPRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_SENSORPRINT(X) TelnetStream.print(X);
    #define DEBUG_SENSORPRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_SENSORPRINT(X) 
    #define DEBUG_SENSORPRINTLN(X) 
#endif
//______________ DEBUG SENSOR CERRADURA _______________///
//#define DEBUG_VISUAL_SCerradura
//#define DEBUG_SCerradura
#ifdef DEBUG_VISUAL_SCerradura
    #ifdef DEBUG_SCerradura
    #define DEBUG_SCerraduraPRINT(X) Serial.print(X);
    #define DEBUG_SCerraduraPRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_SCerraduraPRINT(X) TelnetStream.print(X);
    #define DEBUG_SCerraduraPRINTLN(X) TelnetStream.println(X);
    #endif 
#else
    #define DEBUG_SCerraduraPRINT(X) 
    #define DEBUG_SCerraduraPRINTLN(X) 
#endif 
//________________ DEBUG SENSOR HUMO ___________________///
#define DEBUG_VISUAL_SHUMO
//#define DEBUG_SHUMO
#ifdef DEBUG_VISUAL_SHUMO
    #ifdef DEBUG_SHUMO
    #define DEBUG_SHUMO_PRINT(X) Serial.print(X);
    #define DEBUG_SHUMO_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_SHUMO_PRINT(X) TelnetStream.print(X);
    #define DEBUG_SHUMO_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_SHUMO_PRINT(X) 
    #define DEBUG_SHUMO_PRINTLN(X) 
#endif
//________________ DEBUG SENSOR MQ2 ___________________///
//#define DEBUG_VISUAL_MQ2
//#define DEBUG_MQ2
#ifdef DEBUG_VISUAL_MQ2
    #ifdef DEBUG_MQ2
    #define DEBUG_MQ2_PRINT(X) Serial.print(X);
    #define DEBUG_MQ2_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_MQ2_PRINT(X) TelnetStream.print(X);
    #define DEBUG_MQ2_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_MQ2_PRINT(X) 
    #define DEBUG_MQ2_PRINTLN(X) 
#endif

//______________ DEBUG TEMPERATURA HUMEDAD ____________///
//#define DEBUG_VISUAL_SENSORTH
//#define DEBUG_SENSORTH
#ifdef DEBUG_VISUAL_SENSORTH
    #ifdef DEBUG_SENSORTH
    #define DEBUG_SENSORTH_PRINT(X) Serial.print(X);
    #define DEBUG_SENSORTH_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_SENSORTH_PRINT(X) TelnetStream.print(X);
    #define DEBUG_SENSORTH_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_SENSORTH_PRINT(X) 
    #define DEBUG_SENSORTH_PRINTLN(X) 
#endif
//________________ DEBUG SENSOR VOLTAJE _______________///
//#define DEBUG_VISUAL_SENSORVOLT
//#define DEBUG_SENSORVOLT
#ifdef DEBUG_VISUAL_SENSORVOLT
    #ifdef DEBUG_SENSORVOLT
    #define DEBUG_SENSORVOLT_PRINT(X) Serial.print(X);
    #define DEBUG_SENSORVOLT_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_SENSORVOLT_PRINT(X) TelnetStream.print(X);
    #define DEBUG_SENSORVOLT_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_SENSORVOLT_PRINT(X) 
    #define DEBUG_SENSORVOLT_PRINTLN(X)
#endif
//___________________ DEBUG UDP _______________________///
//#define DEBUG_VISUAL_UPCONN
//#define DEBUG_UPCONN
#ifdef DEBUG_VISUAL_UPCONN
    #ifdef DEBUG_UPCONN
    #define DEBUG_UPCONN_PRINT(X) Serial.print(X);
    #define DEBUG_UPCONN_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_UPCONN_PRINT(X) TelnetStream.print(X);
    #define DEBUG_UPCONN_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_UPCONN_PRINT(X) 
    #define DEBUG_UPCONN_PRINTLN(X) 
#endif
//___________________ DEBUG WEBSERVER _________________///
#define DEBUG_VISUAL_WEBSERVER
#define DEBUG_WEBSERVER
#ifdef DEBUG_VISUAL_WEBSERVER
    #ifdef DEBUG_WEBSERVER
    #define DEBUG_WEBSERVER_PRINT(X) Serial.print(X);
    #define DEBUG_WEBSERVER_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_WEBSERVER_PRINT(X) TelnetStream.print(X);
    #define DEBUG_WEBSERVER_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_WEBSERVER_PRINT(X) 
    #define DEBUG_WEBSERVER_PRINTLN(X)
#endif
//___________________ DEBUG WIFI ___________________///
#define DEBUG_VISUAL_WIFI
#define DEBUG_WIFI
#ifdef DEBUG_VISUAL_WIFI
    #ifdef DEBUG_WIFI
    #define DEBUG_WIFI_PRINT(X) Serial.print(X);
    #define DEBUG_WIFI_PRINTLN(X) Serial.println(X);
    #else
    #define DEBUG_WIFI_PRINT(X) TelnetStream.print(X);
    #define DEBUG_WIFI_PRINTLN(X) TelnetStream.println(X);
    #endif
#else
    #define DEBUG_WIFI_PRINT(X) 
    #define DEBUG_WIFI_PRINTLN(X) 
#endif


//___________________ DEBUG Lector SD ___________________///
//#define DEBUG_VISUAL_FUNCIONES_FILE
//#define DEBUG_FUNCIONES_FILE
#ifdef DEBUG_VISUAL_FUNCIONES_FILE
    #ifdef DEBUG_FUNCIONES_FILE
    #define DEBUG_FUNCIONES_FILEPRINT(x) Serial.print(x);  
    #define DEBUG_FUNCIONES_FILEPRINTLN(x) Serial.println(x); 
    #else
    #define DEBUG_FUNCIONES_FILEPRINT(x)  TelnetStream.print(x);
    #define DEBUG_FUNCIONES_FILEPRINTLN(x) TelnetStream.println(x);
    #endif 
#else 
    #define DEBUG_FUNCIONES_FILEPRINT(x)  
    #define DEBUG_FUNCIONES_FILEPRINTLN(x)
#endif

#endif