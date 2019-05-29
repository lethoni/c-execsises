#include<iostream>
#include<cstdlib>
#include<vector>
#include "Menu.h"
#include "Date.h"
#include "Order.h"
#include "Buyer.h"
#include "Seller.h"

using namespace std;

void buyerMode();
void sellerMode();
void sellerControlMenu();
void mainControlMenu();
void buyerControlMenu();

int main()
{
    Seller s;
    string psd;
    int choose;
    //显示菜单
    mainControlMenu();
    //选择菜单
    while(cin>>choose)
    {
        switch(choose)
        {
        case 1:
            cout<<"\n"<<"Please enter password : ";
            cin>>psd;
            if (psd == s.getPassword()) sellerMode();
            else cout<<"password error."<<endl;
            break;
        case 2:
            buyerMode();
            break;
        case 3:
            exit(0);
        }
        mainControlMenu();
    }
	return 0;
}

//卖家控制
void sellerMode()
{
    vector<Menu> mu;
	vector<Order> od;
    Seller s;
    string psd, cpsd;
    int choose;
    //显示菜单
    sellerControlMenu();
    while(cin>>choose)
    {
        switch(choose)
        {
        case 1:
            s.modifyOrder(od);
            break;
        case 2:
            s.inquireOrder(od);
            break;
        case 3:
            s.appendMenu(mu);
            break;
        case 4:
            s.canceMenu(mu);
            break;
        case 5:
            cout<<"\n"<<"Please enter a new password : ";
            cin>>psd;
            cout<<"Please enter the password again : ";
            cin>>cpsd;
            if (psd == cpsd)
            {
                s.setPassword(psd);
                cout<<"Setup successfully."<<endl;
            }
            else cout<<"Setup failed."<<endl;
            break;
        case 6:
            return;
        case 7:
            exit(0);
        }
        sellerControlMenu();
    }
}

//顾客控制
void buyerMode()
{
    vector<Menu> mu;
	vector<Order> od;
    Buyer b;
    string psd, cpsd;
    int choose;
    //显示菜单
    buyerControlMenu();
    while(cin>>choose)
    {
        switch(choose)
        {
        case 1:
            b.bookOrder(mu, od);
            break;
        case 2:
            b.modifyOrder(od);
            break;
        case 3:
            b.inquireOrder(od);
            break;
        case 4:
            return;
        case 5:
            exit(0);
        }
        buyerControlMenu();
    }
}

//主显示菜单
void mainControlMenu()
{
    cout<<endl;
    cout<<"************************"<<endl;
    cout<<"*                      *"<<endl;
    cout<<"*       1. Seller      *"<<endl;
    cout<<"*                      *"<<endl;
    cout<<"*       2. Buyer       *"<<endl;
    cout<<"*                      *"<<endl;
    cout<<"*       3. Exit        *"<<endl;
    cout<<"*                      *"<<endl;
    cout<<"************************"<<endl;
    cout<<"\n"<<"Please choose the mode : ";
}

//卖家显示菜单
void sellerControlMenu()
{
    cout<<endl;
    cout<<"**********************************"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       1. Modify order          *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       2. Inquire order         *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       3. Append menu           *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       4. Cancel menu           *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       5. Set password          *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       6. Back to home page     *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       7. exit                  *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"\n"<<"Please select the function : ";
}

//顾客显示菜单
void buyerControlMenu()
{
    cout<<endl;
    cout<<"**********************************"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       1. Book order            *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       2. Modify order          *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       3. Inquire order         *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       4. Back to home page     *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"*       5. exit                  *"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"\n"<<"Please select the function : ";
}
