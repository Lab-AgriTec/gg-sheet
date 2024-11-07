// Semáforo 

///Declarando as variáveis
int ledvermelho = 23;
int ledamarelo = 22;
int ledverde = 5;


///Entradas e saídas
void setup(){
  pinMode(ledvermelho, OUTPUT);   
  pinMode(ledamarelo, OUTPUT);    
  pinMode(ledverde, OUTPUT);    
}

void loop() {
  digitalWrite(ledverde, HIGH);     
  delay(5000);

  digitalWrite(ledverde, LOW);     
  digitalWrite(ledamarelo, HIGH);     
  delay(2000);

  digitalWrite(ledamarelo, LOW);
  digitalWrite(ledvermelho,HIGH);
  delay(5000);  
  digitalWrite(ledvermelho,LOW);   
}
