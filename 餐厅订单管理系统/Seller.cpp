#include<fstream>
#include<iomanip>
#include "Seller.h"

using namespace std;

void print_menu(vector<Menu>);
void write_file(vector<Order>&, ofstream&);
void print_order(vector<Order>);
void read_file(vector<Order>&, ifstream&);

void write_menu(vector<Menu> &mu, ofstream &outfile)
{
    unsigned i;
    if (!outfile)
    {
        cout<<"The system can't read the file!";
        return;
    }
    for (i = 0; i < mu.size(); i++)
    {
        outfile<<mu[i].getDishID()<<" "<<mu[i].getDishName()<<" "<<mu[i].getPrice()<<endl;
    }
}

void read_menu(vector<Menu> &mu, ifstream &infile)
{
    string num, name;
    double price;
    //读取菜单
    if (!infile)
    {
        cout<<"The system can't read the file!";
        return;
    }
    while(infile)
    {
        infile>>num>>name>>price;
        if (infile.fail()) break;
        mu.push_back(Menu(name, num, price));
    }
}

void printControlMenu()
{
    cout<<endl;
    cout<<"**************************"<<endl;
    cout<<"*                        *"<<endl;
    cout<<"*       1. Continue      *"<<endl;
    cout<<"*                        *"<<endl;
    cout<<"*       2. Return        *"<<endl;
    cout<<"*                        *"<<endl;
    cout<<"**************************"<<endl;
    cout<<"\n"<<"Please choose the mode : ";
}

void modifyOneControlMenu()
{
    cout<<endl;
    cout<<"****************************"<<endl;
    cout<<"*                          *"<<endl;
    cout<<"*       1. Modify one      *"<<endl;
    cout<<"*                          *"<<endl;
    cout<<"*       2. Return          *"<<endl;
    cout<<"*                          *"<<endl;
    cout<<"****************************"<<endl;
    cout<<"\n"<<"Please choose the mode : ";
}

void modifyControlMenu()
{
    cout<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"*                                       *"<<endl;
    cout<<"*       1. All modifications            *"<<endl;
    cout<<"*                                       *"<<endl;
    cout<<"*       2. Print unconfirmed order      *"<<endl;
    cout<<"*                                       *"<<endl;
    cout<<"*       3. Return                       *"<<endl;
    cout<<"*                                       *"<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"\n"<<"Please choose the mode : ";
}

Seller::Seller(){};

void Seller::modifyOrder(vector<Order>& od)
{
    string str;
    unsigned i;
    int choose;
    bool can = 1;
    vector<Order> unorder;
    //读取订单
    ifstream infile("Order.txt");
    read_file(od, infile);
    infile.close();
    //检查未确认订单
    for (i = 0; i < od.size(); i++)
    {
        if (od[i].getModify() == 1)
        {
            unorder.push_back(od[i]);
            can = 0;
        }
    }
    if (can)
    {
        cout<<"All orders have been confirmed."<<endl;
    }
    //选择菜单
    modifyControlMenu();
    while(cin>>choose)
    {
        switch(choose)
        {
        case 3: //退出
            unorder.clear();
            od.clear();
            return;
        case 2: //打印未确认订单
                cout<<endl;
                if (unorder.empty()) cout<<"All orders have been confirmed."<<endl;
                else
                {
                    print_order(unorder);
                    //选择菜单
                    modifyOneControlMenu();
                    while(cin>>choose)
                    {
                        switch(choose)
                        {
                        case 1: //修改指定订单
                            can = 1;
                            cout<<"Please enter order number: ";
                            cin>>str;
                            for (i = 0; i < od.size(); i++)
                            {
                                if (str == od[i].getDishID())
                                {
                                    od[i].setModify(0);
                                    can = 0;
                                }
                            }
                            if (!can) cout<<"Modification completed."<<endl;
                            else cout<<"Order not find."<<endl;
                            break;
                        case 2: //写入文件
                            ofstream ofile("Order.txt");
                            write_file(od, ofile);
                            ofile.close();
                            unorder.clear();
                            od.clear();
                            return;
                        }
                        modifyOneControlMenu();
                    }
                }
                break;
        case 1: //全部确认
            for (i = 0; i < od.size(); i++)
            {
                if (od[i].getModify() == 1) od[i].setModify(0);
            }
            ofstream ofile("Order.txt");
            write_file(od, ofile);
            ofile.close();
            cout<<"Modification completed."<<endl;
            unorder.clear();
            od.clear();
            return;
        }
        modifyControlMenu();
    }
}

void Seller::inquireOrder(vector<Order> &od)
{
    //打开订单
    ifstream infile("Order.txt");
    read_file(od, infile);
    infile.close();
    //显示订单
    print_order(od);
    od.clear();
    cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
    getchar();
    getchar();
}

void Seller::appendMenu(vector<Menu>& mu)
{
    string num, name, str;
    double price;
    cout<<"\n"<<"Do you need to add a menu?"<<endl;
    printControlMenu();
    while(cin>>str)
    {
        if (str == "2") break;
        //增加菜单
        cout<<"\n"<<"Please enter the menu id: ";
        cin>>num;
        cout<<"Please enter the menu name: ";
        cin>>name;
        cout<<"Please enter the menu price: ";
        cin>>price;
        mu.push_back(Menu(name, num, price));
        printControlMenu();
    }

    if (mu.empty())
    {
        cout<<"No menu added.";
        return;
    }
    //写入文件
    ofstream outfile("Menu.txt", ios::app);
    write_menu(mu, outfile);
    outfile.close();
    cout<<"\n"<<"New menu has been added.";
    mu.clear();
}

void Seller::canceMenu(vector<Menu>& mu)
{
    string str;
    unsigned i, id;
    bool can = 1, isBreakLoop = 1;
    //读取菜单
    ifstream infile("Menu.txt");
    read_menu(mu, infile);
    infile.close();
    //修改菜单
    print_menu(mu);
    cout<<"\n"<<"Do you need to delete a menu?"<<endl;
    printControlMenu();
    while(isBreakLoop&&(cin>>id))
    {
        switch(id)
        {
        case 2:
            isBreakLoop = 0;
            break;
        case 1:
            cout<<"Please enter the deletion number: ";
            cin>>str;
            for (i = 0; i < mu.size(); i++)
            {
                if (str == mu[i].getDishID())
                {
                    can = 0;
                    mu.erase(mu.begin()+i);
                    cout<<str<<" has been deleted."<<endl;
                }
            }
            if (can) cout<<"The number no find."<<endl;

        default:
            can = 1;
            printControlMenu();
        }
    }
    //更新文件
    ofstream outfile("Menu.txt");
    write_menu(mu, outfile);
    outfile.close();
    cout<<"New menu is done."<<endl;
    mu.clear();
}

void Seller::setPassword(string psd)
{
    password = psd;
    ofstream outfile("Password.txt");
    outfile<<password;
    outfile.close();
}

string Seller::getPassword()
{
    string psd;
    ifstream infile("Password.txt");
    getline(infile, psd);
    infile.close();
    return psd;
}
