
// set constants for buttons, potentiometer, and LED lights
const int button1 = 2;
const int button2 = 4;
const int poten = A0;
const int redLED = 6;
const int yellowLED = 5;

// setup of initial conditions
unsigned long startTime = 0; // set atrt time to an integer 0
bool potenTurn = false; // potentiometer has not been turned
bool buttonPress1 = false; //button 1 has not been pressed
bool buttonPress2 = false; //button 2 has not been pressed

// setup inputs and  outputs
void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  int buttonRead1 = digitalRead(button1);
  int buttonRead2 = digitalRead(button2);
  int potenRead = analogRead(poten);

  if (!buttonPress2 && buttonRead2 == HIGH) {
    buttonPress2 = true;
    startTime = currentTime;
  }

  if (!potenTurn && buttonPress2 && (currentTime - startTime < 10000)) {
    if (potenRead >= 1023) {
      potenTurn = true;
    }
  }

  if (buttonPress2 && potenTurn && buttonRead1 == HIGH && (currentTime - startTime < 10000)) {
    buttonPress1 = true;
  }

  if (buttonPress2 && potenTurn && buttonPress1) {
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  } else {
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  delay(100);
}
