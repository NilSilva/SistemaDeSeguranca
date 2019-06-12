int ledPin = 4;  // LED pin
int pirPin = 7; // HC-S501 pin

int pirValue;

long time = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
 
  digitalWrite(ledPin, LOW);
  
  
  Serial.begin(9600);
  
}

void loop() {
  
  pirValue = digitalRead(pirPin);

  if(millis() >= 60000){
    
    digitalWrite(ledPin, pirValue);
	Serial.print(pirValue);
  }else if(millis() == time){

    time += 1000;
    Serial.println(millis());
  }
}