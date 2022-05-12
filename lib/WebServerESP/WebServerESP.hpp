#include <WebServer.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//#define ARDUINOJSON_USE_LONG_LONG 1
//#include <ArduinoJson.h>
#include "Controller.hpp"
//#include "Rele.h"
#ifndef WebServerESP_h
#define WebServerESP_h

#include "Arduino.h"

class WebServerESP {
    public:
    	
        WebServerESP();
        void initServer();
        void handleClient();
        void handleRoot(); 
 		void handleNotFound();
		void handleLock();
        void handleScan();
        void handleUpdate();
        void handleIdUser();
        void handleFw_ver();
        void HandleSetInfoAddr();
        int getPort();
        void setPort(int port);
    private:
        int port = 1111;
};

#endif	
