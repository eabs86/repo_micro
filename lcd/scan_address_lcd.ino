#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nEscaneando o barramento I2C...");
  Serial.println("Seu endereço será exibido logo abaixo:");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Escaneando...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado no endereço 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Erro desconhecido no endereço 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  
  if (nDevices == 0) {
    Serial.println("Nenhum dispositivo I2C encontrado.\n");
  } else {
    Serial.println("Pronto!\n");
  }

  delay(5000); // Aguarda 5 segundos para escanear novamente
}