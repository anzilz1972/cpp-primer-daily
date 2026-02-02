#include <iostream>
#include <string>
#include "wga.h"
#include "sales_data.h"
using namespace std;

int main()
{
    //string data1str = "0-201-78345-X   3          20.0";
    //string data2str = "0-201-78345-X   2          25.0";

    double price = 0;
    sales_data data1,data2;

    //输入sales data1
    cout << "Input ISBN,units_sold and price of data1:" << endl;
    cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;

    //输入sales data2
    cout << "Input ISBN,units_sold and price of data2:" << endl;
    cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold *price;

    splitline();

    if(data1.bookNo != data2.bookNo)  
    {   //两条数据不是指向同一本书，报错返回
        cerr << "Error:Data must refer to the same ISBN!" << endl;
        return -1;
    }

    unsigned totalCnt = data1.units_sold + data2.units_sold;
    double totalRevenue = data1.revenue +data2.revenue;

    cout << "ISBN: " << data1.bookNo << "\n" 
        << "Total Sold: " << totalCnt << "\n" 
        << "Total Revenue: " << totalRevenue << "\n";
    if (totalCnt != 0)
        cout << "Average Price: " << totalRevenue/totalCnt << endl;
    else
        cout << "(no sales)"  << endl;
    return 0;
}

//////////////////sales data////////////////////////
//   ISBN         units_sold price
//0-201-78345-X   3          20.0   
//0-201-78345-X   2          25.0 



