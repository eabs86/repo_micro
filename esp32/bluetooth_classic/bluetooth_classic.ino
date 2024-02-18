#include "BluetoothSerial.h"

// Descomente a linha abaixo para usar um PIN durante o pareamento
//#define USE_PIN
const char *pin = "1234"; // Altere para um PIN mais seguro.

String nome_dispositivo = "ESP32-BT-Escravo";

// Verifica se o Bluetooth está habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth não está habilitado! Por favor, execute `make menuconfig` para habilitá-lo.
#endif

// Verifica se o Bluetooth Serial está disponível e habilitado
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Bluetooth Serial não disponível ou não habilitado. Disponível apenas para o chip ESP32.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(nome_dispositivo); // Nome do dispositivo Bluetooth
  Serial.printf("Dispositivo com nome \"%s\" iniciado.\nAgora você pode pareá-lo com o Bluetooth!\n", nome_dispositivo.c_str());

  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Usando PIN");
  #endif
}

void loop() {
  // Lê dados do Serial e envia para o Bluetooth
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  // Lê dados do Bluetooth e envia para o Serial
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20); // Pequena pausa para estabilidade
}
