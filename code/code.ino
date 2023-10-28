#include<DHT.h>      // подключаем библиотеку для работы с датчиком 
#include<LiquidCrystal.h> // подключаем библиотеку для работы с ЖК дисплеем
 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // инициализация портов для ЖК
#define DHTPIN 13 // порт для датчика темп

#define DHTTYPE DHT11 // тип датчика темп
DHT dht(DHTPIN, DHTTYPE);
#define pwm 9 // выход на кулер
//int counter = 0;
//bool flag = false;
// #define btnStart 12
bool flag_rez = true; // auto
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
  lcd.print("Fan Speed ");
  lcd.setCursor(0,1);
  lcd.print("Controlling ");
  delay(200);
  analogWrite(pwm, 0);
  lcd.clear();
  lcd.print("Circuit Digest ");

  Serial.begin(9600); // открывает сериал порт
  //Serial.println(counter);
  //pinMode(10, INPUT_PULLUP);
  // pinMode(8, INPUT_PULLUP);
  dht.begin();
  Serial.println("test");
}

void loop()
{
  //int rezhim = digitalRead(11);
  Serial.print("Mod: ");
  Serial.print(flag_rez);
  Serial.println();
  // Serial.println(rezhim);

  int rezistor = analogRead(A0); // ручной режим (пока через резистор)
  if (rezistor > 0) {
    Serial.println("custom");
    Serial.print("rezistor ");
    Serial.print(rezistor);
    Serial.println();
    int speed = map(rezistor, 0, 1023, 0, 255); // конвертируем знаяения для выхода  
    Serial.print("speed ");
    Serial.print(speed);
    Serial.println();
    analogWrite(pwm, speed);
    float per = speed*100/255;
    lcd.print("Fan Speed: "); 
    lcd.print(per);// скорость вращения (еще добавлю в оборотах, пока так)
  }
  else{ 
    Serial.println("auto");
    float temp=dht.readTemperature(); // читаем с датчика температуру
    // if (isnan(temp)) {
    //   Serial.println("Failed to read from DHT sensor");
    //   return;
    // }
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print("Temperature:");
    lcd.print(temp);   // значение температуры на ЖК дисплее
    lcd.write(1);
    lcd.print("C");
    lcd.setCursor(0,1);
    if(temp < 30 )
      { 
        analogWrite(pwm,0);
        lcd.print("Fan OFF");
      }
      
      else if((temp>=30) & (temp<40))
      {
        analogWrite(pwm, 51);
        lcd.print("Fan Speed: 20%"); 
      }
      
      else if((temp>=40) & (temp<70))
      {
        analogWrite(pwm, 102);
        lcd.print("Fan Speed: 40%"); 
      }
      
      else if(temp>70)
      {
        analogWrite(pwm, 255);
        lcd.print("Fan Speed: 100%");
      }
  }
  delay(2000);
}