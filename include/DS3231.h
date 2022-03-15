#ifndef DS3231_H
#define DS3231_H


class DS3231
{
public:
    bool begin(void); // инициализация, вернет true, если RTC найден

    static void setSecond(uint8_t second);   // Установить секунды
    static void setMinute(uint8_t minute);   // Установить минуты
    static void setHour(uint8_t hour);       // Установить часы
    static void setWeekDay(uint8_t weekday); // Установить день недели
    static void setDay(uint8_t day);         // Установить день месяца
    static void setMonth(uint8_t month);     // Установить месяц
    static void setYear(uint8_t year);       // Установить год

    static uint8_t getSecond(void);  // Получить секунды
    static uint8_t getMinute(void);  // Получить минуты
    static uint8_t getHour(void);    // Получить часы
    static uint8_t getWeekDay(void); // Получить день недели
    static uint8_t getDay(void);     // Получить день месяца
    static uint8_t getMonth(void);   // Получить месяц
    static uint16_t getYear(void);   // Получить год

    float getTemperatureFloat(void); // получить температуру float
    int getTemperature(void);        // получить температуру

private:
    // static uint8_t encodeRegister(int8_t data);
    static int getTemperatureRaw(void);
    static uint8_t readRegister(uint8_t addr);
    static uint8_t unpackRegister(uint8_t data);
    static uint8_t unpackHours(uint8_t data);
};

#endif