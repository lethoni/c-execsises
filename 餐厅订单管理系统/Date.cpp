#include "Date.h"

Date::Date(){}

Date::Date(int y, int m, int d, int h):
    year(y), month(m), day(d), hour(h){}

void Date::setYear(int y)
{
    year = y;
}

void Date::setMonth(int m)
{
    month = m;
}

void Date::setDay(int d)
{
    day = d;
}

void Date::setHour(int h)
{
    hour = h;
}

int Date::getYear()
{
    return year;
}

int Date::getMonth()
{
    return month;
}

int Date::getDay()
{
    return day;
}

int Date::getHour()
{
    return hour;
}

ostream& operator<<(ostream&output,const Date&d)
{
    output<<d.year<<" "<<d.month<<" "<<d.day<<" "<<d.hour;
    return output;
}

Date::~Date(){}
