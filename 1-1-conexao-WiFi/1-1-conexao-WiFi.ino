#include <WiFi.h>
// ----------------------------------------------------------------------------------------------
char ssid[] = "seu_ssid";
char pass[] = "sua_senha";
// ----------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  conexaoWiFi();  
}
// ----------------------------------------------------------------------------------------------
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Rede Conectada");
    Serial.println("");
  }else{
    Serial.println("");
    Serial.println("Rede DESconectada");
    Serial.println("");
    conexaoWiFi();
  }
  delay(3000);
}
// ----------------------------------------------------------------------------------------------
void conexaoWiFi(){
  Serial.println("Conectando WiFi...");

  WiFi.begin(ssid, pass); //--> Connect to your WiFi router
  Serial.print(".");
}
