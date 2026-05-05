#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

const char* topic_temp = "fiap/guilherme/temperatura";
const char* topic_umidade = "fiap/guilherme/umidade";
const char* topic_dist = "fiap/guilherme/distancia";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define TRIG_PIN 5
#define ECHO_PIN 18

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a rede WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT...");
    String clientId = "ESP32Client-Guilherme-";
    clientId += String(random(0, 1000), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao Broker MQTT!");
    } else {
      Serial.print("Falhou, erro=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.print("Temp: "); Serial.print(t); 
  Serial.print(" °C | Umi: "); Serial.print(h); 
  Serial.print(" % | Dist: "); Serial.print(distance); Serial.println(" cm");

  client.publish(topic_temp, String(t).c_str());
  client.publish(topic_umidade, String(h).c_str());
  client.publish(topic_dist, String(distance).c_str());

  delay(2000);
}