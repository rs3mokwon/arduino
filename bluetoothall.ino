#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTTYPE DHT22

int tilt = 13; // 기울기센서
int PWM = 10; //fan 모터
int IN1 = 11; //fan 모터
int IN2 = 12;//fan 모터
int motor1 = 3; //실린더핀
int motor2 = 4; //실린더핀
int DHTPIN = 2; //온습도핀
int ledpin = 9; //LED핀
int gaspin = A0; //가스핀
DHT dht(DHTPIN, DHT22);

int hum;
int tem;

int p;
int blueTx=8;   //Tx (보내는핀 설정)at
int blueRx=7;   //Rx (받는핀 설정)
SoftwareSerial BTSerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

String myString = ""; //받는 문자열
int a=0;
int b=0;
void setup() {
  pinMode(tilt, INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(gaspin, INPUT);
  pinMode(ledpin, OUTPUT);
  dht.begin();
  Serial.begin(9600);  //시리얼모니터
  BTSerial.begin(9600); //블루투스 시리얼
}

void loop() {
   int rldnfrl = digitalRead(tilt);
   while(BTSerial.available()) 
  {       
    char myChar = (char)BTSerial.read();
    myString += myChar;
    delay(5); 
  }
  if(!myString.equals("")){
    Serial.println(myString);
    if(myString == "3"){
      a=1;
      //digitalWrite(IN2,LOW);
      //analogWrite(PWM, 255);
    }
    else if(myString == "4"){
      a=0;
      digitalWrite(IN1,LOW);
      analogWrite(PWM, 0);
    }
    else if(myString == "1"){
    
      digitalWrite(ledpin, HIGH);
    }
    else if(myString == "0"){
      digitalWrite(ledpin, LOW);
    }

    else if(myString == "5"){
      //실린더 올라감
      if(rldnfrl == HIGH){
        b=0;
       digitalWrite(motor1, LOW); 
       digitalWrite(motor2, HIGH);
        }
      }
    
    else if(myString == "6"){
      //실린더 내려감
      b=0;
      if(rldnfrl == HIGH){
       digitalWrite(motor1, HIGH);
       digitalWrite(motor2, LOW);
       }
    }
    
    myString = "";
  }
  if(rldnfrl == LOW || b){
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, HIGH);
  }
    if(analogRead(gaspin) > 400 || a){
       digitalWrite(IN2,LOW);
       analogWrite(PWM, 200);
       delay(100);
    }
    else if(analogRead(gaspin) < 400){
      digitalWrite(IN2,LOW);
       analogWrite(PWM, 0);
       delay(100);
    }

    hum = dht.readHumidity();
    tem = dht.readTemperature();
    
    BTSerial.print(analogRead(gaspin));
    BTSerial.print(" ");

    BTSerial.print(hum);
    BTSerial.print(" ");

    BTSerial.print(tem);
    BTSerial.print(" ");

    BTSerial.println(rldnfrl);

    delay(100);
}
