#ifndef USER_H
#define USER_H

#include<iostream>
#include<vector>

using namespace std;

class Order;

class User
{
protected:
    virtual void modifyOrder(vector<Order>&)=0;
    virtual void inquireOrder(vector<Order>&)=0;
};
#endif // USER_H
