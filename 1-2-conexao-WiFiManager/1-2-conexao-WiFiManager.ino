#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
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
  Serial.println("Reconectando WiFi...");

  WiFiManager wm; // Objeto WiFiManager
  wm.setConfigPortalTimeout(20);
  bool res;

  // Se conecta automaticamente com WiFiManager
  res = wm.autoConnect("AgriTec", "laboratorio"); // AP protegido por senha
  if (!res) {
    Serial.println("Falha ao conectar...");
    delay(500);
  }
}
