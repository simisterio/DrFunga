#ifndef Wifi_h
#define Wifi_h
#include <WiFi.h>
#include <WiFiClient.h>
#include "Controller.hpp"

class Wifi
{
	public:
		Wifi(char *SSID, char *PWD, char *AP_SSID, char *AP_PWD);
		
		void connect_wifi();
		void create_ap();
		void monitorWifi();

		//GETTER
		char *getSSID();
		char *getPWD();
		char *getAP_SSID();
		char *getAP_PWD();
		String getIP();
		String getMAC();
		//SETTER
		void setSSID(char *ssid);
		void setPWD(char *pwd);
		void setAP_SSID(char *ap_ssid);
		void setAP_PWD(char *ap_pwd);
		void setMAC(String MAC);
		void setIP(String IP);
		int isdhcpEnable();
		void enableDhcp();
		void disableDhcp();
		int isAPEnable();
		unsigned long getlastTimeNoNet();
		unsigned long getSearchInterval();
		void setlastTimeNoNet(unsigned long lastTimeNoNet);
		void setSearchInterval(unsigned long searchInterval);
		String GetExternalIP();
		
	private:
		char *ssid;
		char *pwd;
		char *ap_ssid;
		char *ap_pwd;
		String IP;
		String MAC;
		int dhcp = 1;
		int ap = 0;
		unsigned long lastTimeNoNet=0;
		unsigned long searchInterval = 60000; // 1 minuto // 900000;//15minutos
};
#endif
