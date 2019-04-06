/*
 * 赤外線リモコンテスト
 * 2019/04/05
 */
#include <IRremote.h>
byte SEND_PIN = 9;
IRsend irsend(SEND_PIN);

#include <M5StickC.h>


bool led = true;

int IO_1 = 0;
int IO_2 = 26;
int IO_3 = 36;

void setup()
{
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  M5.Axp.ScreenBreath(9); //7 - 16

  M5.Lcd.setTextSize(2); //3
  M5.Lcd.setCursor(4, 40);
  M5.Lcd.print("M5 IR");
  //M5.Lcd.printf("%2d On", buttonPins[i]);

  //start serial connection
  Serial.begin(9600);

  /*
  //!Screen
  M5.Lcd.fillScreen(BLUE);
  delay(50);
  M5.Lcd.fillScreen(RED);
  delay(50);
  M5.Lcd.fillScreen(YELLOW);
  delay(50);
  M5.Lcd.fillScreen(ORANGE);
  delay(50);
  M5.Lcd.fillScreen(WHITE);
  delay(50);
  */

  //!IR LED
  //rem.begin(M5_IR,true);
  pinMode(M5_LED, OUTPUT);
  digitalWrite(M5_LED, LOW); //これで点灯
  digitalWrite(M5_LED, HIGH); //これで消灯
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
}

void loop() {

  //右ボタン 
  if(digitalRead(M5_BUTTON_RST) == LOW){
    digitalWrite(M5_LED, LOW);  //◆LED 消灯

    //irsend.sendNEC(0x02fd58a7, 32); //東芝REGZA VOLUME UP 58a7 
    irsend.sendPanasonic(0x4004, 0x0D00818C); //Panasonic DIGA Back 40040D00818C
    
    while(digitalRead(M5_BUTTON_RST) == LOW);

    digitalWrite(M5_LED, HIGH);  //◆LED 点灯
  }
  
  //HOMEボタン 
  if(digitalRead(M5_BUTTON_HOME) == LOW){
    digitalWrite(M5_LED, LOW);  //◆LED 消灯

    //irsend.sendNEC(0x02fd7887, 32); //東芝REGZA VOL DOWN 7887
    irsend.sendPanasonic(0x4004, 0x0D00FAF7); //Panasonic DIGA display 40040D00FAF7

    while(digitalRead(M5_BUTTON_HOME) == LOW);
    digitalWrite(M5_LED, HIGH);  //◆LED 点灯
  }
}
