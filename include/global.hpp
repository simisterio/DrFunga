#ifndef GLOBALS_h
#define GLOBALS_h
/*____GPIO____*/
/*___Inputs___*/
#define DI1  26     //Ppal 1
#define DI2  27     //Psec  1
#define DI3  32     //Ppal 2 
#define DI4  33     //Psec 2 
#define DI5  25     //Btn   
#define DI6  4      //DHT22
#define DI7  5      // CS Lector MicroSD
/*__ Outputs__*/
#define DO1  21     //rele Ppal 1  
#define DO2  22     //rele Psec  2
#define DO3  23     //rele Libre (baliza)
/*__Analog Inputs__*/
#define AI1  36     //Voltaje 
#define AI2  35     //MQ2
/*___DHT SENSOR___*/
#define DHTTYPE DHT22

/*________ Credenciales WiFi_______*/
char STA_SSID [] =  "VTR-8009866";//"VER2D2_9999";////"Vertice_Consultores";//  "VTR-0623887";// "Jorjolo";//
char STA_PWD  [] =   "4hrgpdBHnnh5";//"L7l@1234";//"vertice2015"; // "q6wHmdq5dydg";// "awaeweiwiowouwu";// 
char AP_SSID  [] =  "VER2D2_BKP";
char AP_PWD   [] = "L7l@1234";

/*______ GABINENTE______*/
#define ID_GABINETE "9999"
/*______ MCU CREDENTIALS______*/

#define ID_MCU "0004"
#define PWD_MCU "lula"
#define VERSION "ver32_1_NA_1_1.0_ENEL"
/*______SERVIDOR REAL-IoT____*/
#define SERVER "http://191.239.249.109:8082/newData?DRIV_ID=51"
/*______ NTP CLIENT______*/
#define NTP_SERVER "1.south-america.pool.ntp.org"
const long utcOffsetInSeconds = 0;

/*____TIEMPO_____*/
#define SEG 1000
#define MIN 60000
#define HRS 3600000
#define DIA 86400000
#define LOCK_ALARM_TIME 1*DIA // 1 DIA

#endif