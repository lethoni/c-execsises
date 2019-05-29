#ifndef MENU_H
#define MENU_H
#include<iostream>
#include<cstring>

using namespace std;

class Menu
{
public:
    Menu();
    Menu(string dishName, string dishID, double price);
    void setDishName(string);
    void setDishID(string);
    void setPrice(double);
    string getDishName();
    string getDishID();
    double getPrice();
    ~Menu();

protected:
    string dishName, dishID;
    double price;
};
#endif // MENU_H
