#include <Servo.h>

Servo myServo;  // Cria um objeto servo para controlar um servo motor

void setup() {
  myServo.attach(9);  // Anexa o servo no pino 9
  Serial.begin(9600);  // Inicia a comunicação serial
}

void loop() {
  if (Serial.available() > 0) {  // Checa se há dados disponíveis para ler na porta serial
    String input = Serial.readString();  // Lê a entrada como string
    input.trim();  // Remove espaços em branco e quebras de linha

    if (isNumber(input)) {  // Checa se a entrada é um número
      int angle = input.toInt();  // Converte a string para um inteiro
      if (angle >= 0 && angle <= 180) {  // Verifica se o ângulo está no intervalo permitido para servos
        myServo.write(angle);  // Move o servo para o ângulo especificado
        Serial.println("Movendo o servo para " + String(angle) + " graus.");
      } else {
        Serial.println("Erro: digite um valor entre 0 e 180.");
      }
    } else {
      Serial.println("Erro: entrada inválida. Digite um número.");
    }
  }
}

// Função para verificar se a string é um número
bool isNumber(String str) {
  for (char c : str) {
    if (!isDigit(c)) {
      return false;
    }
  }
  return true;
}
