// plantduino.ino
#include <Wire.h>

#define SLAVE_ADDRESS 0x08

const int motor1Pin =  2;
const int motor2Pin =  3;
const int lightsPin =  4;
const int doserPin =  5;
const int PowerVPin =  A1;
const int PowerIPin =  A0;

// 10 byte data buffer
int receiveBuffer[9];
uint8_t keepCounted = 0;
float Output = 0;

// Read data in to buffer, offset in first element.
void receiveData(int byteCount){
    int counter = 0;
    while(Wire.available()) {
        receiveBuffer[counter] = Wire.read();
        Serial.print("Got data: ");
        Serial.println(receiveBuffer[counter]);
        if (receiveBuffer[0] == 1) {  //Motor 1 on
            digitalWrite(motor1Pin, LOW);
            Serial.print("Motor 1 on");
        }
        else if (receiveBuffer[0] == 2) {  //Motor 1 off
            digitalWrite(motor1Pin, HIGH);
            Serial.println("Motor 1 off");
        } 
        else if (receiveBuffer[0] == 3) {  //Motor 2 on
            digitalWrite(motor2Pin, LOW);
            Serial.println("Motor 2 on");
        } 
        else if (receiveBuffer[0] == 4) {  //Motor 2 off
            digitalWrite(motor2Pin, HIGH);
            Serial.println("Motor 2 off");
        } 
        else if (receiveBuffer[0] == 5) {  //Lights on
            digitalWrite(lightsPin, LOW);
            Serial.print("Lights on");
        } 
        else if (receiveBuffer[0] == 6) {  //Lights off
            digitalWrite(lightsPin, HIGH);
            Serial.print("Lights off");
        } 
        else if (receiveBuffer[0] == 7) {  //Doser on
            digitalWrite(doserPin, LOW);
            Serial.println("Doser on");
        } 
        else if (receiveBuffer[0] == 8) {  //Doser off
            digitalWrite(doserPin, HIGH);
            Serial.println("Doser off");
        }
        else if (receiveBuffer[0] == 9) {  //Voltage read
            int VValue = 0;
            VValue = analogRead(PowerVPin);
            float voltage= VValue * (5.0 / 1023.0);
            Serial.print("Voltage: ");
            Serial.println(voltage);
            Output = voltage;
        }
        else if (receiveBuffer[0] == 0) {  //Current read
            int IValue = 0;
            IValue = analogRead(PowerIPin);
            float current= IValue * (5.0 / 1023.0);
            Serial.print("Current: ");
            Serial.println(current);
            Output = current;
        } else{
            Serial.println("No function for this address");
        }
        counter ++;
    }
}


// Use the offset value to select a function
void sendData(){
    Serial.print("Sending output: ");
    Serial.println(Output);
    char result[8]; // Buffer big enough for 7-character float
    dtostrf(Output, 6, 2, result); // Leave room for too large numbers!
    Serial.print("After transform: ");
    Serial.println(result);
    /* writeData(result); */
    int dataSize = sizeof(result);
    Wire.write(result, dataSize);
}


// Write data
void writeData(char newData) {
    char data[] = {receiveBuffer[0], newData};
    int dataSize = sizeof(data);
    Serial.print("Write data: ");
    Serial.println(data);
    Wire.write(data, dataSize);
}


void setup(){
  // set the digital pins as outputs and start off relays off:
  pinMode(motor1Pin, OUTPUT);
  digitalWrite(motor1Pin, HIGH);
  pinMode(motor2Pin, OUTPUT);
  digitalWrite(motor2Pin, HIGH);
  pinMode(lightsPin, OUTPUT);
  digitalWrite(lightsPin, HIGH);
  pinMode(doserPin, OUTPUT);
  digitalWrite(doserPin, HIGH);
  
  Serial.begin(9600); // start serial for output
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("I2C Ready!");
}


void loop(){
  delay(100);
}
