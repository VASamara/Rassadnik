#include <Arduino.h>
#include <Wire.h>
#include "DS3231.h"

static const uint8_t DS3231_ADDR = 0x68;

bool DS3231::begin(void)
{
    Wire.begin();                        // Инит шины
    Wire.beginTransmission(DS3231_ADDR); // Зовем DS3231 по адресу
    return (!Wire.endTransmission());    // если никто не откликнулся - возвращаем false
}

uint8_t DS3231::getSecond(void)
{
    return (unpackRegister(readRegister(0x00)));
}

uint8_t DS3231::getMinute(void)
{
    return (unpackRegister(readRegister(0x01)));
}

uint8_t DS3231::getHour(void)
{
    return (unpackHours(readRegister(0x02)));
}

uint8_t DS3231::getWeekDay(void)
{
    return readRegister(0x03);
}

uint8_t DS3231::getDay(void)
{
    return (unpackRegister(readRegister(0x04)));
}

uint8_t DS3231::getMonth(void)
{
    return (unpackRegister(readRegister(0x05)));
}

uint16_t DS3231::getYear(void)
{
    return (unpackRegister(readRegister(0x06)) + 2000);
}

uint8_t DS3231::readRegister(uint8_t addr)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(addr);
    if (Wire.endTransmission() != 0)
        return 0;
    Wire.requestFrom(DS3231_ADDR, (uint8_t)1);
    uint8_t data = Wire.read();
    return data;
}

uint8_t DS3231::unpackRegister(uint8_t data)
{
    return ((data >> 4) * 10 + (data & 0xF));
}

uint8_t DS3231::unpackHours(uint8_t data)
{
    if (data & 0x20)
        return ((data & 0xF) + 20);
    else if (data & 0x10)
        return ((data & 0xF) + 10);
    else
        return (data & 0xF);
}

float DS3231::getTemperatureFloat(void)
{
    return (getTemperatureRaw() * 0.25f);
}

int DS3231::getTemperature(void)
{
    return (getTemperatureRaw() >> 2);
}

int DS3231::getTemperatureRaw(void)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x11);
    Wire.endTransmission();
    Wire.requestFrom(DS3231_ADDR, (uint8_t)2);
    return ((int8_t)Wire.read() << 2) + (Wire.read() >> 6);
}

void DS3231::setSecond(uint8_t second)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x00);
    second = ((second / 10) << 4) | (second % 10);
    Wire.write(second);
    Wire.endTransmission();
}

void DS3231::setMinute(uint8_t minute)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x01);
    minute = ((minute / 10) << 4) | (minute % 10);
    Wire.write(minute);
    Wire.endTransmission();
}

void DS3231::setHour(uint8_t hour)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x02);
    if (hour > 19)
        Wire.write((0x2 << 4) | (hour % 20));
    else if (hour > 9)
        Wire.write((0x1 << 4) | (hour % 10));
    else
        Wire.write(hour);
    Wire.endTransmission();
}

void DS3231::setWeekDay(uint8_t weekday)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x03);
    Wire.write(weekday);
    Wire.endTransmission();
}

void DS3231::setDay(uint8_t day)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x04);
    day = ((day / 10) << 4) | (day % 10);
    Wire.write(day);
    Wire.endTransmission();
}

void DS3231::setMonth(uint8_t month)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x05);
    month = ((month / 10) << 4) | (month % 10);
    Wire.write(month);
    Wire.endTransmission();
}

void DS3231::setYear(uint8_t year)
{
    Wire.beginTransmission(DS3231_ADDR);
    Wire.write(0x06);
    year = ((year / 10) << 4) | (year % 10);
    Wire.write(year);
    Wire.endTransmission();
}