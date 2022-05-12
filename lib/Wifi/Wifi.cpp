#include "Wifi.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>


extern Controller mcu;

Wifi::Wifi(char *SSID, char *PWD, char *AP_SSID, char *AP_PWD)
{
  setSSID(SSID);
  setPWD(PWD);
  setAP_SSID(AP_SSID);
  setAP_PWD(AP_PWD);

}

void Wifi::connect_wifi()
{
  //WiFi.disconnect();
  //WiFi.mode(WIFI_STA)
  if (isdhcpEnable())
  {
    WiFi.begin(getSSID(), getPWD());
  }
  else
  {
    IPAddress local_IP;
    if (mcu.getID_MCU() == "0001")
    {
      IPAddress IP(192, 168, 0, 141);       // Modificacion realizada por cambio de router
      local_IP=IP;
    }
    else if(mcu.getID_MCU() == "0002"){
      IPAddress IP(192, 168, 5, 142);       // Modificacion realizada por cambio de router
      local_IP=IP;
    }
    else if(mcu.getID_MCU() == "0004"){
        IPAddress IP(192, 168, 5, 144);
        local_IP=IP;
    }
    // Set your Gateway IP address
    IPAddress gateway(192, 168, 5, 1);      // Modificacion realizada por cambio de router

    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(8, 8, 8, 8);   //optional
    IPAddress secondaryDNS(8, 8, 4, 4); //optional
      // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
      DEBUG_WIFI_PRINTLN("STA Failed to configure");
    }

    WiFi.begin(getSSID(), getPWD());
  }

  while (WiFi.status() != WL_CONNECTED )
  {
    if ((unsigned long)(millis() - getlastTimeNoNet() > getSearchInterval()))
    {
      DEBUG_WIFI_PRINTLN("Restart mcu");
      delay(1500);
      ESP.restart();
    }
     DEBUG_WIFI_PRINT(WiFi.status());
     delay(500);
     DEBUG_WIFI_PRINT(".");  
  }
  DEBUG_WIFI_PRINTLN();
  DEBUG_WIFI_PRINT("Connected, IP address: ");
  DEBUG_WIFI_PRINTLN(WiFi.localIP());
  setIP(WiFi.localIP().toString());
  //DEBUG_WIFI_PRINT(getIP());
  setMAC(String(WiFi.macAddress()));
    //setIP(IpAddress2String(WiFi.localIP()));
}
int Wifi::isAPEnable(){
  return this->ap;
}
int Wifi::isdhcpEnable(){
  return this->dhcp;
}
void Wifi::enableDhcp(){
  this->dhcp = 1;
}
void Wifi::disableDhcp(){
  this->dhcp = 0;
}
void Wifi::create_ap()
{
  DEBUG_WIFI_PRINT("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(getAP_SSID(), getAP_PWD());

    IPAddress myIP = WiFi.softAPIP();
    DEBUG_WIFI_PRINT("AP IP address: ");
    DEBUG_WIFI_PRINTLN(myIP);
    setMAC(String(WiFi.macAddress()));
    setIP(WiFi.softAPIP().toString());
}
void Wifi::monitorWifi()
{
  if (isAPEnable() )
  {
    return;
  }
  else{
    if (WiFi.status() != WL_CONNECTED)
    {
      setlastTimeNoNet(millis());
      WiFi.disconnect();
      delay(5000);
      connect_wifi();
      mcu.setIP(getIP());
    } 
  } 
}

void Wifi::setSSID(char *ssid)
{
  this->ssid=ssid;
}
void Wifi::setPWD(char *pwd)
{
  this->pwd=pwd;
}
void Wifi::setAP_SSID(char *ap_ssid)
{
  this->ap_ssid=ap_ssid;
}
void Wifi::setAP_PWD(char *ap_pwd)
{
  this->ap_pwd=ap_pwd;
}
void Wifi::setMAC(String MAC)
{
  this->MAC=MAC;
}
void Wifi::setIP(String IP)
{
  this->IP=IP;
}
char *Wifi::getSSID()
{
  return this->ssid;
}
char *Wifi::getPWD()
{
  return this->pwd;
}
char *Wifi::getAP_SSID()
{
  return this->ap_ssid;
}
char *Wifi::getAP_PWD()
{
  return this->ap_pwd;
}
String Wifi::getIP()
{
  return this->IP;
}
String Wifi::getMAC()
{
  return this->MAC;
}
unsigned long Wifi::getlastTimeNoNet(){
  return this->lastTimeNoNet;
}
unsigned long Wifi::getSearchInterval(){
  return this->searchInterval;
}
void Wifi::setlastTimeNoNet(unsigned long lastTimeNoNet){
  this->lastTimeNoNet = lastTimeNoNet;
}
void Wifi::setSearchInterval(unsigned long searchInterval){
  this->searchInterval = searchInterval;
}
    
String Wifi::GetExternalIP()
{
 /* WiFiClient client;
  if (!client.connect("api.ipify.org", 80)) {
    DEBUG_WIFI_PRINTln("Failed to connect with 'api.ipify.org' !");
  }
  else {
    int timeout = millis() + 5000;
    client.print("GET /?format=json HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n");
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        DEBUG_WIFI_PRINTln(">>> Client Timeout !");
        client.stop();
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      String externIP = (String) msg;
      free(msg);
    }
    return externIP;
  }
  return "";*/
  return "";
}