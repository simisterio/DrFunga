#include "Controller.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>

extern NTPClient timeClient;
extern uint64_t ipoc;
extern uint64_t ipoc_exception;

Controller::Controller(String ID, String server)
{
  this->ID = ID;
  this->server = server;
}

void Controller::setID(String ID)
{
  this->ID = ID;
}
void Controller::setServer(String server)
{
  this->server = server;
}
void Controller::setMAC(String MAC){
  this->MAC = MAC;
}
void Controller::setcodigoApp(String codigoApp)
{
  this->codigoApp = codigoApp;
}
void Controller:: setIP(String IP){
  this->IP = IP;
}
String Controller::getIP(){
  return this->IP;
}
String Controller::getMAC()
{
  return this->MAC;
}
String Controller::getcodigoApp(){
  return this->codigoApp;
}
String Controller::getID()
{
  return this->ID;
}
String Controller::getServer()
{
  return this->server;
}
long Controller::getidUser()
{
  return this->idUser;
}
void Controller::setidUser(long idUser)
{
  this->idUser = idUser;
}

int Controller::getupdateStatus(){
  return this->updateStatus;
}
void Controller::setupdateStatus(int updateStatus){
  this->updateStatus = updateStatus;
}
String Controller::getFw_ver(){
  return this->fw_ver;
}
void Controller::setFw_ver(String fw_ver){
  this->fw_ver = fw_ver;
}
String Controller::getID_MCU(){
  return this->ID_MCU;
}
void Controller::setID_MCU(String ID_MCU){
  this->ID_MCU = ID_MCU;
}

void update_started() {
  DEBUG_CTRLPRINTLN("CALLBACK:  HTTP update process started");
}

void update_finished() {
  DEBUG_CTRLPRINTLN("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void Controller::update_start(){
  setupdateStatus(0);
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;

    // The line below is optional. It can be used to blink the LED on the board during flashing
    // The LED will be on during download of one buffer of data from the network. The LED will
    // be off during writing that buffer to flash
    // On a good connection the LED should flash regularly. On a bad connection the LED will be
    // on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
    // value is used to put the LED on. If the LED is on with HIGH, that value should be passed
   
   /* ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
    // Add optional callback notifiers
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);*/

    DEBUG_CTRLPRINTLN(getupdateServer());

    //t_httpUpdate_return ret = ESPhttpUpdate.update(client, getupdateServer());
    // Or:
    //t_httpUpdate_return ret = ESPhttpUpdate.update(client, "server", 80, "file.bin");
    //OR:
    t_httpUpdate_return ret = ESPhttpUpdate.update(getupdateServer()/*+(String)"/V32Controller.bin"*/);
    //Serial.println(getupdateServer()+(String)"/V32Controller.bin");
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        DEBUG_CTRLPRINTLN("HTTP_UPDATE_OK");
        break;
    }
  }
  else{
    DEBUG_CTRLPRINTLN("Connection Error");
  }
}

int Controller::checkVersion(){
  return 0;
}

void Controller::setupdateServer(String updateServer){
  this->updateServer = updateServer;
}
String Controller::getupdateServer(){
  return this->updateServer;
}

void Controller::reportCredentials(){
  DEBUG_CTRLPRINTLN("reportCredentials");
  HTTPClient http;
  WiFiClient client;
    // Your Domain name with URL path or IP address with path
  http.begin(client, getServer());
    // Specify content-type header
  http.addHeader("Content-Type", "application/json"); 
    // Data to send with HTTP POST
    // Send HTTP POST request
  StaticJsonDocument<512> doc;

  doc["type"] = "0003";
  doc["addr"] = getID()+getID_MCU();
  doc["time"] = ipoc*1000;

  JsonArray content = doc.createNestedArray("content");

  JsonObject content_0 = content.createNestedObject();
  content_0["infoValue"] = getID_MCU();
  content_0["infoAddr"] = "00A1";

  JsonObject content_1 = content.createNestedObject();
  content_1["infoValue"] = getMAC();
  content_1["infoAddr"] = "00A2";

  JsonObject content_2 = content.createNestedObject();
  content_2["infoValue"] = getIP();
  content_2["infoAddr"] = "00A3";

  JsonObject content_3 = content.createNestedObject();
  content_3["infoValue"] = getFw_ver();
  content_3["infoAddr"] = "00A4";

  JsonObject content_4 = content.createNestedObject();
  content_4["infoValue"] = getupdateServer();
  content_4["infoAddr"] = "00A5";

  String output;
  serializeJson(doc, output);
      
  int httpResponseCode1 = http.POST(output);

  DEBUG_CTRLPRINT("HTTP Response code reportCredentials: ");
  DEBUG_CTRLPRINTLN(httpResponseCode1);
  if (httpResponseCode1 == 200)
  {
    this->firstSend = 1;
  }
  else{
    this->firstSend = 0;
  }
  DEBUG_CTRLPRINT("first send = ");
  DEBUG_CTRLPRINTLN(this->firstSend);
    //String payload = http.getString();

    DEBUG_CTRLPRINT("payload Exception: ");
    DEBUG_CTRLPRINTLN(payload);
    // Free resources
  http.end();
}

void Controller::sendCredentials(){
  unsigned long intervaloReporte = 300000;//cada 5 minutos hasta que sea recibido
  if ((unsigned long)(millis() - getlastTimeReport()) > intervaloReporte){
    if(this->firstSend == 0){
      reportCredentials();
      setlastTimeReport();
    }
  }  
}

String Controller::GetExternalIP()
{
  HTTPClient http;
  WiFiClient client;
          // Your Domain name with URL path or IP address with path
  http.begin(client, "http://api.ipify.org");
  
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    DEBUG_CTRLPRINT("HTTP Response code: ");
    DEBUG_CTRLPRINTLN(httpResponseCode);
    payload = http.getString();
  }
  else {
    DEBUG_CTRLPRINT("Error code: ");
    DEBUG_CTRLPRINTLN(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void Controller::reportExternalIP(){
  unsigned long intervaloReporte = 303000;//cada 5 min y 30 seg
  if ((unsigned long)(millis() - (this->lastTimeReportExternIP)) > intervaloReporte)
  {
      
    HTTPClient http;
    WiFiClient client;
          // Your Domain name with URL path or IP address with path
    http.begin(client, getServer());
          // Specify content-type header
    http.addHeader("Content-Type", "application/json"); 
    String msj = GetExternalIP();
    if (msj != "{}")
    { 
      this->externIP = msj;
    }
    else{
      this->externIP = this->externIP;
    }
    StaticJsonDocument<192> doc;

    doc["type"] = "0003";
    doc["addr"] = getID()+getID_MCU();
    doc["time"] = ipoc*1000;;
    JsonObject content_0 = doc["content"].createNestedObject();
    content_0["infoValue"] = this->externIP;
    content_0["infoAddr"] = "00A6";// esto se cambiara
    String output;
    serializeJson(doc, output);

    DEBUG_CTRLPRINT("HTTP Response code IP dynamic: ");
    int httpResponseCode1 = http.POST(output);
    DEBUG_CTRLPRINTLN(httpResponseCode1);
    http.end();
        
    DEBUG_CTRLPRINT("externIP: ");
    DEBUG_CTRLPRINTLN(this->externIP);
    this->lastTimeReportExternIP = millis();
  }
}

unsigned long Controller::getlastTimeReport(){return this->lastTimeReport;}
void Controller::setlastTimeReport(){this->lastTimeReport = millis();}
