//--Constantes--
//definição dos pins
const int LED_PIN = 4;  // LED pin
const int PIR_PIN = 7; // HC-S501 pin
const int BUTTON_PIN = 2; //button pin

//definição dos estados
const int ESPERAR = 0;// espera durante 60 segundos
const int DETETAR = 1;// le dados do sensor
const int DETETOU = 2;// detetou movimento
const int PYTHON = 3;// envia dados para o python

//--Variaveis--
long time = 0;
int pirValue;
int x = 0;
int button = 1;
int state = ESPERAR;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), butt, RISING);

  Serial.begin(9600);
}

void loop() {

  switch (state) {
    case ESPERAR:

      time = millis();
      digitalWrite(LED_PIN, LOW);
      while (millis() - time < 60000);
      digitalWrite(LED_PIN, HIGH);

      state = DETETAR;
      break;
    case DETETAR:

      pirValue = digitalRead(PIR_PIN);

      if (pirValue == 1) {

        state = DETETOU;
      } else {

        state = DETETAR;
      }
      break;
    case DETETOU:


      time = millis();
      digitalWrite(LED_PIN, LOW);
      while (millis() - time < 30000);
      state = PYTHON;
      break;
    case PYTHON:

      Serial.println(button);
      state = ESPERAR;
      button = 1;
      break;
  }
}

void butt() {

  if (state == DETETOU) {

    time = 0;
    button = 0;
  }
}
