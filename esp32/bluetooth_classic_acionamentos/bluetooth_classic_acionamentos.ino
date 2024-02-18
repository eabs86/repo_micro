//---Mapeamento de Hardware---//
#define led 5
#define btn 4

//Biblioteca para habilitar a comunicação SERIAL
#include "BluetoothSerial.h"

//Verifica se o bluetooth esta habilitado corretamente
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//---Variáveis Globais---//
char dado;
bool flagBtn=0;
bool flagLed=0;

//Cria uma instância de BluetoothSerial chamado SerialBT
BluetoothSerial SerialBT;

//---Protótipo das Funções Auxiliares---//
void configuracao();
void leBotao();
void leSerial();
void leBluetooth();
void escreveBluetooth();

//---Função Principal---//
void setup() 
{
configuracao();  
}

//---Loop Infinito---//
void loop() 
{
leBotao();
leSerial();
leBluetooth();
delay(20);
}

//---Funções Auxiliares---//
void configuracao()
{
Serial.begin(115200);
SerialBT.begin("DSF_Eletronica_Maker");
Serial.println("O dispositivo foi iniciado, agora você pode emparelhá-lo com bluetooth!");
pinMode(led,OUTPUT);
pinMode(btn,INPUT);  
}
//==============================================//
void leSerial()
{
  if (Serial.available()) 
  {
  dado=(Serial.read());
  SerialBT.write(Serial.read());
  escreveBluetooth();
  }  
}

//==============================================//
void leBluetooth()
{
  if (SerialBT.available()) 
  {
  dado=(SerialBT.read());
  Serial.write(SerialBT.read());
  escreveBluetooth();
  } 
}

//==============================================//
void leBotao()
{
  if((digitalRead(btn)==LOW)&&(flagBtn==0))
  {
  flagBtn=1;
  flagLed=!flagLed;
    if(flagLed==0) dado='b';
    if(flagLed==1) dado='B';
    escreveBluetooth();
  }

    if((digitalRead(btn)==HIGH)&&(flagBtn==1))
    {
    flagBtn=0;
    }
}

//==============================================//
void escreveBluetooth()
{
  if(dado=='B') 
  {
  digitalWrite(led,HIGH);
  SerialBT.print("Led Acionado via botao");
  Serial.println("Led Acionado via botao");
  SerialBT.print("*LR255*");
  }
    if(dado=='b')
    {
    digitalWrite(led,LOW);
    SerialBT.print("Led Desacionado via botao");
    Serial.println("Led Desacionado via botao");
    SerialBT.print("*LR50*");
    } 
      if(dado=='l') 
      {
      digitalWrite(led,HIGH);
      SerialBT.print("Led Acionado via bluetooth");
      Serial.println("Led Acionado via bluetooth");
      SerialBT.print("*LR255*");
      }
      
        if(dado=='d')
        {
        digitalWrite(led,LOW);
        SerialBT.print("Led Desacionado via bluetooth");
        Serial.println("Led Desacionado via bluetooth");
        SerialBT.print("*LR50*");
        } 
          if(dado=='L') 
          {
          digitalWrite(led,HIGH);
          SerialBT.print("Led Acionado via SERIAL");
          Serial.println("Led Acionado via SERIAL");
          SerialBT.print("*LR255*");
          }
            if(dado=='D')
            {
            digitalWrite(led,LOW);
            SerialBT.print("Led Desacionado via SERIAL");
            Serial.println("Led Desacionado via SERIAL");
            SerialBT.print("*LR50*");
            }     
}
