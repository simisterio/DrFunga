#include "WebServerESP.hpp"
#include "Boton.hpp"
#include "Sensor.hpp"
#include "SensorTH.hpp"
#include "SensorVoltaje.hpp"
#include "Controller.hpp"
#include "../../include/debug.hpp"
#include <TelnetStream.h>
//#include "../include/externs.hpp"
//#include <externs.hpp>


extern SensorVoltaje sVolt;
extern SensorTH sTH;
extern Sensor sHumo;
extern Sensor sPPretorno;
extern Sensor sPSretorno;
extern Sensor sAC;
extern Sensor sCerraduraPP;
extern Sensor sCerraduraPS;
extern Sensor sDetectPer;
extern Boton btnEmergencia;

extern Controller mcu;
WebServer server(80);

WebServerESP::WebServerESP(){}

void handleSomeData(){
}

void WebServerESP::handleClient(){
    server.handleClient();
}

void WebServerESP::initServer(){
    server.on("/", HTTP_GET, std::bind(&WebServerESP::handleRoot,this));
    server.on("/operation", HTTP_POST, std::bind(&WebServerESP::handleLock,this));
    server.on("/scan", HTTP_POST, std::bind(&WebServerESP::handleScan,this));
    server.on("/update", HTTP_POST, std::bind(&WebServerESP::handleUpdate, this));
    server.on("/idUser", HTTP_POST, std::bind(&WebServerESP::handleIdUser, this));  
    server.on("/fwver", HTTP_GET, std::bind(&WebServerESP::handleFw_ver, this));
    server.on("/setInfoAddr", HTTP_POST, std::bind(&WebServerESP::HandleSetInfoAddr,this));

  // Set not found response
    server.onNotFound(std::bind(&WebServerESP::handleNotFound,this));
    server.begin();
    DEBUG_WEBSERVER_PRINTLN("Web Server has started");
}

void WebServerESP::handleRoot()
{
    server.send(200, "text/html", "<h1>Welcome to EMERGENCY ACCESS CONTROL</h1>");
}

void WebServerESP::handleLock()
{

    DEBUG_WEBSERVER_PRINTLN("handleLock");
    if (server.hasArg("plain") == false) { //Check if body received
        server.send(400, "text/plain", "Bad request: body not received");
      }

    else 
    { // we received a body, hopefully our JSON data
        String message = server.arg("plain");
        message += "\n";
        // Allocate the JSON document
        // Use arduinojson.org/v6/assistant to compute the capacity.
        
        StaticJsonDocument<192> doc;
        deserializeJson(doc, message);
  
        const char* macMCU = doc["macMCU"]; // "xx:xx:xx:xx:xx"
        const char* securityCode = doc["securityCode"]; // "xxxxyyyzzz"
        const char* typeSelected = doc["typeSelected"]; // "Puerta Principal"

        /*const size_t capacity = JSON_OBJECT_SIZE(3) + 80;*/
    
       // DynamicJsonDocument doc(capacity);
        // Parse JSON object
        
        DeserializationError error = deserializeJson(doc, message);
        
      
        if (error)
        {
          DEBUG_WEBSERVER_PRINT("deserializeJson() failed: ");
          DEBUG_WEBSERVER_PRINTLN(error.c_str());
          return;
        }
        
        String code = doc["securityCode"].as<String>(); // "xxxyyyzzz"
        // Extract values
        DEBUG_WEBSERVER_PRINT("Response:");
        DEBUG_WEBSERVER_PRINTLN(code);

        DEBUG_WEBSERVER_PRINT("Codigo Puerta: ");
        DEBUG_WEBSERVER_PRINTLN(d1.getCodigo());
        if (String(typeSelected) == String(d1.getTipoAcceso()))
        {
          if (d1.validarAcceso(code))
          {
            StaticJsonDocument<96> doc;

            doc["macMCU"] = mcu.getID();
            doc["result"] = "Successful";

            String json;
            serializeJson(doc, json);

            server.send(200, "text/json", json);

            DEBUG_WEBSERVER_PRINT("Especificacion puerta: ");
            DEBUG_WEBSERVER_PRINTLN(d1.getEsp());
            //r1.operarAbrirCerrar(5000);
            d1.operarAbrirCerrar(5000);
            return;
          }
          else
          {
            StaticJsonDocument<96> doc;

            doc["macMCU"] = mcu.getID();
            doc["result"] = "Failed";
            String json;
            serializeJson(doc, json);
            server.send(404, "text/json", json);
          }   
        }
        else if (String(typeSelected) == String(d2.getTipoAcceso()))
        {
          if (d2.validarAcceso(code))
          {
            StaticJsonDocument<96> doc;

            doc["macMCU"] = mcu.getID();
            doc["result"] = "Successful";

            String json;
            serializeJson(doc, json);

            server.send(200, "text/json", json);

            DEBUG_WEBSERVER_PRINT("Especificacion puerta: ");
            DEBUG_WEBSERVER_PRINTLN(d2.getEsp());
            //r2.operarAbrirCerrar(5000);
            d2.operarAbrirCerrar(5000);
            return;
          }
          else
          {
            StaticJsonDocument<96> doc;

            doc["macMCU"] = mcu.getID();
            doc["result"] = "Failed";

            String json;
            serializeJson(doc, json);
            server.send(404, "text/json", json);
          } 
        }
        else
        {
          DEBUG_WEBSERVER_PRINT("typeSelected:");
          DEBUG_WEBSERVER_PRINTLN(typeSelected);
          DEBUG_WEBSERVER_PRINT("d1: ");
          DEBUG_WEBSERVER_PRINTLN(d1.getTipoAcceso());
          DEBUG_WEBSERVER_PRINT("d2: ");
          DEBUG_WEBSERVER_PRINTLN(d2.getTipoAcceso());
        }
    }    
}

