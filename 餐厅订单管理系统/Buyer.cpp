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
        infile.get(); //��ȡ���Ļس���
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
    //��ȡ�˵�
    ifstream infile("Menu.txt");
    read_menu(mu, infile);
    infile.close();
    //�жϲ˵��Ƿ�Ϊ��
    if(mu.empty())
    {
        cout<<"Sorry! There is no dish for you to choose!"<<endl;
        return;
    }

    //����˵�
    cout<<"\n"<<"Choose the menu of our shop : "<<endl;
    cout<<"num"<<setw(9)<<"name"<<setw(9)<<"price"<<endl;
    print_menu(mu);
    //�ж�1�㵥��2���
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
                    //����˵�
                    od.push_back(Order(mu[i],m));
                    break;
                }
                //��Ų������ٴ�����˵�
                if (i == mu.size()-1)
                {
                    cout<<"\n"<<"There is no such dish!"<<endl;
                    printControlMenu();;
                    can = 0;
                }
            }
            if (!can) continue;
            //��������
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
    //�ж�Ԥ���Ƿ�Ϊ��
    if (appNum == 0)
    {
		cout<<"\n"<<"You haven't ordered anything!"<<endl;
        return;
    }
    //��ӡ��ѡ�˵�
    cout<<"\n"<<"Here is the dish you have ordered: "<<endl;
    cout<<"=========================================="<<endl;
    cout<<"num"<<"\tname"<<"\tprice"<<"\tquantity"<<endl;
    for (i = 0; i < od.size(); i++)
    {
        cout<<od[i].getDishID()<<"\t"<<od[i].getDishName()<<"\t"<<od[i].getPrice()<<"\t"<<od[i].getNum()<<endl;
    }
    cout<<"=========================================="<<endl;
    //������������ַ���绰
    /*str="\n";
    getline(cin,str); //���������
    getline(cin, name); //�ɽ��պ��ո�����*/
    cout<<"Please enter your name: ";
    cin>>name;
    cout<<"Please enter your address: ";
    cin>>address;
    cout<<"Please enter your phone: ";
    cin>>phone;
    //����Ԥ������
    cout<<"\n"<<"Please input the date you want to have you dish,"<<endl;
	cout<<"just as 2013/5/2 14 (year/month/day hour) : ";
	cin>>year>>ch>>month>>ch>>day>>hour;
    //�洢������Ϣ
    for (i = 0; i < od.size(); i++)
    {
        od[i].setCustomerName(name);
        od[i].setAddress(address);
        od[i].setPhone(phone);
        od[i].setBookDate(Date(year, month, day, hour));
    }
    cout<<"\n"<<"New orders : "<<endl;
    print_order(od);
    //д���ı�
    ofstream ofile("Order.txt", ios::app);
    write_file(od, ofile);
    ofile.close();
    mu.clear();
    od.clear();
    //��ͣ
    cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
    getchar();
    getchar();
}

void Buyer::modifyOrder(vector<Order>&od)
{
    unsigned int i;
    string str;
    bool can = 1, can2 = 1;
    //�ж��Ƿ��ж���
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
        //����˵�
        cout<<endl;
        if (str == "2") break;
        //��ӡȫ������
        else if(str == "1")
        {
            print_order(od);
            //�����޸ı��
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
            //��һ���ж�
            can = 1;
            can2 = 1;
            //��ͣ
            cout<<"\n"<<"Press \"Enter\" to return to the main menu.";
            getchar();
            getchar();
        }
        printControlMenu();
    }
    //д���ļ�
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
    //��ȡ����
    ifstream infile("Order.txt");
    read_file(od,infile);
    infile.close();

    //�����ֲ�ѯ����
    if (name == "\0")
    {
        cout<<"Please enter inquire name: ";
        cin>>name;
    }
    cout<<endl;
    //��ӡ��ѯ����
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
    //��ͣ
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


