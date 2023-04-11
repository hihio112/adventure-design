#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(12,4,NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(2,3);
int redColor = 0;
int greenColor = 0;
int blueColor =0;
int echoPin = 6;
int trigPin = 5;
/* <나만의 소맥머신 레시피>
 *  1번 모터 (소주)
 *  2번 모터 (맥주)
 *  3번 모터 (보드카)
 *  4번 모터 (오렌지 쥬스)
 *  5번 모터 (핫식스)
 *  
 *  1. 소주 한잔
 *  2. 맥주 반잔
 *  3. 소맥 강도 상 (4:6)
 *  4. 소맥 강도 중 (3:7)
 *  5. 소맥 강도 하 (2:8)
 *  6. 보드카밤 = 보드카 1샷 + 핫식스 반잔
 *  7. 스크류 드라이버 = 보드카 1샷 + 오렌지 주스(나머지)
 */
int recipes[7][5] = { {20, 0, 0, 0, 0},
                     {0, 50, 0, 0, 0},
                     {40, 60, 0, 0, 0},
                     {30, 70, 0, 0, 0},
                     {20, 80, 0, 12, 0},
                     {0, 0, 15, 0, 50},
                     {0, 0, 15, 50, 0} };

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pixels.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7,OUTPUT);    //모터 7~11
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);


  pixels.setBrightness(120);  //밝기 조절 0~255

}

void loop() 
{
  while (true){
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    unsigned long duration = pulseIn(echoPin, HIGH); 
    // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
    float distance = ((float)(340 * duration) / 10000) / 2;  
  
  //Serial.print(distance);
  //Serial.println("cm");
  //delay(500);
  
  int Serial_num=0;
   if(mySerial.available()){
      Serial_num = mySerial.read();
      Serial.println(Serial_num);
    
     //turn_led();
      if (distance >= 7) {    //초음파 센서 감지
        break;
      }
     switch(Serial_num){
      case 49:
          setRed();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
      case 50:
          setBlue();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
      case 51:
          setGreen();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
      case 52:
          setYellow();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
      case 53:
          setLime();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
       case 54:
          setColor();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
      case 55:
          setSky();
          turn_led();
          pour(Serial_num);
          pixels.clear();
          pixels.show();
          break;
     }
  }
 }
}
void setRed(){
  redColor = 255;
  greenColor = 0;
  blueColor = 0;
}
void setBlue(){
  redColor = 0;
  greenColor = 0;
  blueColor = 255;
}
void setGreen(){
  redColor = 0;
  greenColor = 255;
  blueColor = 0;
}
void setYellow(){
  redColor = 255;
  greenColor = 212;
  blueColor = 0;
}
void setLime(){
  redColor = 191;
  greenColor = 255;
  blueColor = 0;
}
void setColor(){
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}
void setSky(){
  redColor = 80;
  greenColor = 188;
  blueColor = 223;
}
void turn_led(){
  for (int i=0;i<12;i++){
    pixels.setPixelColor(i,pixels.Color(redColor,greenColor,blueColor));
    pixels.show();
  }
}
void pour(int message){   // 술 따르는 함수
for (int i = 0; i < 5; i++) {
        digitalWrite(i + 7, HIGH);
        delay(100 * recipes[message - 49][i]);
        digitalWrite(i + 7, LOW);
        delay(1000);
 }
}