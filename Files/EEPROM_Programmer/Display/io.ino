


void writeAddress(int data) {
  // Write given address to ports

  //Serial.print(" [");

  if (data == 0) {
    for (int i = 0; i < 12; i++) {
      digitalWrite(addPins[i], LOW);
      //Serial.print(bitRead(data, i));
    }
  } else {
    for (int i = 0; i < 12; i++) {
      digitalWrite(addPins[i], bitRead(data, i));
      //Serial.print(bitRead(data, i));
    }
  }
  //Serial.print("] ");
  delay(10);
}

byte readOutput() {
  // Read current output

  byte buff = 0;

  Serial.print(" [");
  for (int i = 0; i < 8; i++) {
    bitWrite(buff, i, digitalRead(outPins[i]));
    Serial.print(digitalRead(outPins[i]));
  }
  Serial.print("] ");
  return buff;
}

void writeOutput(byte data) {
  //Write given output to DataOut pins

  //Serial.print(" [");
  for (int i = 0; i < 8; i++) {
    digitalWrite(outPins[i], 1 - bitRead(data, i));
    //Serial.print(bitRead(data, i));
  }
  //Serial.print("] ");

  digitalWrite(pinW, LOW);
  delayMicroseconds(5);
  digitalWrite(pinW, HIGH);
  delay(5);

}

void setWriteMode() {

  for (int i = 0; i < 8; i++) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }

  digitalWrite(pinE, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinW, HIGH);
}

void setReadMode() {

  for (int i = 0; i < 8; i++) {
    digitalWrite(outPins[i], LOW);
    pinMode(outPins[i], INPUT);
  }

  digitalWrite(pinE, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinW, HIGH);
}


