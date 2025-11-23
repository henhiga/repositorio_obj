// Incluir bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

// Definições e constantes
char SSIDName[] = "Wokwi-GUEST";
char SSIDPass[] = "";

const int LDR_PIN = 34;  // Entrada analógica do LDR (A0 no ESP32)

char BrokerURL[] = "broker.hivemq.com";
char BrokerUserName[] = "";
char BrokerPassword[] = "";
char MQTTClientName[] = "mqtt-mack-pub-sub";
int BrokerPort = 1883;

char Topico_01[] = "MACK10402805/Som"; // Novo tópico para o LDR

// Variáveis globais e objetos
WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

// Funções definidas pelo usuário
void mqttReconnect() {
  while (!clienteMQTT.connected()) {
    Serial.println("Conectando-se ao broker MQTT...");
    Serial.println(MQTTClientName);

    if (clienteMQTT.connect(MQTTClientName, BrokerUserName, BrokerPassword)) {
      Serial.print(MQTTClientName);
      Serial.println(" conectado!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" tente novamente em 5 segundos.");
      delay(5000);
    }
  }
}

// Setup
void setup() {
  Serial.begin(9600);
  
  pinMode(LDR_PIN, INPUT);

  Serial.println("Conectando-se ao Wi-Fi...");
  WiFi.begin(SSIDName, SSIDPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  clienteMQTT.setServer(BrokerURL, BrokerPort);
}

// Loop
void loop() {
  if (!clienteMQTT.connected()) {
    mqttReconnect();
  }
  clienteMQTT.loop();


  int raw = analogRead(LDR_PIN);

  float intensidade = (raw / 4095.0) * 100.0;

  char msg[10];
  dtostrf(intensidade, 1, 2, msg);

  clienteMQTT.publish(Topico_01, msg);

  Serial.print("Valor LDR publicado (simulando som): ");
  Serial.println(msg);

  delay(1000);
}
