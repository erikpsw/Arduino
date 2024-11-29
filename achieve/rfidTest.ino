/*******************************************
 * 湖南创乐博智能科技有限公司
 * 名称: RFID 门禁系统
 * 功能: 首先通过 getid.ino 文件获取 RFID 钥匙的 ID，然后将 ID 分成四部分并填入 loop() 函数中
 * 在 RFID 模块上刷 RFID 钥匙环。
 * 如果密码正确，继电器的常开触点将闭合，LCD 将显示字符串 “ID:5AE4C955” "hello Arduino",
 * 然后两秒后显示 "Welcome!";
 * 如果密码不正确，继电器的常开触点将断开，LCD 将显示字符串 "Hello unknown guy" ,
 * 然后两秒后显示 "Welcome!"
 * 连接:
 * RFID	                  Arduino Uno
 * VCC	                      3.3V
 * RST	                      2
 * GND	                      GND
 * MISO	                      3
 * MOSI	                      4
 * SCK	                      5
 * NSS	                      6
 * IRQ	                      7
 ****************************************/

#include"rfid.h"
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
RFID rfid; // 创建一个 RFID 类型的变量
#define relayPin 8  // 继电器模块连接到引脚 8

uchar serNum[5]; // 用于存储 ID 的数组

void setup()
{
  lcd.init(); // 初始化 LCD
  lcd.backlight(); // 打开背光
  Serial.begin(9600);
  rfid.begin(7, 5, 4, 3, 6, 2); // rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(100); 
  rfid.init(); // 初始化 RFID
  pinMode(relayPin, OUTPUT);  // 将 relayPin 设置为输出
  digitalWrite(relayPin,HIGH); // 设置为高电平
  //Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("    Welcome!    "); // 显示 "    Welcome!    "
  delay(2000); // 延迟 2 秒

}
void loop()
{
  uchar status;
  uchar str[MAX_LEN];
   // 搜索卡片，返回卡片类型
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return;
  }
  // 显示卡片类型
  rfid.showCardType(str);
  // 防止冲突，返回卡片的 4 字节序列号
  status = rfid.anticoll(str);

  if (status == MI_OK)
  {
    //Serial.print("The card's number is: ");
    lcd.setCursor(0,0);
    lcd.print(" ID: ");
    memcpy(serNum, str, 5);
    rfid.showCardID(serNum); // 显示卡片 ID
    // Serial.println();

    // 检查与卡片 ID 8F3D0329 关联的人
    uchar* id = serNum;
    if( id[0]==0x0A && id[1]==0x40 && id[2]==0x7E && id[3]==0x7F ) 
    {
      digitalWrite(relayPin,LOW);
      // Serial.println("Hello Dannel!");
      lcd.setCursor(0,1);
      lcd.print(" Hello Dannel! ");
      delay(2000);
      lcd.clear();
      digitalWrite(relayPin,HIGH);
    } 
    // 如果卡片 ID 是 AB8058A3，则继电器连接
    else if(id[0]==0xAB && id[1]==0x80 && id[2]==0x58 && id[3]==0xA3) 
    {
      digitalWrite(relayPin,LOW);
      //Serial.println("Hello Arduino");
      lcd.setCursor(0,1);
      lcd.print("Hello Arduino");
      delay(2000);
      lcd.clear();
      digitalWrite(relayPin,HIGH);
    } 
    else
    {
      //Serial.println("Hello unkown guy!");
      lcd.setCursor(0,1);
      lcd.print("Hello unkown guy");
      delay(2000);
      lcd.clear();
    }
  }
  lcd.setCursor(0,0);
  lcd.print("    Welcome!    ");
  delay(2000);
  rfid.halt(); // 命令卡片进入休眠模式
}