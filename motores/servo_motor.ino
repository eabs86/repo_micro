/*
  Servo via Serial - versão simples
  Envie pela Serial (9600 bps) um número de 0 a 180 e pressione Enter.
  Ex.: 90<Enter> -> posiciona o servo em 90 graus.
*/

#include <Servo.h>

const uint8_t SERVO_PIN = 9;
const long BAUD = 9600;

Servo servo;
int anguloAtual = 90;

// buffer mínimo para leitura da linha (ex.: "180\n")
char buf[8];
uint8_t idx = 0;

bool ehDigitoOuSinal(char c) {
  return (c >= '0' && c <= '9') || c == '+' || c == '-';
}

void setup() {
  Serial.begin(BAUD);
  servo.attach(SERVO_PIN);
  servo.write(anguloAtual);
  Serial.println(F("Digite um angulo (0-180) e pressione Enter."));
}

void loop() {
  while (Serial.available()) {
    char c = (char)Serial.read();

    if (c == '\r') continue;        // ignora CR (Windows)
    if (c == '\n') {                // fim da linha -> processa
      buf[idx] = '\0';
      if (idx == 0) {               // linha vazia
        idx = 0;
        return;
      }

      // valida: todos os chars precisam ser dígitos (ou sinal na primeira pos)
      bool ok = true;
      for (uint8_t i = 0; i < idx; i++) {
        if (!(ehDigitoOuSinal(buf[i]) && (i == 0 || (buf[i] >= '0' && buf[i] <= '9')))) {
          ok = false; break;
        }
      }

      if (!ok) {
        Serial.println(F("ERRO: Digite apenas numeros (0-180)."));
      } else {
        int val = atoi(buf);
        if (val < 0 || val > 180) {
          Serial.println(F("ERRO: Fora do intervalo (0-180)."));
        } else {
          servo.write(val);
          anguloAtual = val;
          Serial.print(F("OK: angulo="));
          Serial.println(anguloAtual);
        }
      }
      idx = 0;                      // pronto para próxima linha
    } else {
      // acumula até o limite do buffer
      if (idx < sizeof(buf) - 1) {
        buf[idx++] = c;
      } else {
        // excedeu o tamanho -> reseta e avisa
        idx = 0;
        Serial.println(F("ERRO: Entrada muito longa. Tente novamente."));
      }
    }
  }
}
