int ledPin = 4;  // LED pin
int pirPin = 7; // HC-S501 pin
int buttonPin = 2; //button pin

long time = 0;

int pirValue;

int x = 0;
int button = 1;

const int esperar = 0;
const int detetar = 1;
const int detetou = 2;
const int python = 3;

int state = esperar;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), butt, RISING);

  Serial.begin(9600);
}

void loop() {

  switch (state) {
    case esperar:

      /*if(x == 0){

        Serial.println("A inicializar...");
        x = 1;
        }*/
      
      time = millis();
      digitalWrite(ledPin, LOW);
      while (millis() - time < 60000);
      digitalWrite(ledPin, HIGH);

      //Serial.println("Inicialização completada");

      state = detetar;
      break;
    case detetar:

      pirValue = digitalRead(pirPin);

      if (pirValue == 1) {

        //Serial.println("Movimento detetado");
        state = detetou;
      } else {

        state = detetar;
      }
      break;
    case detetou:


      time = millis();
      digitalWrite(ledPin, LOW);
      while (millis() - time < 30000);
      digitalWrite(ledPin, HIGH);
      //Serial.println("Enviar dados para o python");
      x = 0;
      state = python;
      break;
    case python:

      Serial.println(button);
      state = esperar;
      button = 1;
      break;
  }
}

void butt() {

  if (state == detetou) {

    time = 0;
    button = 0;
  }
}
