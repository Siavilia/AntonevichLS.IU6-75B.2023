#include<dht.h>      // подключаем библиотеку для работы с датчиком 
#include<LiquidCrystal.h> // подключаем библиотеку для работы с ЖК дисплеем
 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define dht_dpin 12 
#define pin_start 8
dht DHT;
#define pwm 9
byte degree[8] = // символ градуса для отображения на ЖК дисплее
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
void setup()
{
 lcd.begin(16, 2);
 lcd.createChar(1, degree);
 lcd.clear();
 lcd.print("   Fan Speed  ");
 lcd.setCursor(0,1);
 lcd.print("  Controlling ");
 delay(2000);
 analogWrite(pwm, 255);
 lcd.clear();
 lcd.print("Circuit Digest ");
 delay(2000);
}
void loop()
{
  DHT.read11(dht_dpin); // считываем значение с выхода датчика температуры
  int temp=DHT.temperature; // извлекаем из него температуру
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temp);   // показываем значение температуры на ЖК дисплее
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(0,1);
  if(temp <26 )
    { 
      analogWrite(9,0);
      lcd.print("Fan OFF            ");
      delay(100);
    }
    
    else if(temp==26)
    {
      analogWrite(pwm, 51);
      lcd.print("Fan Speed: 20%   "); // скорость вращения 20%
      delay(100);
    }
    
     else if(temp==27)
    {
      analogWrite(pwm, 102);
      lcd.print("Fan Speed: 40%   "); // скорость вращения 40%
      delay(100);
    }
    
     else if(temp==28)
    {
      analogWrite(pwm, 153);
      lcd.print("Fan Speed: 60%   "); // скорость вращения 60%
      delay(100);
    }
    
    else if(temp==29)
    {
      analogWrite(pwm, 204);
      lcd.print("Fan Speed: 80%    "); // скорость вращения 80%
      delay(100);
    }
     else if(temp>29)
    {
      analogWrite(pwm, 255);
      lcd.print("Fan Speed: 100%   "); // скорость вращения 100%
      delay(100);
    } 
  delay(3000);
}