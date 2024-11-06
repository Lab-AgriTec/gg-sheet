// ----------------------------------------------------------------------------------------------
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h> // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClientSecure.h
// ----------------------------------------------------------------------------------------------
String GAS_ID = "AKfycbygteblz2FtQAJUWmwvUh40QFfSYQ6Gb7xhxq2w-GNr6bwgWpJiBgt5YtZBXX7LrWbZ"; //Código de implatação do Apps Script
const char* host = "script.google.com"; // Host de conexão do Apps Script

// ----------------------------------------------------------------------------------------------
int cont = 0;

// ----------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  connectWiFi();
}
// ----------------------------------------------------------------------------------------------
void loop() {
  
  if (WiFi.status() == WL_CONNECTED){  
    update_google_sheet();   //envia os dados para o google sheet
    Serial.print("Contador: "); 
    Serial.println(cont); 
    Serial.println("");
    
    cont += 1;    
  }else{
    connectWiFi();      //verifica a conexão com a internet         
  }
  delay(5000);
}
// ----------------------------------------------------------------------------------------------
//Função para Conexão com Internet
void connectWiFi() {

  Serial.println("Conectando WiFi...");

  WiFiManager wm; // Objeto WiFiManager
  wm.setConfigPortalTimeout(60);
  bool res;

  // Tentar conectar automaticamente com WiFiManager
  res = wm.autoConnect("AgriTec", "laboratorio"); // AP protegido por senha
  if (!res) {
    Serial.println("Falha ao conectar...");
    delay(500);
  }
}
// ----------------------------------------------------------------------------------------------
void update_google_sheet() {
  Serial.print("Conectando-se a ");
  Serial.println(host);
  
  WiFiClientSecure client;
  const int httpPort = 443; // 80 para HTTP / 443 para HTTPS!
  
  client.setInsecure();

  if (!client.connect(host, httpPort)) {
    Serial.println("Falha ao conectar ao Google Sheets");
    return;
  }       

  String url = "/macros/s/" + GAS_ID + "/exec?";
  url += "contador=";
  url += String(cont);

  //  /macros/s/AKfycbygteblz2FtQAJUWmwvUh40QFfSYQ6Gb7xhxq2w-GNr6bwgWpJiBgt5YtZBXX7LrWbZ/exec?contador=0
 
  Serial.print("Solicitando URL: "); Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  Serial.println("Conexão fechada");
  delay(100);
}
