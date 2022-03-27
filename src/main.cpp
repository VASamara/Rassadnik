#include <data.h>

MenuLCD menu;
LiquidCrystal_I2C lcd(0x27, 16, 2);
EncButton<EB_TICK, 3, 2, 0> enc;
AHT10 aht10;
DS3231 rtc;
Sun sun;
Heat heat;
MicroDS18B20<DALLAS_1> ds;
elapsedSeconds timeBackLight;

void setup()
{
  pinMode(LIGHT, OUTPUT);
  pinMode(HEAT, OUTPUT);

  lcd.init();
  lcd.backlight();
  timeBackLight = 0;
  Serial.begin(115200);
  Wire.begin();
  enc.getState();
  menu.MainMenu();
}
void loop()
{
  heat.Heating();
  sun.Lighting();

  enc.tick();

  if (enc.right() or enc.left())
  {
    lcd.backlight();
    timeBackLight = 0;
    enc.counter = constrain(enc.counter, 0, 3);

    switch (enc.counter)
    {
    case 0:
      menu.MainMenu();
      break;
    case 1:
      menu.DateTime();
      break;
    case 2:
      menu.Lighting();
      break;
    case 3:
      menu.Heating();
      break;
    }
  }
  if (enc.click())
  {
    lcd.backlight();
    timeBackLight = 0;
    if (enc.counter == 1)
      menu.DateTimeSet();
    if (enc.counter == 2)
      menu.LightingSet();
    if (enc.counter == 3)
      menu.HeatingSet();
  }
  if (timeBackLight >= 300)
    lcd.noBacklight();
}