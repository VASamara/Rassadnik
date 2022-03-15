#include <menu.h>
extern LiquidCrystal_I2C lcd;
extern AHT10 aht10;
extern DS3231 rtc;
extern int8_t tempHeatNow;
extern EncButton<EB_TICK, 3, 2, 0> enc;
extern MicroDS18B20<DALLAS_1> ds;

void MenuLCD::MainMenu()
{
    lcd.setCursor(0, 0);
    lcd.print(F("  :    tHeat   C"));
    lcd.setCursor(0, 1);
    lcd.print(F("Temp   C Him   %"));

    lcd.setCursor(0, 0);
    if (rtc.getHour() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getHour());
    lcd.setCursor(3, 0);
    if (rtc.getMinute() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getMinute());
    lcd.setCursor(5, 1);
    lcd.print(int8_t(aht10.getTemperature()));
    lcd.setCursor(13, 1);
    lcd.print(int8_t(aht10.getHumidity()));
    lcd.setCursor(13, 0);
    lcd.print(tempHeatNow);
    //lcd.print(int8_t(ds.getTemp()));
}

void MenuLCD::DateTimeSet()
{
    while (1)
    {

        enc.tick();
        lcd.blink();
        uint8_t psp[6]{};
        uint8_t sim[]{0, 3, 6, 9, 12, 14};
        uint8_t str[]{1, 1, 1, 1, 1, 1};
        uint8_t i = constrain(i, 0, 5);
        if (enc.right())
            i++;
        if (enc.left())
            i--;
        lcd.setCursor(sim[i], str[i]);

        if (enc.click())
        {

            while (1)
            {
                enc.tick();
                psp[0] = constrain(enc.counter, 0, 23);
                psp[1] = constrain(enc.counter, 0, 59);
                psp[2] = constrain(enc.counter, 0, 59);
                psp[3] = constrain(enc.counter, 1, 31);
                psp[4] = constrain(enc.counter, 1, 12);
                psp[5] = constrain(enc.counter, 1, 7);

                lcd.setCursor((sim[i]), str[i]);
                if (psp[i] < 10)
                    lcd.print(0);
                lcd.print(psp[i]);
                if (enc.click())
                {
                    if (i == 0)
                        rtc.setHour(psp[i]);
                    if (i == 1)
                        rtc.setMinute(psp[i]);
                    if (i == 2)
                        rtc.setSecond(psp[i]);
                    if (i == 3)
                        rtc.setDay(psp[i]);
                    if (i == 4)
                        rtc.setMonth(psp[i]);
                    if (i == 5)
                        rtc.setWeekDay(psp[i]);
                    lcd.noBlink();
                    enc.counter = 1;
                    return;
                }
            }
        }
    }
}

void MenuLCD::DateTime()
{
    lcd.setCursor(0, 0);
    lcd.print(F("Hr Mt Sc DM Mo D"));
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    if (rtc.getHour() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getHour());
    lcd.setCursor(3, 1);
    if (rtc.getMinute() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getMinute());
    lcd.setCursor(6, 1);
    if (rtc.getSecond() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getSecond());
    lcd.setCursor(9, 1);
    if (rtc.getDay() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getDay());
    lcd.setCursor(12, 1);
    if (rtc.getMonth() < 10)
        lcd.print(F("0"));
    lcd.print(rtc.getMonth());
    lcd.setCursor(15, 1);
    lcd.print(rtc.getWeekDay());
}

