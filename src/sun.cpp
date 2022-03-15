#include <sun.h>

extern DS3231 rtc;
elapsedSeconds brightInt;
bool day;
uint8_t bright;

void Sun::Lighting()
{

    if ((rtc.getHour() >= EEPROM.read(EE_SUNRISE_HOUR)) && (rtc.getMinute() >= EEPROM.read(EE_SUNRISE_MINUTE)) && (rtc.getHour() <= 23) && (rtc.getHour() > 0) && (!day) && (rtc.getHour() < EEPROM.read(EE_SUNSET_HOUR)))
    {
        if (brightInt >= (EEPROM.read(EE_DURATION_SUN) * 60 / 256))
        {

            bright++;
            analogWrite(LIGHT, bright);
            brightInt = 0;
            if (bright == 255)
            {
                day = true;
                return;
            }
        }
    }
    if ((rtc.getHour() == EEPROM.read(EE_SUNSET_HOUR)) && (rtc.getMinute() >= EEPROM.read(EE_SUNSET_MINUTE)) && (day) && (rtc.getHour() > EEPROM.read(EE_SUNRISE_HOUR)))
    {
        if (brightInt >= (EEPROM.read(EE_DURATION_SUN) * 60 / 256))
        {

            bright--;
            analogWrite(LIGHT, bright);
            brightInt = 0;
            if (bright == 0)
            {
                day = false;
                return;
            }
        }
    }
}
