#include "header.hpp"
#include "global.hpp"
#include "..\include\debug.hpp"

/*________Puntero a Tarea para boton_____*/
TaskHandle_t taskBoton;
/*______Definicion Controlador______*/
Controller mcu(ID_GABINETE, SERVER);
/*_Instancias Sensores_*/
SensorTH sTH = SensorTH(DHTTYPE, DI6, "ANALOGICO", "INPUT");
/*_Instancias Calentador_*/
Calentador calentador = Calentador(DO1, DI4,"NA");
/*_Instancia Boton_*/
Boton btnEmergencia(DI5, "DIGITAL", "INPUT");
/*_Instancias Wifi_*/
Wifi wifi(STA_SSID, STA_PWD, AP_SSID, AP_PWD);
/*_Instancias WebServer_*/
WebServerESP webServer;
/*_LEDS_*/
LED ledRojo = LED(DO2, "ROJO");
LED ledVerde = LED(DO3, "VERDE");

/*_Define NTP Client to get time_*/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, utcOffsetInSeconds);
uint64_t ipoc;
uint64_t ipoc_exception;

void taskBotoncode(void * parameter)
{
    while (true)
    {
        //DEBUG_BOTONPRINTLN("El estado de Cerradura PS es: ");
        //DEBUG_BOTONPRINTLN(sCerraduraPS.readSensorData());
        boolean state =btnEmergencia.antiRebote();
        if(!state)
        {
            DEBUG_BOTONPRINTLN("Apagar Calentador Agua");
            calentador.operarApertura();
            delay(100);
            DEBUG_BOTONPRINTLN("Esta corriendo el Task Boton");
        }
    }
}

void setup()
{
    Serial.begin(115200);
    sTH.init();
    sTH.setNombre("Sensor Temperatura y Humedad");

     /*_Uso de task para monitoreo de boton_*/
    xTaskCreatePinnedToCore
    (
        taskBotoncode, /* Function to implement the task */
        "TaskBoton",   /* Name of the task */
        10000,         /* Stack size in words */
        NULL,          /* Task input parameter */
        0,             /* Priority of the task */
        &taskBoton,    /* Task handle. */
        0
    );            /* Core where the task should run */

    mcu.setID_MCU(ID_MCU);
    //wifi.disableDhcp();
    WiFi.mode(WIFI_MODE_APSTA); 
    //WiFi.softAP(AP_SSID, AP_PWD); 
    wifi.create_ap();
    wifi.connect_wifi();
    webServer.initServer();
    DEBUG_CONTROLADOR1_PRINTLN(wifi.getIP());
    DEBUG_CONTROLADOR1_PRINTLN(wifi.getMAC());
    
    mcu.setMAC(wifi.getMAC());
    mcu.setIP(wifi.getIP());
    mcu.setupdateServer("http://192.168.1.150:3000/update1");
    DEBUG_CONTROLADOR1_PRINT("ID GABINETE: ");
    DEBUG_CONTROLADOR1_PRINTLN(mcu.getID().c_str());
    DEBUG_CONTROLADOR1_PRINT("ID MCU: ");
    DEBUG_CONTROLADOR1_PRINTLN(mcu.getID_MCU().c_str());
    mcu.setFw_ver(VERSION);
    DEBUG_CONTROLADOR1_PRINT("Firmware: ");
    DEBUG_CONTROLADOR1_PRINTLN(mcu.getFw_ver().c_str());
    //udp.initListening();
    //DEBUG_CONTROLADOR1_PRINT("setup() running on core ");
    // DEBUG_CONTROLADOR1_PRINTLN(xPortGetCoreID());
    // Remote Debug  
    TelnetStream.begin(); 
}

void loop() 
{
    switch (TelnetStream.read())
    {
      case 'R':
      TelnetStream.stop();
      delay(100);
      ESP.restart();
        break;
      case 'C':
        TelnetStream.println("bye bye");
        TelnetStream.stop();
        break;
    }

    delay(500);
    wifi.monitorWifi();
    mcu.setIP(wifi.getIP());
    webServer.handleClient();
    timeClient.update();
    ipoc = timeClient.getEpochTime();
    float TempActual = sTH.getTemp();
    float HumdActual = sTH.getHum();

    if(mcu.getupdateStatus()){mcu.update_start();}
    else
    {
        if (sTH.isEnabled()) 
        {
            sTH.periodicReport();
            sTH.exceptionReport();
            if (isnan(TempActual))
            {
                Serial.println("Problema Sensor Temperatura: NaN");
                ledVerde.intermitente();
            }
            else
            {
                ledVerde.encender();
                if (TempActual <= 22.0)
                {
                    Serial.print("ALERTA Temperatura Ambiente baja: ");
                    Serial.println(TempActual);
                    Serial.println("Activando Calentador");
                    calentador.operarCerrarAbrir(2*MIN);
                    //ledRojo.intermitenteFinito(2*MIN);
                    //ledVerde.intermitenteFinito(2*MIN);
                }
                else
                {
                    ledRojo.encender();
                    calentador.operarApertura();
                }
            }

            if(isnan(HumdActual)){Serial.println("Problema Sensor Humedad: NaN");}
            else
            {
                if(HumdActual < 82.0)
                {
                    Serial.print("ALERTA Humedad baja");
                    Serial.println(HumdActual);
                    ledVerde.intermitente();
                }
                else{ledVerde.encender();}
            }
        }  
    }
}