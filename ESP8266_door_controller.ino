//#include <Adafruit_GFX.h>
#include <Adafruit_ssd1306syp.h>
int keya = 1, keyb = 0, keyc = 1; //三个密码
int relayPin = 1;           //继电器接D10=gpio1,低电平触发
int middleKeyPin = 14;      //中键接D5=gpio14
int upKeyPin = 12;           //上键D6=gpio12
int screenIdle;             //屏幕超时.
Adafruit_ssd1306syp display(5, 4); //OLED屏幕:sda5,scl4


void setup() {
  //初始化gpio
  pinMode(middleKeyPin, INPUT_PULLUP);
  pinMode(upKeyPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  delay(100);
  
  display.initialize(); //初始化屏幕
}

void loop() {
  if (digitalRead(middleKeyPin) == LOW) { //亮屏
    screenIdle = 30;
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("ESP8266 door controller");
    display.update();
  };

  if (screenIdle > 0) {         //定时灭屏
    screenIdle = screenIdle - 1;
  } else {
    display.clear();
    display.update();
  };

  if (digitalRead(upKeyPin) == LOW) { //上键开门
    delay(200);
    digitalWrite(relayPin, LOW);
    screenIdle = 30;                  //亮屏
    display.setCursor(0, 0);
    display.print("Door opened by pressing key");
    display.update();
    delay(400);
    digitalWrite(relayPin, HIGH);
  };
  
  if(analogRead(A0)>100){       //按铃开门
       delay(200);
    digitalWrite(relayPin, LOW);
    screenIdle = 30;                  //亮屏
    display.setCursor(0, 0);
    display.print("Door opened by ring");
    display.update();
    delay(400);
    digitalWrite(relayPin, HIGH);
    };
 

  delay(100); //0.1秒延迟..
}
