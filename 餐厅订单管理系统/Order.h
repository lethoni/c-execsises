#include<iostream>
#ifndef ORDER_H
#define ORDER_H
#include<cstring>
#include "Menu.h"
#include "Date.h"

using namespace std;

class Order: public Menu
{
public:
    Order();
    Order(string dishName, string dishID, double price, string customerName, string address, string phone, Date bookDate);
    Order(string dishName, string dishID, double price);
    Order(Menu, int);
    void setCustomerName(string);
    void setAddress(string);
    void setPhone(string);
    void setNum(int);
    void setModify(bool);
    void setBookDate(Date);
    string getCustomerName();
    string getAddress();
    string getPhone();
    int getNum();
    bool getModify();
    Date getBookDate();
    ~Order();

protected:
    string customerName, address, phone;
    int num;
    bool modify;
    Date bookDate;
};
#endif // ORDER_H