void WebServerESP::handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    } 
    server.send(404, "text/plain", message);
}

void WebServerESP::handleScan()
{
    DEBUG_WEBSERVER_PRINTLN("Scan");
    if (server.hasArg("plain") == false) { //Check if body received
        server.send(400, "text/plain", "Bad request: body not received");
      }
    else 
    { // we received a body, hopefully our JSON data
        String message = server.arg("plain");
        message += "\n";
        // Allocate the JSON document
        // Use arduinojson.org/v6/assistant to compute the capacity.
        
        StaticJsonDocument<48> doc;
        deserializeJson(doc, message);
        DeserializationError error = deserializeJson(doc, message);
        
        if (error)
        {
          DEBUG_WEBSERVER_PRINT(F("deserializeJson() failed: "));
          DEBUG_WEBSERVER_PRINTLN(error.c_str());
          return;
        }
        
        String code = doc["codeApp"].as<String>(); // "lula"
        // Extract values
        DEBUG_WEBSERVER_PRINTLN(F("Response:"));
        DEBUG_WEBSERVER_PRINTLN(code);

        DEBUG_WEBSERVER_PRINT("Codigo App: ");
        DEBUG_WEBSERVER_PRINTLN(mcu.getcodigoApp());
        if (code == mcu.getcodigoApp())
        {
          
          StaticJsonDocument<1024> doc;

          doc["addr"] = mcu.getMAC();
          doc["ip"] = mcu.getIP();

          JsonArray content = doc.createNestedArray("content");
          if (sPPretorno.isEnabled())
          {
            JsonObject content_0 = content.createNestedObject();
            content_0["deviceName"] = d1.getTipoAcceso();
            content_0["signalType"] = sPPretorno.getSensorTipoDato();
            content_0["state"] = sPPretorno.readSensorData();  
          }
          if (sTH.isEnabled())
          {
            JsonObject content_1 = content.createNestedObject();
            content_1["deviceName"] = "Sensor Temperatura";//sTH.getNombre();
            content_1["signalType"] = sTH.getSensorTipoDato();
            content_1["state"] = sTH.getTemp();
            
            JsonObject content_2 = content.createNestedObject();
            content_2["deviceName"] = "Sensor Humedad";//sTH.getNombre();
            content_2["signalType"] = sTH.getSensorTipoDato();
            content_2["state"] = sTH.getHum();
          }
          if (sVolt.isEnabled())
          {
            JsonObject content_3 = content.createNestedObject();
            content_3["deviceName"] = sVolt.getNombre();
            content_3["signalType"] = sVolt.getSensorTipoDato();
            content_3["state"] = sVolt.getVoltage();
          }
          if (sHumo.isEnabled())
          {
            JsonObject content_4 = content.createNestedObject();  
            content_4["deviceName"] = sHumo.getNombre();
            content_4["signalType"] = sHumo.getSensorTipoDato();
            content_4["state"] = sHumo.readSensorDataAnalog();
          }

          if (sPSretorno.isEnabled())
          {    
            JsonObject content_5 = content.createNestedObject();
            content_5["deviceName"] = d2.getTipoAcceso();
            content_5["signalType"] = sPSretorno.getSensorTipoDato();
            content_5["state"] = sPSretorno.readSensorData();
          }
          if (sAC.isEnabled())
          {    
            JsonObject content_7 = content.createNestedObject();
            content_7["deviceName"] = sAC.getNombre();
            content_7["signalType"] = sAC.getSensorTipoDato();
            content_7["state"] = sAC.readSensorData();
          }
          if (sCerraduraPP.isEnabled())
          {    
            JsonObject content_8 = content.createNestedObject();
            content_8["deviceName"] = sCerraduraPP.getNombre();
            content_8["signalType"] = sCerraduraPP.getSensorTipoDato();
            content_8["state"] = sCerraduraPP.readSensorData();
          }
          if (sCerraduraPS.isEnabled())
          {    
            JsonObject content_8 = content.createNestedObject();
            content_8["deviceName"] = sCerraduraPS.getNombre();
            content_8["signalType"] = sCerraduraPS.getSensorTipoDato();
            content_8["state"] = sCerraduraPS.readSensorData();
          }
          if (btnEmergencia.isEnabled())
          {    
            JsonObject content_9 = content.createNestedObject();
            content_9["deviceName"] = btnEmergencia.getNombre();
            content_9["signalType"] = btnEmergencia.getSensorTipoDato();
            content_9["state"] = btnEmergencia.readSensorData();
          }

          String json;
          serializeJson(doc, json);
          server.send(200, "text/json", json);
        }
        else
        {
          doc["addr"] = mcu.getMAC();
          doc["ip"] = mcu.getIP();
          doc["result"] = "Failed";

          String json;
          serializeJson(doc, json);
          server.send(404, "text/json", json);
        }
    } 
}

