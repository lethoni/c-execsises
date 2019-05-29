#include<iostream>
#include<cstring>
#include<vector>
#include "User.h"
#include "Menu.h"
#include "Order.h"

using namespace std;

class Seller: public User
{
public:
    Seller();
    void modifyOrder(vector<Order>&);
    void inquireOrder(vector<Order>&);
    void appendMenu(vector<Menu>&);
    void canceMenu(vector<Menu>&);
    void setPassword(string);
    string getPassword();
protected:
    string password;
};
