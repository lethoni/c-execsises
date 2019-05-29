#ifndef DATE_H
#define DATE_H
#include<iostream>

using namespace std;

class Date
{
public:
    Date();
    Date(int year, int month, int day, int hour);
    void setYear(int);
    void setMonth(int);
    void setDay(int);
    void setHour(int);
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    friend ostream& operator<<(ostream&,const Date&);
    ~Date();

protected:
    int year, month, day, hour;
};
#endif // DATE_H
