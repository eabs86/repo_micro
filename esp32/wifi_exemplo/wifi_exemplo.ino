#include <WiFi.h>

const char* ssid     = "NOME_DA_SUA_REDE";     // Substitua pelo nome da sua rede Wi-Fi
const char* password = "SUA_SENHA"; // Substitua pela senha da sua rede Wi-Fi

void setup() {
  Serial.begin(115200);
  // Inicia a conexão Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado com sucesso ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aqui você pode adicionar o código que será executado continuamente enquanto o ESP32 estiver conectado
}