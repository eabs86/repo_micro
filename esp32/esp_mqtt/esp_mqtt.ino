#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>

// Configurações do WiFi e MQTT
const char* ssid = "SUA_REDE"; // Nome do ponto de acesso
const char* password = "SENHA_DA_REDE"; // Senha do ponto de acesso
const char* mqtt_server = "SEU_IP"; // Usando um broker público como exemplo
const int mqtt_port = 1885; // Porta padrão MQTT

// Tópico MQTT para publicar os dados
const char* mqtt_topic = "dados";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectToWiFi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi conectado.");
  Serial.print("IP atribuído: ");
  Serial.println(WiFi.localIP());
}

void reconnectToMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Conectando ao MQTT...");
    if (mqttClient.connect("ESP32_ClientID")) {
      Serial.println("Conectado ao MQTT");
    } else {
      Serial.print("Falha ao conectar, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  mqttClient.setServer(mqtt_server, mqtt_port);

  // Configurar o relógio para obter o horário
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); // GMT-3 sem horário de verão
  Serial.println("Aguardando sincronização com o servidor NTP...");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Hora sincronizada.");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (!mqttClient.connected()) {
    reconnectToMQTT();
  }
  mqttClient.loop();

  // Gerar dados aleatórios
  float tensao = random(400, 501) / 100.0; // 4.00 a 5.00 V
  float temperatura = random(2000, 2501) / 100.0; // 20.00 a 25.00 ºC
  int umidade = random(70, 101); // 70% a 100%
  int luminosidade = random(500, 1001); // 500 a 1000

  // Obter o datetime atual
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  // Criar o JSON
  StaticJsonDocument<256> doc;

  char datetime[30];
  strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);
  doc["datetime"] = datetime; // Primeiro campo do JSON
  doc["tensao"] = tensao;
  doc["temperatura"] = temperatura;
  doc["umidade"] = umidade;
  doc["luminosidade"] = luminosidade;

  // Serializar o JSON para string
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  // Publicar no broker MQTT
  mqttClient.publish(mqtt_topic, jsonBuffer);

  // Exibir no Serial Monitor
  Serial.println("Dados publicados:");
  Serial.println(jsonBuffer);

  // Aguardar 1 segundo antes do próximo envio
  delay(1000);
}
