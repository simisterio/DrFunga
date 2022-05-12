#ifndef Controller_h
#define Controller_h
#include <WiFi.h>
#include <WiFiClient.h>
#include "../../.pio/libdeps/esp32dev/ESP32httpUpdate/src/ESP32httpUpdate.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>

//#define ARDUINOJSON_USE_LONG_LONG 1

class Controller
{
	public:
		Controller(String ID, String server);
		Controller();

		void setID(String ID);
		void setID_MCU(String ID_MCU);
		void setServer(String server);
		void setupdateServer(String updateServer);
		void setMAC(String MAC);
		void setcodigoApp(String codigoApp);
		void setIP(String IP);
		String getIP();
		String getMAC();
		String	getcodigoApp();
		String getID();
		String getID_MCU();
		String getServer();
		String getupdateServer();
		String getFw_ver();
		void setFw_ver(String fw_ver);
		long getidUser();
		void setidUser(long idUser);
		int getupdateStatus();
		void setupdateStatus(int updateStatus);
		unsigned long getlastTimeReport();
		void setlastTimeReport();
		int checkVersion();
		void update_start();
		void reportCredentials();
		void sendCredentials();
		void reportExternalIP();
		String GetExternalIP();

	private:
		String ID;
		String ID_MCU;
		String server;
		String updateServer;
		String MAC;
		String IP;
		String externIP;
		String fw_ver;
		String codigoApp;
		long idUser=0;
		int updateStatus = 0;
		int firstSend = 0;
		unsigned long lastTimeReport=0; 
		unsigned long lastTimeReportExternIP=0;
};
#endif
