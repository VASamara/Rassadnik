#include <data.h>

extern DS3231 rtc;
extern MicroDS18B20<DALLAS_1> ds;
extern EncButton<EB_TICK, 2, 3, 0> enc;
extern AHT10 aht10;
int8_t tempHeatNow;
uint8_t tempIn;
uint8_t tempOut;
elapsedSeconds interVal;
elapsedMillis emds;
elapsedSeconds dsInt;

void Heat::Heating()
{
    if (dsInt >= 10)
    {
        dsInt = 0;
        bool day;
        if ((rtc.getHour() >= EEPROM.read(EE_SUNRISE_HOUR)) && (rtc.getHour() < EEPROM.read(EE_SUNSET_HOUR)))
            day = true;
        else
            day = false;

        ds.requestTemp();
        if (emds >= 1000)
            if (ds.readTemp())
                tempHeatNow = (int8_t(ds.getTemp()));
        if (tempHeatNow < EEPROM.read(EE_TEMP_HEATING_DAY) && (day == true))
            analogWrite(HEAT, EEPROM.read(EE_HEATING_PWM));
        if (tempHeatNow > EEPROM.read(EE_TEMP_HEATING_DAY) && (day == true))
            analogWrite(HEAT, 0);
        if (tempHeatNow < EEPROM.read(EE_TEMP_HEATING_NIGHT) && (day == false))
            analogWrite(HEAT, EEPROM.read(EE_HEATING_PWM));
        if (tempHeatNow > EEPROM.read(EE_TEMP_HEATING_NIGHT) && (day == false))
            analogWrite(HEAT, 0);
    }
}
