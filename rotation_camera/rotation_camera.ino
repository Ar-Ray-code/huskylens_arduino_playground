#include <Wire.h>
#include <PCA9685.h>


#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

PCA9685 pwm = PCA9685(0x40);
HUSKYLENS huskylens;

SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11

#define SERVOMIN 150
#define SERVOMAX 600


int x = 90;
int old_x = 90;
float p = 0.05;
float d = 0.7;

void printResult(HUSKYLENSResult result);
void servo_write(int ch, int ang);

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);

    pwm.begin();
    pwm.setPWMFreq(60);
    
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request()) ;//Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) ;//Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) ;//Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        //Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            //printResult(result);
            x -= int(float(result.xCenter - 160)*p);
            x += int((x - old_x)*d);
            
            if(x <= 0)        x = 0;
            else if(x >= 180) x = 180;
            servo_write(0,x);
            Serial.print("x:");
            Serial.println(x);
            delay(50);
            old_x = x;
        }    
    }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）に変換
  pwm.setPWM(ch, 0, ang);
  //delay(1);
}
