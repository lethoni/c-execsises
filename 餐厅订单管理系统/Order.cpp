#include "Order.h"

Order::Order()
{
    modify = 1;
}

Order::Order(string dN, string dID, double pr, string cN, string addr, string ph, Date bD):
    Menu(dN, dID, pr), customerName(cN), address(addr), phone(ph), bookDate(bD)
    {
        modify = 1;
    }

Order::Order(string dN, string dID, double pr): Menu(dN, dID, pr)
{
    modify = 1;
}

Order::Order(Menu m, int n): Menu(m), num(n)
{
    modify = 1;
}

void Order::setCustomerName(string cN)
{
    customerName = cN;
}

void Order::setAddress(string addr)
{
    address = addr;
}

void Order::setPhone(string ph)
{
    phone = ph;
}

void Order::setNum(int n)
{
    num = n;
}

void Order::setBookDate(Date bD)
{
    bookDate = bD;
}

void Order::setModify(bool mD)
{
    modify = mD;
}

string Order::getCustomerName()
{
    return customerName;
}

string Order::getAddress()
{
    return address;
}

string Order::getPhone()
{
    return phone;
}

int Order::getNum()
{
    return num;
}

bool Order::getModify()
{
    return modify;
}

Date Order::getBookDate()
{
    return bookDate;
}

Order::~Order(){}
