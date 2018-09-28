


void writeAddress(int data) {
  // Write given address to ports

  if (data == 0) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(addPins[i], LOW);
    }

  } else {
    for (int i = 0; i < 7; i++) {
      digitalWrite(addPins[i], bitRead(data, 6 - i));
      //Serial.print(bitRead(data, i));
    }
  }
  delay(10);
}

uint16_t readOutput() {
  // Read current input

  uint16_t buff = 0;

  //Serial.print(" [");
  for (int i = 0; i < 16; i++) {
    bitWrite(buff, 15 - i, digitalRead(outPins[i]));
    //Serial.print(digitalRead(outPins[i]));
  }
  //Serial.print("] ");
  delay(10);
  return buff;
}

void writeOutput(uint16_t data) {
  //Write given output to DataOut pins

  for (int i = 0; i < 16; i++) {
    digitalWrite(outPins[i], bitRead(data, 15 - i));
  }

  digitalWrite(pinW, LOW);
  digitalWrite(pinW2, LOW);
  delayMicroseconds(500);
  digitalWrite(pinW, HIGH);
  digitalWrite(pinW2, HIGH);
  delay(50);

}

void setWriteMode() {

  for (int i = 0; i < 16; i++) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }

  digitalWrite(pinE, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinW, HIGH);
  digitalWrite(pinG2, HIGH);
  digitalWrite(pinW2, HIGH);
}

void setReadMode() {

  for (int i = 0; i < 16; i++) {
    digitalWrite(outPins[i], LOW);
    pinMode(outPins[i], INPUT);
  }

  digitalWrite(pinE, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinW, HIGH);
  digitalWrite(pinG2, LOW);
  digitalWrite(pinW2, HIGH);
}


