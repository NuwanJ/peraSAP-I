
//          E   G   W
//  Read    0   0   1
//  Write   0   1   0



void writeAddress(int data);
byte readOutput();
void writeOutput(byte data);

//const int outPins[] = {32, 30, 28, 26, 27, 29, 31, 33, 35};
//const int addPins[] = {34, 36, 38, 40, 42, 44, 46, 48, 52, 50, 45};

const int outPins[] = {22, 24, 26, 28, 30, 32, 34, 36};
const int addPins[] = {38, 40, 42, 44, 46, 48, 50, 52, 43, 45, 47};

//const int pinW = 49, pinG = 47, pinE = 43;
const int pinW = 8, pinG = 10, pinE = 9;

const byte digits[] = {
  0x3F, 0x06, 0x5B, 0x4F,
  0x66, 0x6D, 0x7D, 0x07,
  0x7F, 0x67, 0x77, 0x7C,
  0x39, 0x5E, 0x79, 0x71,
  0x00
};

#define HLT = 0b100000000000000
#define MI  = 0b010000000000000
#define RI  = 0b001000000000000
#define RO  = 0b000100000000000
#define IO  = 0b000010000000000
#define II  = 0b010001000000000
#define AI  = 0b010000100000000
#define AO  = 0b010000010000000
#define SM  = 0b010000001000000
#define SU  = 0b010000000100000
#define BI  = 0b010000000010000
#define OI  = 0b010000000001000
#define CE  = 0b010000000000100
#define CO  = 0b010000000000010
#define J  =  0b010000000000001

uint16_t data[]={
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //0000 -NOP
  MI|CO,    RO|II|CE,   MI|IO,    RO|AI,    0,          0,    0,    0                  //0001 -LOAD A
  MI|CO,    RO|II|CE,   MI|IO,    RO|BI,    AI|SM,      0,    0,    0                  //0010 -ADDITION
  MI|CO,    RO|II|CE,   MI|IO,    RO|BI,    AI|SM|SU,   0,    0,    0                  //0011 -SUBSTRACTION
  MI|CO,    RO|II|CE,   MI|IO,    RI|AO,    0,          0,    0,    0                  //0100 -STORE A
  MI|CO,    RO|II|CE,   IO|AI,    0,        0,          0,    0,    0                  //0101 -LOAD IMMEDIATE
  MI|CO,    RO|II|CE,   IO|J,     0,        0,          0,    0,    0                  //0110 -JUMP
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //0111
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1000
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1001
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1010
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1011
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1100
  MI|CO,    RO|II|CE,   0,        0,        0,          0,    0,    0                  //1101 
  MI|CO,    RO|II|CE,   AO|OI,    0,        0,          0,    0,    0                  //1110 -OUTPUT
  MI|CO,    RO|II|CE,   HLT,      0,        0,          0,    0,    0                  //1111 -HALT SYSTEM
}; 

void setup() {

  // Output Pins, def=read
  for (int i = 0; i < 8; i++) {
    pinMode(outPins[i], INPUT);
  }

  // Address Pins
  for (int i = 0; i < 12; i++) {
    pinMode(addPins[i], OUTPUT);
  }

  // Control Pins, default=Read
  pinMode(pinW, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinE, OUTPUT);
  setReadMode();

  Serial.begin(115200);


  delay(1000);

  Serial.println("\nWriting to EEPROM:");
  //debug();
  writeDigits();
  writeHex();
  //writeEEPROM();

  Serial.println("\nReading from EEPROM:");
  readEEPROM();

}

void loop() {

}

