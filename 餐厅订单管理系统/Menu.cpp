#include "Menu.h"

Menu::Menu(){}

Menu::Menu(string dN, string dI, double pr):
     dishName(dN), dishID(dI), price(pr){}

void Menu::setDishName(string dN)
{
    dishName = dN;
}

void Menu::setDishID(string dI)
{
    dishID = dI;
}

void Menu::setPrice(double pr)
{
    price = pr;
}

string Menu::getDishName()
{
    return dishName;
}

string Menu::getDishID()
{
    return dishID;
}

double Menu::getPrice()
{
    return price;
}

Menu::~Menu(){}
