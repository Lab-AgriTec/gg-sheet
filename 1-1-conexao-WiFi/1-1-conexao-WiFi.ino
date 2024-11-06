#include <WiFi.h>
// ----------------------------------------------------------------------------------------------
char ssid[] = "AP_";
char pass[] = "salatres1";
// ----------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  conexaoWiFi();  
}
// ----------------------------------------------------------------------------------------------
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Rede Conectada");
    Serial.println("");
  }else{
    Serial.println("Rede DESconectada");
    Serial.println("");
    
    conexaoWiFi();
  }
  delay(3000);
}
// ----------------------------------------------------------------------------------------------
void conexaoWiFi(){
  WiFi.begin(ssid, pass); //--> Connect to your WiFi router

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}
