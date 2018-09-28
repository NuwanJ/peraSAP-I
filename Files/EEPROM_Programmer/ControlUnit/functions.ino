
void debug() {
  
  Serial.println(">> Debug\n");

  char address[8] = {};
  char binary[17] = {};

  address[7] = '\0';
  binary[16] = '\0';
  setWriteMode();

  for (int i = 0; i < 16; i++) {
    // Write each Instruction

    for (int j = 0; j < 8; j++) {
      // Write each Machine Code

      Serial.print("write >\t");
      setWriteMode();
      writeAddress(i * 8 + j);
      delay(10);
      writeOutput(data[i * 8 + j]);
      delay(10);

      //--- Debug Section ----------------------------------------------
      //if (data[i * 8 + j] == 0 )continue;

      for (int k = 0; k < 7; k++) {
        address[k] = (bitRead(i * 8 + j, 6 - k) == 1) ? '1' : '0' ;
        if (k == 4)Serial.print(' ');
        Serial.print(address[k]);
      }
      Serial.print(":\t");

      for (int k = 0; k < 16; k++) {
        binary[k] = (bitRead(i * 8 + j, 15 - k) == 1) ? '1' : '0' ;

        if (k == 8)Serial.print(' ');
        Serial.print(binary[k]);
      }
      Serial.print("\n");

      //--- Read Section ----------------------------------------------

      setReadMode();
      uint16_t dataRead = readOutput();

      Serial.print("read  >\t");
      for (int k = 0; k < 7; k++) {
        address[k] = (bitRead(i * 8 + j, 6 - k) == 1) ? '1' : '0' ;
        if (k == 4)Serial.print(' ');
        Serial.print(address[k]);
      }
      Serial.print(":\t");

      for (int k = 0; k < 16; k++) {
        binary[k] = (bitRead(dataRead, 15 - k) == 1) ? '1' : '0' ;

        if (k == 8)Serial.print(' ');
        Serial.print(binary[k]);
      }
      Serial.print("\n");
    }
    Serial.println();
    Serial.println();
  }

  setReadMode();
}


void writeData() {

  Serial.println(">> Write data to EEPROM\n");

  char address[8] = {};
  char binary[17] = {};

  address[7] = '\0';
  binary[16] = '\0';
  setWriteMode();

  for (int i = 0; i < 16; i++) {
    // Write each Instruction

    for (int j = 0; j < 8; j++) {
      // Write each Machine Code

      Serial.print("write >\t");
      setWriteMode();
      writeAddress(i * 8 + j);
      delay(10);
      writeOutput(data[i * 8 + j]);
      delay(10);

      //--- Debug Section ----------------------------------------------
      //if (data[i * 8 + j] == 0 )continue;

      for (int k = 0; k < 7; k++) {
        address[k] = (bitRead(i * 8 + j, 6 - k) == 1) ? '1' : '0' ;
        if (k == 4)Serial.print(' ');
        Serial.print(address[k]);
      }
      Serial.print(":\t");

      for (int k = 0; k < 16; k++) {
        binary[k] = (bitRead(data[i * 8 + j], 15 - k) == 1) ? '1' : '0' ;

        if (k == 8)Serial.print(' ');
        Serial.print(binary[k]);
      }
      Serial.print("\n");

      //--- Read Section ----------------------------------------------

      setReadMode();
      uint16_t dataRead = readOutput();

      Serial.print("read  >\t");
      for (int k = 0; k < 7; k++) {
        address[k] = (bitRead(i * 8 + j, 6 - k) == 1) ? '1' : '0' ;
        if (k == 4)Serial.print(' ');
        Serial.print(address[k]);
      }
      Serial.print(":\t");

      for (int k = 0; k < 16; k++) {
        binary[k] = (bitRead(dataRead, 15 - k) == 1) ? '1' : '0' ;

        if (k == 8)Serial.print(' ');
        Serial.print(binary[k]);
      }
      Serial.print("\n");
    }
    Serial.println();
    Serial.println();
  }

  setReadMode();
}


void readData() {

  Serial.println(">> Read data from EEPROM\n");
  char address[8] = {};
  char binary[17] = {};

  address[7] = '\0';
  binary[16] = '\0';
  setReadMode();

  for (int i = 0; i < 16; i++) {
    // Write each Instruction

    for (int j = 0; j < 8; j++) {
      // Write each Machine Code

      writeAddress(i * 8 + j);
      delay(10);


      uint16_t dataRead = readOutput();

      //if (dataRead == 0 )continue;

      for (int k = 0; k < 7; k++) {
        address[k] = (bitRead(i * 8 + j, 6 - k) == 1) ? '1' : '0' ;
        if (k == 4)Serial.print(' ');
        Serial.print(address[k]);
      }
      Serial.print(":\t");

      for (int k = 0; k < 16; k++) {
        binary[k] = (bitRead(dataRead, 15 - k) == 1) ? '1' : '0' ;

        if (k == 8)Serial.print(' ');
        Serial.print(binary[k]);
      }
      Serial.print("\n");
    }
    Serial.println();
  }
}