void MenuLCD::LightingSet()
{
    while (1)
    {

        enc.tick();
        lcd.blink();
        uint8_t psp[5]{};
        uint8_t sim[]{3, 6, 3, 6, 13};
        uint8_t str[]{0, 0, 1, 1, 1};
        uint8_t num[]{EE_SUNRISE_HOUR, EE_SUNRISE_MINUTE, EE_SUNSET_HOUR, EE_SUNSET_MINUTE, EE_DURATION_SUN};
        uint8_t i = constrain(i, 0, 4);
        if (enc.right())
            i++;
        if (enc.left())
            i--;
        lcd.setCursor(sim[i], str[i]);

        if (enc.click())
        {

            while (1)
            {
                enc.tick();
                psp[0] = constrain(enc.counter, 0, 23);
                psp[1] = constrain(enc.counter, 0, 59);
                psp[2] = constrain(enc.counter, 0, 23);
                psp[3] = constrain(enc.counter, 0, 59);
                psp[4] = constrain(enc.counter, 0, 59);

                lcd.setCursor((sim[i]), str[i]);
                if (psp[i] < 10)
                    lcd.print(0);
                lcd.print(psp[i]);
                if (enc.click())
                {
                    EEPROM.put(num[i], psp[i]);
                    lcd.noBlink();
                    enc.counter = 2;
                    return;
                }
            }
        }
    }
}

void MenuLCD::Lighting()
{
    lcd.setCursor(0, 0);
    lcd.print(F("Rs   :    Svet  "));
    lcd.setCursor(0, 1);
    lcd.print(F("Zk   :   Dlt   m"));

    lcd.setCursor(3, 0);
    if (EEPROM.read(EE_SUNRISE_HOUR) < 10)
        lcd.print(F("0"));
    lcd.print(EEPROM.read(EE_SUNRISE_HOUR));
    lcd.setCursor(6, 0);
    if (EEPROM.read(EE_SUNRISE_MINUTE) < 10)
        lcd.print(F("0"));
    lcd.print(EEPROM.read(EE_SUNRISE_MINUTE));
    lcd.setCursor(3, 1);
    if (EEPROM.read(EE_SUNSET_HOUR) < 10)
        lcd.print(F("0"));
    lcd.print(EEPROM.read(EE_SUNSET_HOUR));
    lcd.setCursor(6, 1);
    if (EEPROM.read(EE_SUNSET_MINUTE) < 10)
        lcd.print(F("0"));
    lcd.print(EEPROM.read(EE_SUNSET_MINUTE));
    lcd.setCursor(13, 1);
    if (EEPROM.read(EE_DURATION_SUN) < 10)
        lcd.print(F("0"));
    lcd.print(EEPROM.read(EE_DURATION_SUN));
}

void MenuLCD::HeatingSet()
{
    while (1)
    {

        enc.tick();
        lcd.blink();
        uint8_t psp[3]{};
        uint8_t sim[]{5, 5, 13};
        uint8_t str[]{0, 1, 1};
        uint8_t num[]{EE_TEMP_HEATING_DAY, EE_TEMP_HEATING_NIGHT, EE_HEATING_PWM};
        uint8_t i = constrain(i, 0, 2);
        if (enc.right())
            i++;
        if (enc.left())
            i--;
        lcd.setCursor(sim[i], str[i]);

        if (enc.click())
        {

            while (1)
            {
                enc.tick();

                psp[0] = constrain(enc.counter, 5, 40);
                psp[1] = constrain(enc.counter, 5, 40);
                psp[2] = constrain(enc.counter, 0, 255);

                lcd.setCursor((sim[i]), str[i]);
                if (psp[i] < 10)
                    lcd.print(0);
                lcd.print(psp[i]);
                if (enc.click())
                {
                    EEPROM.put(num[i], psp[i]);
                    lcd.noBlink();
                    enc.counter = 3;
                    return;
                }
            }
        }
    }
}

void MenuLCD::Heating()
{
    lcd.setCursor(0, 0);
    lcd.print(F("TmpD   C  Heat  "));
    lcd.setCursor(0, 1);
    lcd.print(F("TmpN   C PWM    "));
    lcd.setCursor(5, 0);
    lcd.print(EEPROM.read(EE_TEMP_HEATING_DAY));
    lcd.setCursor(5, 1);
    lcd.print(EEPROM.read(EE_TEMP_HEATING_NIGHT));
    lcd.setCursor(13, 1);
    lcd.print(EEPROM.read(EE_HEATING_PWM));
}
