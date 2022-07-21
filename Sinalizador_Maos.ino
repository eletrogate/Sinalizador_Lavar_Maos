/*
   Sensor para auxiliar no uso do Alcool em Gel
   Autor: Gustavo - Eletrogate
*/
#define TimeSensores 500 // Tempo limite em ms para passar entre os dois sensores
#define TimeLavar 10000 // Tempo limite (em ms) entre as mãos e passar nos sensores

#define SensibilidadeLDR 120 // É o nivel onde o sensor entenderá que passou alguem

//----- Declaração dos pinos que usaremos -------//
#define Sensor1 A0
#define Sensor2 A1
#define FimDeCurso 7
#define Laser1 2
#define Laser2 3
#define PinBuzzer 8
#define PinLED 9
//-----------------------------------------------//

byte ReconhecerSentido();


void setup() {
  Serial.begin(9600);
  pinMode(Laser1, OUTPUT);
  pinMode(Laser2, OUTPUT);
  digitalWrite(Laser1, HIGH);
  digitalWrite(Laser2, HIGH);
  pinMode(FimDeCurso, INPUT_PULLUP);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(PinBuzzer, OUTPUT);
  pinMode(PinLED, OUTPUT);
}

void loop() {
  long time1 = -10000; // Faz o tempo ser -10s para simpliciar a lógica, onde, já inicia com o tempo que lavou a mão pela ultima vez excedido
  while (1) {
    if (!digitalRead(FimDeCurso)) { // Se caso a pessoa usou o alcool em gel, salva em qual tempo foi
      time1 = millis();
    }

    if (ReconhecerSentido() == 2) { // Verifica se a pessoa está no sentido 2, que é saindo de casa
      if ((millis() - time1) > TimeLavar) { // Ele confere se lavou a mão nos ultimos 10 segundos, se não, faz o alerta sonoro e visual.
        Serial.println("ESQUECEU DE LAVAR A MÃO!");
        digitalWrite(PinLED, HIGH);
        digitalWrite(PinBuzzer, HIGH);
        delay(1000);
        digitalWrite(PinLED, LOW);
        digitalWrite(PinBuzzer, LOW);
      }
      else {
        Serial.println("LAVOU AS MÃOS!"); // faz i time1 ser negativo para que garanta que na proxima pessoa que passar sem lavar as mãos, apite.
        time1 = -10000;
      }
    }
  }

}


byte ReconhecerSentido() { // Esse algoritmo reconhece qual sentido a pessoa passou. Se retornar 0 é porque não passou ninguem. O sentido 2 é porque a pessoa entrou em casa.
  byte sentido;
  unsigned long time1, tempototal = 0;
  sentido = 0;
  if (analogRead(Sensor1) > SensibilidadeLDR) {
    while (analogRead(Sensor1) > SensibilidadeLDR) {}
    tempototal = 0;
    time1 = millis();
    while ((analogRead(Sensor2) < SensibilidadeLDR) and (tempototal < TimeSensores)) {
      tempototal = millis() - time1;
    }

    if (tempototal < TimeSensores) {
      sentido = 2;
      return (sentido);
    }
  }

  if (analogRead(Sensor2) > SensibilidadeLDR) {
    while (analogRead(Sensor2) > SensibilidadeLDR) {}
    tempototal = 0;
    time1 = millis();
    while ((analogRead(Sensor1) < SensibilidadeLDR) and (tempototal < TimeSensores)) {
      tempototal = millis() - time1;
    }
    if (tempototal < TimeSensores) {
      sentido = 1;
      return (sentido);
    }
  }
  return (sentido);
}