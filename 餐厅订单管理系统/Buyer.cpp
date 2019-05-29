#include<fstream>
#include<vector>
#include<iomanip>
#include "Order.h"
#include "Buyer.h"

using namespace std;

void printControlMenu();

void print_menu(vector<Menu> mu)
{
    unsigned int i;
    for (i = 0; i < mu.size(); i++)
    {
        cout<<mu[i].getDishID()<<"\t"<<mu[i].getDishName()<<"\t"<<mu[i].getPrice()<<endl;
    }
}

void print_order(vector<Order> od)
{
    unsigned int i;
    cout<<"num"<<setw(10)<<"name"<<setw(10)<<"price"<<setw(10)<<"amount"<<setw(10)<<"customer"<<setw(10)<<"address"<<setw(10)<<"phone"<<setw(15)<<"date"<<endl;
    for (i = 0; i < od.size(); i++)
    {
        cout<<od[i].getDishID()<<setw(10)<<od[i].getDishName()<<setw(10)<<od[i].getPrice()<<setw(8)<<od[i].getNum()<<setw(10)
            <<od[i].getCustomerName()<<setw(10)<<od[i].getAddress()<<setw(15)<<od[i].getPhone()<<setw(10)<<od[i].getBookDate()<<endl;
    }
}

void write_file(vector<Order>&od, ofstream &outfile)
{
    unsigned int i;
    if (!outfile)
    {
		cout<<"\n"<<"The system can't find the file!"<<endl;
		return;
    }
    for (i = 0; i < od.size(); i++)
    {
        outfile<<od[i].getDishID()<<" "<<od[i].getDishName()<<" "<<od[i].getPrice()<<" "
                <<od[i].getNum()<<" "<<od[i].getCustomerName()<<" "<<od[i].getAddress()<<" "
                <<od[i].getPhone()<<" "<<od[i].getBookDate()<<" "<<od[i].getModify()<<endl;
    }
}

void read_file(vector<Order>&od, ifstream &infile)
{
    unsigned i = 0;
    int num, year, month, day, hour;
    string id, name, customer, address, phone;
    double price;
    bool modify;
    if(!infile)
    {
        cout<<"\n"<<"The system can't read the file!"<<endl;
		return;
    }
    while (!infile.eof())
    {
        infile>>id>>name>>price>>num>>customer>>address>>phone
              >>year>>month>>day>>hour>>modify;
        od.push_back(Order(name,id,price,customer,address,phone,Date(year,month,day,hour)));
        od[i].setNum(num);
        od[i].setModify(modify);
        i++;
        infile.get(); //读取最后的回车符
        if(infile.peek() == '\n') break;
    }
}

void read_menu(vector<Menu>&, ifstream&);

Buyer::Buyer(){};

void Buyer::bookOrder(vector<Menu>&mu, vector<Order>&od)
{
    unsigned int i;
    int year, month, day, hour, m = 0, appNum = 0;
    string str, name, address, phone;
    char ch;
    bool can;
    //读取菜单
    ifstream infile("Menu.txt");
    read_menu(mu, infile);
    infile.close();
    //判断菜单是否为空
    if(mu.empty())
    {
        cout<<"Sorry! There is no dish for you to choose!"<<endl;
        return;
    }

    //输出菜单
    cout<<"\n"<<"Choose the menu of our shop : "<<endl;
    cout<<"num"<<setw(9)<<"name"<<setw(9)<<"price"<<endl;
    print_menu(mu);
    //判断1点单，2输出
    printControlMenu();;
    while(cin>>str)
    {
        can = 1;
        if (str == "2") break;
        else if (str == "1")
        {
            cout<<"Please input the dish ID : ";
            cin>>str;
            for (i = 0; i < mu.size(); i++)
            {
                if(str == mu[i].getDishID())
                {
                    //保存菜单
                    od.push_back(Order(mu[i],m));
                    break;
                }
                //编号不存在再次输出菜单
                if (i == mu.size()-1)
                {
                    cout<<"\n"<<"There is no such dish!"<<endl;
                    printControlMenu();;
                    can = 0;
                }
            }
            if (!can) continue;
            //输入数量
            appNum++;
            cout<<"Please enter quantity: ";
            cin>>m;
            od[appNum-1].setNum(m);
            printControlMenu();;
        }
        else
        {
            cout<<"\n"<<"num"<<"\tname"<<"\tprice"<<endl;
            print_menu(mu);
            printControlMenu();;
        }
    }
    //判断预定是否为空
    if (appNum == 0)
    {
		cout<<"\n"<<"You haven't ordered anything!"<<endl;
        return;
    }
    //打印已选菜单
    cout<<"\n"<<"Here is the dish you have ordered: "<<endl;
    cout<<"=========================================="<<endl;
    cout<<"num"<<"\tname"<<"\tprice"<<"\tquantity"<<endl;
    for (i = 0; i < od.size(); i++)
    {
        cout<<od[i].getDishID()<<"\t"<<od[i].getDishName()<<"\t"<<od[i].getPrice()<<"\t"<<od[i].getNum()<<endl;
    }
    cout<<"=========================================="<<endl;
    //输入姓名、地址、电话
    /*str="\n";
    getline(cin,str); //先清除缓存
    getline(cin, name); //可接收含空格内容*/
    cout<<"Please enter your name: ";
    cin>>name;
    cout<<"Please enter your address: ";
    cin>>address;
    cout<<"Please enter your phone: ";
    cin>>phone;
    //输入预定日期
    cout<<"\n"<<"Please input the date you want to have you dish,"<<endl;
	cout<<"just as 2013/5/2 14 (year/month/day hour) : ";
	cin>>year>>ch>>month>>ch>>day>>hour;
    //存储输入信息
    for (i = 0; i < od.size(); i++)
    {
        od[i].setCustomerName(name);
        od[i].setAddress(address);
        od[i].setPhone(phone);
        od[i].setBookDate(Date(year, month, day, hour));
    }
    cout<<"\n"<<"New orders : "<<endl;
    print_order(od);
    //写入文本
    ofstream ofile("Order.txt", ios::app);
    write_file(od, ofile);
    ofile.close();
    mu.clear();
    od.clear();
    //暂停
    cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
    getchar();
    getchar();
}

