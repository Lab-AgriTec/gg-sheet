#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClientSecure.h> //https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClientSecure.h
#include <DHT.h>  //https://github.com/adafruit/DHT-sensor-library
// ----------------------------------------------------------------------------------------------
const int pinDatos = 13;
float temperatura = 0, umidade = 0;
DHT dht(pinDatos, DHT22);
// ----------------------------------------------------------------------------------------------
String GAS_ID = "AKfycbygteblz2FtQAJUWmwvUh40QFfSYQ6Gb7xhxq2w-GNr6bwgWpJiBgt5YtZBXX7LrWbZ"; //Código de implatação do Apps Script
const char* host = "script.google.com"; // Host de conexão do Apps Script
// ----------------------------------------------------------------------------------------------
#define UPDATE_INTERVAL_HOUR  (0)
#define UPDATE_INTERVAL_MIN   (1)
#define UPDATE_INTERVAL_SEC   (0)

#define UPDATE_INTERVAL_MS    ( ((UPDATE_INTERVAL_HOUR*60*60) + (UPDATE_INTERVAL_MIN * 60) + UPDATE_INTERVAL_SEC ) * 1000 )

unsigned long time_ms;
unsigned long time_read;
unsigned long time_sheet_update_buf;
unsigned long time_dif;
// ----------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  conexaoWiFi(); 
}
// ----------------------------------------------------------------------------------------------
void loop() {
  
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  //Impressão no Serial Monitor a cada 2s
  time_ms = millis();
  time_dif = time_ms - time_read;
  if ( time_dif >= 2000 ){    //2000 milissegundos = 2 segundos
    time_read = time_ms;
    printLeituraDHT();
  }

  //Atualização de dados para o google sheets no período determinado por UPDATE_INTERVAL_MS
  time_ms = millis();
  time_dif = time_ms - time_sheet_update_buf;  
  if (time_dif >= UPDATE_INTERVAL_MS){
    time_sheet_update_buf = time_ms;
    
    if (WiFi.status() == WL_CONNECTED){   
      update_google_sheet();   //envia os dados para o google sheet              (em GoogleSheets.h)
      resetData();           //zera todos os dados para receber os novos dados  (em DataReset.h)
    }else{
      conexaoWiFi();      //verifica a conexão com a internet                 (em ConnWiFi.h)
    }  
  }
}
// ----------------------------------------------------------------------------------------------
void conexaoWiFi(){
  Serial.println("Reconectando WiFi...");

  WiFiManager wm; // Objeto WiFiManager
  wm.setConfigPortalTimeout(30);
  bool res;

  // Se conecta automaticamente com WiFiManager
  res = wm.autoConnect("AgriTec", "laboratorio"); // AP protegido por senha
  if (!res) {
    Serial.println("Falha ao conectar...");
    delay(500);
  }
}
// ----------------------------------------------------------------------------------------------
void printLeituraDHT(){
  Serial.print("Temperatura: "); Serial.println(temperatura);
  Serial.print("Umidade: "); Serial.println(Umidade); 
  Serial.println("");
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
  url += "temperatura=" + String(temperatura);
  url += "&umidade=" + String(umidade);

  //  /macros/s/AKfycbygteblz2FtQAJUWmwvUh40QFfSYQ6Gb7xhxq2w-GNr6bwgWpJiBgt5YtZBXX7LrWbZ/exec?temperatura=0&umidade=0
 
  Serial.print("Solicitando URL: "); Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  Serial.println("Conexão fechada");
  delay(100);
}