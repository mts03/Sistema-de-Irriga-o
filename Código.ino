#define BLYNK_TEMPLATE_ID "TMPLGt6FCIWv"
#define BLYNK_DEVICE_NAME "Leds"
#define BLYNK_AUTH_TOKEN "rkGi95KSC6S3TQcsEBBzIe7zKwZcghj_"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

//Credenciais do WIFI da residência.
char ssid[] = "Alegro42 2G";
char pass[] = "02165299";

//Definindo os pinos
int rele = 14;
#define LDR_PIN 36
#define UMID_PIN 39


//Botão do Blynk realizando a ação no relé.
 BLYNK_WRITE(V2){
 int value = param.asInt();
 digitalWrite(rele, value); 
 }

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(rele, OUTPUT);
  pinMode(UMID_PIN, INPUT);


  Blynk.begin(auth, ssid, pass);  
}

//Variáveis
int analog_value = 0;
int porcentagemumid = 0;

void loop()
{ 
  delay(5000);
  //Valor de luminosidade
  int valorLDR = analogRead(LDR_PIN);
  Serial.println(valorLDR);
  Serial.print("Luminosidade:");

  //Valor de umidade
  analog_value = analogRead(UMID_PIN);
  //Calculando a porcentagem da umidade baseado no valor máximo do sensor (1023)
  porcentagemumid = (analog_value * 100) / 1023;

  //Se a porcentagem estiver abaixo de 50% avisar e regar a planta por 5 segundos. 
  //Se a porcentagem estiver acima de 50% avisar que está muito alta e fechar a válvula caso ela estiver aberta.
  if(porcentagemumid < 50){
    Serial.print("Umidade muito baixa!");
    digitalWrite(rele, LOW);
    delay(5000);
    digitalWrite(rele, HIGH);
  }
  else if(porcentagemumid > 70){
    Serial.print("Umidade muito alta!");
    digitalWrite(rele, HIGH);
  }

//Definindo um evento de notificação para o Blynk baseado na luminosidade
  Blynk.virtualWrite(V3, valorLDR);
  if(valorLDR < 2000 && eventTrigger == false){
    eventTrigger == true;
  }
  else if(valorLDR 4000 300){
    eventTrigger == false;
  }
  Serial.print(analog_value);
  Serial.println(" ");
  Blynk.run();
}
 