void Buyer::modifyOrder(vector<Order>&od)
{
    unsigned int i;
    string str;
    bool can = 1, can2 = 1;
    //判断是否有订单
    ifstream ifile("Order.txt");
    read_file(od,ifile);
    ifile.close();
    if(od.empty())
    {
        cout<<"Sorry,There is no order."<<endl;
        return;
    }
    cout<<"Do you want to change the order?"<<endl;
    printControlMenu();
    while(cin>>str)
    {
        //输出菜单
        cout<<endl;
        if (str == "2") break;
        //打印全部订单
        else if(str == "1")
        {
            print_order(od);
            //输入修改编号
            cout<<"\n"<<"Please enter modify number: ";
            cin>>str;
            cout<<endl;
            for (i = 0; i < od.size(); i++)
            {
                if (str == od[i].getDishID())
                {
                    can = 0;
                    if(od[i].getModify())
                    {
                        od.erase(od.begin()+i);
                        can2 = 0;
                    }
                }
            }

            if(can) cout<<"No order found."<<endl;
            else if(!can && !can2) cout<<"The order has been cancelled.\n"<<endl;
            else cout<<"The order has been confirmed and cannot be modified."<<endl;
            //下一次判断
            can = 1;
            can2 = 1;
            //暂停
            cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
            getchar();
            getchar();
        }
        printControlMenu();
    }
    //写入文件
    ofstream ofile("Order.txt");
    write_file(od,ofile);
    ofile.close();
    od.clear();
}

void Buyer::inquireOrder(vector<Order>&od)
{
    unsigned i;
    bool can = 0;
    string name = "\0";
    //读取订单
    ifstream infile("Order.txt");
    read_file(od,infile);
    infile.close();

    //用名字查询订单
    if (name == "\0")
    {
        cout<<"Please enter inquire name: ";
        cin>>name;
    }
    cout<<endl;
    //打印查询订单
    for (i = 0; i < od.size(); i++)
    {
        if (od[i].getCustomerName() == name)
        {
            if (!can) cout<<"num"<<setw(10)<<"name"<<setw(10)<<"price"<<setw(10)<<"amount"<<setw(10)<<"customer"<<setw(10)<<"address"<<setw(10)<<"phone"<<setw(15)<<"date"<<endl;
            cout<<od[i].getDishID()<<setw(10)<<od[i].getDishName()<<setw(10)<<od[i].getPrice()<<setw(8)<<od[i].getNum()<<setw(10)
                <<od[i].getCustomerName()<<setw(10)<<od[i].getAddress()<<setw(15)<<od[i].getPhone()<<setw(10)<<od[i].getBookDate()<<endl;
            can = 1;
        }
    }
    if(!can) cout<<"No find order."<<endl;
    //暂停
    cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
    getchar();
    getchar();
    od.clear();
}

int Buyer::getNum()
{
    return num;
}

string Buyer::getName()
{
    return name;
}

void Buyer::setNum(int n)
{
    num = n;
}

Buyer::~Buyer(){};


