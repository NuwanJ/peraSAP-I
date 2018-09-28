
void debug() {
  byte buff = 0;
  byte w = 0;

  for (int i = 0; i < 32; i++) {

    writeAddress(i);
    Serial.print("  Address > "); Serial.print(i, HEX); Serial.print("\t | "); Serial.print(2048 + i, BIN);

    w = digits[i % 10];
    setWriteMode();
    
    Serial.print("  Write > "); Serial.print(w, HEX); Serial.print("\t | "); Serial.print(256 + w, BIN);

    delay(10);

    setReadMode();
    buff = readOutput();
    Serial.print("\t  Read > "); Serial.print(buff, HEX); Serial.print("\t | "); Serial.print(256 + buff, BIN);
    Serial.println();

    delay(10);
  }
}

void debugWrite(int i, byte w) {
  byte buff;
  
  writeAddress(i);
  Serial.print("  Address > "); Serial.print(i, HEX); Serial.print("\t | "); /*Serial.print(2048 + i, BIN)*/;

  setWriteMode();
  writeOutput(w);
  Serial.print("  Write > "); Serial.print(w, HEX); Serial.print("\t | "); Serial.print(256 + w, BIN);

  delay(10);

  setReadMode();
  buff = readOutput();
  Serial.print("\t  Read > "); Serial.print(buff, HEX); Serial.print("\t | "); Serial.print(256 + buff, BIN);
  Serial.println();
}


void writeHex() {

  setWriteMode();
  byte d1, d2, d3, d4;

  for (int i = 0; i < 256; i++) {
    d4 = 16;
    d3 = 16;
    d2 = (i / 16);
    d1 = (i % 16);

    /*writeAddress(i);
      writeOutput(digits[d1]);

      writeAddress(256 + i);
      writeOutput(digits[d2]);

      writeAddress(512 + i);
      writeOutput(digits[d3]);

      writeAddress((256 * 3) + i);
      writeOutput(digits[d4]);*/

    debugWrite(1024 + i, digits[d1]);
    debugWrite(1024 + i + 256, digits[d2]);
    debugWrite(1024 + i + 512, digits[d3]);
    debugWrite(1024 + i + 256 * 3, digits[d4]);

    /*Serial.print("  Address > "); Serial.print(i, HEX); Serial.print("\t | ");
      Serial.print("00"); Serial.print("\t");
      Serial.print(d3); Serial.print("\t");
      Serial.print(d2); Serial.print("\t");
      Serial.print(d1); Serial.print("\t");

      Serial.print(" | 00\t");
      Serial.print(digits[d3], HEX); Serial.print("\t");
      Serial.print(digits[d2], HEX); Serial.print("\t");
      Serial.print(digits[d1], HEX); Serial.print("\t");
      //Serial.print(digits[d1], BIN);
      Serial.println();*/

  }
}



void writeDigits() {

  setWriteMode();
  byte d1, d2, d3, d4;

  for (int i = 0; i < 256; i++) {
    d4 = 16;
    d3 = i / 100;
    d2 = (i % 100) / 10;
    d1 = (i % 10);

    /*writeAddress(i);
      writeOutput(digits[d1]);

      writeAddress(256 + i);
      writeOutput(digits[d2]);

      writeAddress(512 + i);
      writeOutput(digits[d3]);

      writeAddress((256 * 3) + i);
      writeOutput(digits[d4]);*/

    debugWrite(i + 0, digits[d1]);
    debugWrite(i + 256, digits[d2]);
    debugWrite(i + 512, digits[d3]);
    debugWrite(i + 256 * 3, digits[d4]);

    /*Serial.print("  Address > "); Serial.print(i, HEX); Serial.print("\t | ");
      Serial.print("00"); Serial.print("\t");
      Serial.print(d3); Serial.print("\t");
      Serial.print(d2); Serial.print("\t");
      Serial.print(d1); Serial.print("\t");

      Serial.print(" | 00\t");
      Serial.print(digits[d3], HEX); Serial.print("\t");
      Serial.print(digits[d2], HEX); Serial.print("\t");
      Serial.print(digits[d1], HEX); Serial.print("\t");
      //Serial.print(digits[d1], BIN);
      Serial.println();*/

  }
}


void readEEPROM() {

  setReadMode();
  byte buff = 0;

  for (int i = 0; i < 32; i++) {

    //if (i % 1 == 0) {
    if (i % 4 == 0) {
      Serial.println();
      Serial.print(i);
    }
    Serial.print("\t");
    //}

    writeAddress(i);
    delay(10);
    buff = readOutput();

    Serial.print(buff, BIN); //Serial.print("\t");
    //Serial.print(512 + buff, BIN); Serial.print(" ");
    //Serial.println();

  }
}

void writeEEPROM() {

  setWriteMode();
  byte buff = 0;

  for (int i = 0; i < 2048; i++) {
    writeAddress(i);
    delay(10);
    buff = i % 256;
    writeOutput(buff);

    if (i % 8 == 0) {
      if (i % 32 == 0) {
        Serial.println();
        Serial.print(i);
      }
      Serial.print("\t");
    }

    if (buff > 99) {
      Serial.print(buff); Serial.print(" ");
    } else if (buff > 9) {
      Serial.print(" "); Serial.print(buff); Serial.print(" ");
    } else {
      Serial.print("  "); Serial.print(buff); Serial.print(" ");
    }
  }
}

