/*
 * 赤外線リモコンテスト 2019/04/05
 * 
 * 必要なライブラリ
 * https://github.com/SensorsIot/Arduino-IRremote
 * 
 * M5StickC lib: 0.0.5
 * 
 */

#include <IRremote.h>
byte SEND_PIN = 9; // IR:9
IRsend irsend(SEND_PIN);

#include <M5StickC.h>

void setup()
{
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  M5.Axp.ScreenBreath(9); //7 - 16 暗めにしたい

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(4, 40);
  M5.Lcd.print("M5 IR");

  Serial.begin(115200);

  // LED
  pinMode(M5_LED, OUTPUT);
  digitalWrite(M5_LED, LOW); //これで点灯
  digitalWrite(M5_LED, HIGH); //これで消灯
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
}

void loop() {

  //Right / RST button VOL UP 音量アップ
  if(digitalRead(M5_BUTTON_RST) == LOW){
    Serial.println("RST");
    digitalWrite(M5_LED, LOW);  //LED OFF

    //TV
    irsend.sendNEC(0x02fd58a7, 32); //東芝REGZA VOLUME UP 58a7 
    delay(100);
    irsend.sendNEC(0xA8576897, 32); //FUJITSU A8576897 
    delay(100);
    irsend.sendNEC(0x0AF548B7, 32); //HITACHI 0AF548B7
    delay(100);
    irsend.sendNEC(0x18E740BF, 32); //NEC     18E740BF
    delay(100);
    irsend.sendPanasonic(0x4004, 0x01000405); //Panasonic 400401000405
    delay(100);
    irsend.sendPanasonic(0x555A, 0xF148288F); //SHARP     555AF148288F
    delay(100);
    irsend.sendSony(0x555AF1484900B6FF, 64); //SONY     555AF1484900B6FF
    delay(100);
    //irsend.sendPanasonic(0x4004, 0x0D00818C); //Panasonic DIGA Back 40040D00818C
    
    while(digitalRead(M5_BUTTON_RST) == LOW);

    digitalWrite(M5_LED, HIGH);  //LED ON
  }
  
  //HOME button  VOL DOWN 音量ダウン
  if(digitalRead(M5_BUTTON_HOME) == LOW){
    Serial.println("HOME");
    digitalWrite(M5_LED, LOW);  //LED ON

    //TV
    irsend.sendNEC(0x02fd7887, 32); //東芝REGZA VOL DOWN 7887
    delay(100);
    irsend.sendNEC(0xA857E817, 32); //FUJITSU A857E817
    delay(100);
    irsend.sendNEC(0x0AF5A857, 32); //HITACHI 0AF5A857
    delay(100);
    irsend.sendNEC(0x18E740BF, 32); //NEC     18E7C03F
    delay(100);
    irsend.sendPanasonic(0x4004, 0x01008485); //Panasonic 400401008485
    delay(100);
    irsend.sendPanasonic(0x555A, 0xF148A887); //SHARP     555AF148A887
    delay(100);
    irsend.sendSony(0x555AF148C90036FF, 64); //SONY     555AF148C90036FF
    delay(100);
    //irsend.sendPanasonic(0x4004, 0x0D00FAF7); //Panasonic DIGA display 40040D00FAF7

    while(digitalRead(M5_BUTTON_HOME) == LOW);
    digitalWrite(M5_LED, HIGH);  //LED OFF
  }
}