void WebServerESP::handleUpdate()
{
  DEBUG_WEBSERVER_PRINT("handle update");
  if (server.hasArg("plain") == false) { //Check if body received
    server.send(400, "text/plain", "Bad request: body not received");
  }
  else{
    String ipCliente;
    ipCliente = server.client().remoteIP().toString();

    String message = server.arg("plain");
    message += "\n";      
        
    StaticJsonDocument<64> doc;
    
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
      DEBUG_WEBSERVER_PRINT(F("deserializeJson() failed: "));
      DEBUG_WEBSERVER_PRINTLN(error.f_str());
      return;
    }
    
    int update = doc["update"]; // 1
    String mcu_id = doc["mcu"].as<String>();
    DEBUG_WEBSERVER_PRINT("mensaje: ");
    DEBUG_WEBSERVER_PRINTLN(update);

    if (mcu_id == mcu.getID_MCU() && mcu_id == "0001")
    {
      mcu.setupdateServer("http://"+ipCliente+":3000/update1");
    }
    else if (mcu_id == mcu.getID_MCU() && mcu_id == "0002")
    {
      mcu.setupdateServer("http://"+ipCliente+":3000/update2");
    }
    else if(mcu_id == mcu.getID_MCU() && mcu_id == "0004"){
      mcu.setupdateServer("http://"+ipCliente+":3000/update4");

    }
    else if (mcu_id == mcu.getID_MCU() && mcu_id == "mcu_TEST")
    {
      mcu.setupdateServer("http://"+ipCliente+":3000/updateTEST");
    }
    else{
      DEBUG_WEBSERVER_PRINTLN("error id mcu solicitada");
      return;
    }
    StaticJsonDocument<48> doc2;
    String json;
    if(update){
      mcu.setupdateStatus(1);//updateStatus = 1;
      doc2["result"] = "Successful";
      serializeJson(doc2, json);
      server.send(200, "text/json", json); 
    }
    else{
      mcu.setupdateStatus(0);
      doc2["result"] = "Failed";
      String json;
      serializeJson(doc2, json);
      server.send(200, "text/json", json); 
    }
  } 
}
void WebServerESP::handleIdUser(){
  if (server.hasArg("plain") == false) { //Check if body received
    server.send(400, "text/plain", "Bad request: body not received");
  }
  else 
  { // we received a body, hopefully our JSON data
    String message = server.arg("plain");
    message += "\n";
    // Allocate the JSON document
    // Use arduinojson.org/v6/assistant to compute the capacity.
      
    StaticJsonDocument<48> doc;
    deserializeJson(doc, message);
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
      DEBUG_WEBSERVER_PRINT(F("deserializeJson() failed: "));
      DEBUG_WEBSERVER_PRINTLN(error.f_str());
      return;
    }

    int idUser = doc["idUser"]; // 0
    if (idUser == 0)
    {
      mcu.setidUser(idUser); 
      sDetectPer.setData(0);
    }
    else{
      if (idUser != mcu.getidUser())
      {
        mcu.setidUser(idUser); 
        sDetectPer.setData(sDetectPer.getData() + 1); //en clase sensor se envia el iduser que almacena mcu, solo se suma uno para activar reporte por excepcion
      }
      else{
        mcu.setidUser(idUser); 
        sDetectPer.setData(sDetectPer.getData());
      }
    }
    StaticJsonDocument<96> doc2;
    doc2["Gabinete"] = mcu.getID();
    doc2["mcu"] = mcu.getID_MCU();
    doc2["idUser"] = mcu.getidUser();
    String json;
    serializeJson(doc2, json);
    server.send(200, "text/json", json);  
  }
}
int WebServerESP::getPort(){
  return this->port;
}
void WebServerESP::setPort(int port){
  this->port =port;
}
void WebServerESP::handleFw_ver(){

    StaticJsonDocument<96> doc;

    doc["Gabinete"] = mcu.getID();
    doc["FW_ver"] = mcu.getFw_ver();
    String json;
    serializeJson(doc, json);
    server.send(200, "text/json", json);  

}
void WebServerESP::HandleSetInfoAddr(){

  DEBUG_WEBSERVER_PRINT("handle update");
  if (server.hasArg("plain") == false) { //Check if body received
    server.send(400, "text/plain", "Bad request: body not received");
  }
  else{
    // we received a body, hopefully our JSON data
    String input = server.arg("plain");
    input += "\n";
    // Allocate the JSON document
    // Use arduinojson.org/v6/assistant to compute the capacity.
    // String input;

    StaticJsonDocument<128> doc;
    deserializeJson(doc, input);
    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      DEBUG_WEBSERVER_PRINT(F("deserializeJson() failed: "));
      DEBUG_WEBSERVER_PRINTLN(error.f_str());
      return;
    }

    String Gabinete = doc["Gabinete"]; // "0390"
    String Signal = doc["Signal"]; // "Sensor Humo"
    String info_Addr = doc["info Addr"]; // "0006"
    StaticJsonDocument<128> doc2;

    doc2["Gabinete"] = mcu.getID();
    doc2["Signal"] = Signal;
    

    if(mcu.getID() == Gabinete){
      if (Signal == (String) sVolt.getNombre())
      { 
        sVolt.setInfoAddr(info_Addr);
        doc2["info Addr"] = sVolt.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sHumo.getNombre())
      {
        sHumo.setInfoAddr(info_Addr);
        doc2["info Addr"] = sHumo.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sPPretorno.getNombre())
      {
        sPPretorno.setInfoAddr(info_Addr);
        doc2["info Addr"] = sPPretorno.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sPSretorno.getNombre())
      {
        sPSretorno.setInfoAddr(info_Addr);
        doc2["info Addr"] = sPSretorno.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sAC.getNombre())
      {
        sAC.setInfoAddr(info_Addr);
        doc2["info Addr"] = sAC.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sCerraduraPP.getNombre())
      {
        sCerraduraPP.setInfoAddr(info_Addr);
        doc2["info Addr"] = sCerraduraPP.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sCerraduraPS.getNombre())
      {
        sCerraduraPS.setInfoAddr(info_Addr);
        doc2["info Addr"] = sCerraduraPS.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sDetectPer.getNombre())
      {
        sDetectPer.setInfoAddr(info_Addr);
        doc2["info Addr"] = sDetectPer.getInfoAddr();
        doc2["result"] = "Success";
      }
      else if (Signal ==  (String) sTH.getNombreHum())
      {
        sTH.setInfoAddr(info_Addr, sTH.getNombreHum());
        doc2["info Addr"] = sTH.getInfoAddr(Signal);
        doc2["result"] = "Success";
      }
      else if (Signal == (String) sTH.getNombreTemp())
      {
        sTH.setInfoAddr(info_Addr, sTH.getNombreTemp());
        doc2["info Addr"] = sTH.getInfoAddr(Signal);
        doc2["result"] = "Success";
      }
      else{
        doc2["info Addr"] = info_Addr;
        doc2["result"] = "Failed";
      }
    }

    String output;
    serializeJson(doc2, output);
    server.send(200, "text/json", output);  
  }
}

