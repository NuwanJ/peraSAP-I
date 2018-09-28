
//          E   G   W
//  Read    0   0   1
//  Write   0   1   0

#define HLT  0b1000000000000000
#define MI   0b0100000000000000
#define RI   0b0010000000000000
#define RO   0b0001000000000000
#define IO   0b0000100000000000
#define II   0b0000010000000000
#define AI   0b0000001000000000
#define AO   0b0000000100000000

#define SM   0b0000000010000000
#define SU   0b0000000001000000
#define BI   0b0000000000100000
#define OI   0b0000000000010000
#define CE   0b0000000000001000
#define CO   0b0000000000000100
#define J    0b0000000000000010
#define XX   0b0000000000000000

const int addPins[] = {14, 15, 16, 17, 20, 19, 18}; // A0-A7

const int outPins[] = {
  22, 24, 26, 28, 30, 32, 34, 36, // IC 1
  38, 40, 42, 44, 46, 48, 50, 52  // IC 2
};

const int pinW = 6, pinW2 = 4, pinG = 5, pinG2 = 3, pinE = 9;

//   -------> Machine Cycle
// |
// | Instruction Cycle
// v

uint16_t data[] = {
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //0000 -NOP
  MI | CO,    RO | II | CE,   MI | IO,    RO | AI,    XX,           XX,   XX,   XX,    //0001 -LOAD A
  MI | CO,    RO | II | CE,   MI | IO,    RO | BI,    AI | SM,      XX,   XX,   XX,    //0010 -ADDITION
  MI | CO,    RO | II | CE,   MI | IO,    RO | BI,    AI | SM | SU, XX,   XX,   XX,    //0011 -SUBSTRACTION
  MI | CO,    RO | II | CE,   MI | IO,    RI | AO,    XX,           XX,   XX,   XX,    //0100 -STORE A
  MI | CO,    RO | II | CE,   IO | AI,    XX,         XX,           XX,   XX,   XX,    //0101 -LOAD IMMEDIATE
  MI | CO,    RO | II | CE,   IO | J,     XX,         XX,           XX,   XX,   XX,    //0110 -JUMP
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //0111
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1000
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1001
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1010
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1011
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1100
  MI | CO,    RO | II | CE,   XX,         XX,         XX,           XX,   XX,   XX,    //1101
  MI | CO,    RO | II | CE,   AO | OI,    XX,         XX,           XX,   XX,   XX,    //1110 -OUTPUT
  MI | CO,    RO | II | CE,   HLT,        XX,         XX,           XX,   XX,   XX     //1111 -HALT SYSTEM
};

void setup() {

  // Output Pins
  for (int i = 0; i < 16; i++) {
    pinMode(outPins[i], OUTPUT);
  }

  // Address Pins
  for (int i = 0; i < 7; i++) {
    pinMode(addPins[i], OUTPUT);
  }

  // Control Pins, default=Read
  pinMode(pinW, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinW2, OUTPUT);
  pinMode(pinG2, OUTPUT);
  pinMode(pinE, OUTPUT);

  digitalWrite(pinE, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinW, HIGH);
  digitalWrite(pinG2, LOW);
  digitalWrite(pinW2, HIGH);

  setReadMode();

  Serial.begin(115200);
  delay(1000);

  Serial.println(">> EEPROM: R/W Programmer");
  Serial.println("  begin...");

}

void loop() {

}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    if (inChar == '+') {
      writeData();
    } else if (inChar == '-') {
      readData();
    } else if (inChar == '*') {
      debug();
    } else if (inChar >= 'A' && inChar <= 'z') {

      char address[8] = {};
      char binary[17] = {};

      uint16_t dataRead = 0;
      uint16_t dataWrite = 0;
      int temp = 0;

      address[7] = '\0';
      binary[16] = '\0';

      //-----------------------------------------------------------------------------
      for (int ii = 0; ii < 5; ii++) {
        // Write the current address

        //-----------------------------------------------------------------------------
        if (inChar >= 'a') {

          temp = (inChar - 'a') * 8 + ii;
          writeAddress(temp);

          // Read mode
          setReadMode();
          if (ii == 0)Serial.println(">> Read");
          dataRead = readOutput();

        } else {

          temp = ((inChar - 'A') * 8) + ii;
          writeAddress(temp);

          // Write mode
          if (ii == 0)Serial.println(">> Write");
          setWriteMode();
          delay(10);

          dataWrite = data[temp]; //ii + (8 * ii) + (128 * ii); //
          dataRead =  dataWrite;
          writeOutput(dataWrite);

        }
        //-----------------------------------------------------------------------------
        Serial.print("addr  >\t");
        Serial.print(temp);
        Serial.print("\t");

        for (int k = 0; k < 7; k++) {
          address[k] = (bitRead(temp, 6 - k) == 1) ? '1' : '0' ;
          if (k == 4)Serial.print(' ');
          Serial.print(address[k]);
        }
        Serial.print(":\t");

        //-----------------------------------------------------------------------------
        for (int k = 0; k < 16; k++) {

          binary[k] = (bitRead(dataRead, 15 - k) == 1) ? '1' : '0' ;
          if (k == 8)Serial.print(' ');
          Serial.print(binary[k]);
        }
        Serial.print("\n");
      }
    }
    Serial.print("\n");

  }
}

