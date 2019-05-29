#include<iostream>
#include<cstring>
#include<vector>
#include "User.h"
#include "Date.h"
#include "Order.h"

using namespace std;

class Menu;

class Buyer:public User
{
public:
    Buyer();
    void bookOrder(vector<Menu>&, vector<Order>&);
    void modifyOrder(vector<Order>&);
    void inquireOrder(vector<Order>&);
    int getNum();
    string getName();
    void setNum(int);
    ~Buyer();

protected:
    vector<Order> myOrder;
    string name, address, phone;
    Date bookDate;
    int num;
};
