/*
  28BYJ-48 + ULN2003 - modos via Serial
  Comandos (9600 bps):
    '1' -> full step (duas bobinas)
    '2' -> wave step (uma bobina)
    '3' -> half step (meia etapa)
  O motor gira continuamente para frente; o modo pode ser alterado a qualquer momento.
*/

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

const unsigned int STEP_DELAY_MS = 3; // tempo entre passos (ajuste velocidade)

enum StepMode : uint8_t { FULL = 1, WAVE = 2, HALF = 3 };
volatile StepMode modeAtual = HALF;    // modo inicial

// Tabelas de excitação (IN1..IN4)
const uint8_t SEQ_WAVE[4][4] = {
  {1,0,0,0},
  {0,1,0,0},
  {0,0,1,0},
  {0,0,0,1}
};

const uint8_t SEQ_FULL[4][4] = {
  {1,1,0,0},
  {0,1,1,0},
  {0,0,1,1},
  {1,0,0,1}
};

const uint8_t SEQ_HALF[8][4] = {
  {1,0,0,0},
  {1,1,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,1},
  {0,0,0,1},
  {1,0,0,1}
};

int idx = 0;  // índice da etapa atual (avança sempre)

void aplicaBobinas(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
}

void passo() {
  switch (modeAtual) {
    case WAVE: {
      aplicaBobinas(SEQ_WAVE[idx][0], SEQ_WAVE[idx][1], SEQ_WAVE[idx][2], SEQ_WAVE[idx][3]);
      idx = (idx + 1) % 4;
    } break;

    case FULL: {
      aplicaBobinas(SEQ_FULL[idx][0], SEQ_FULL[idx][1], SEQ_FULL[idx][2], SEQ_FULL[idx][3]);
      idx = (idx + 1) % 4;
    } break;

    case HALF: default: {
      aplicaBobinas(SEQ_HALF[idx][0], SEQ_HALF[idx][1], SEQ_HALF[idx][2], SEQ_HALF[idx][3]);
      idx = (idx + 1) % 8;
    } break;
  }
}

void trocaModo(StepMode novo) {
  modeAtual = novo;
  idx = 0; // reinicia a sequência para evitar tranco
  switch (novo) {
    case FULL: Serial.println(F("Modo: FULL STEP (1)")); break;
    case WAVE: Serial.println(F("Modo: WAVE STEP (2)")); break;
    case HALF: Serial.println(F("Modo: HALF STEP (3)")); break;
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // desliga tudo inicialmente
  aplicaBobinas(0,0,0,0);

  Serial.begin(9600);
  Serial.println(F("28BYJ-48 + ULN2003"));
  Serial.println(F("Digite 1=FULL, 2=WAVE, 3=HALF"));
  trocaModo(modeAtual); // anuncia modo inicial
}

void loop() {
  // Lê comandos simples ('1','2','3')
  if (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '1')      trocaModo(FULL);
    else if (c == '2') trocaModo(WAVE);
    else if (c == '3') trocaModo(HALF);
    else if (c == '\n' || c == '\r' || c == ' ') {
      // ignora
    } else {
      Serial.println(F("Comando invalido. Use 1, 2 ou 3."));
    }
  }

  // Dá um passo no modo atual (giro contínuo para frente)
  passo();
  delay(STEP_DELAY_MS);
}
