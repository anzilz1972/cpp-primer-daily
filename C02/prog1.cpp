#include <iostream>
using namespace std;

//使用指针交换A和B
//C+编程中不建议使用
void SwapAB(int *p1 , int *p2);   

//使用引用传递参数，交换A和B
//C++编程建议使用，好处：安全、显式化、避免数据复制
void SwapAB(int& a , int& b);


int main() {
    cout << "Enter two numbers:" << endl;
    int v1 = 0 , v2 = 0 , prod;
    cin >> v1 >> v2;
    cout << "------------------------------------------------------" << endl;

    cout << "The sum of " << v1 << " and " << v2  << " is " 
          << v1 + v2 << endl;
    cout << "------------------------------------------------------" << endl;
    
    SwapAB(&v1 , &v2);  //使用指针交换A和B

    prod = v1 * v2;

    cout << "The product of " << v1 << " and " << v2
         << " is " << prod << endl;
    cout << "------------------------------------------------------" << endl;


    SwapAB(v1,v2);  //使用引用交换A和B
    cout << "Now v1 = " << v1 << " , v2 = " << v2 << endl;
    cout << "------------------------------------------------------" << endl;


    //定义两个引用，以交换V1和v2的值
    int &refv1 = v1 , &refv2 = v2 , tmp =0;
    tmp = refv1;
    refv1 = refv2;
    refv2 = tmp;
    cout << "Now v1 = " << v1 << " , v2 = " << v2 << endl;
    return 0;
}


//使用引用传递参数，交换A和B
//C++编程建议使用，好处：安全、显式化、避免数据复制
void SwapAB(int &a , int &b)
{
     int c = a;
     a = b;
     b = c;
     return;
}

//使用指针交换A和B
//C+编程中不建议使用
void SwapAB(int *p1,int *p2)
{
     int c;
     c = *p1;
     *p1 = *p2;
     *p2 = c;
     //cout << " *p1 = " << *p1 << " *p2 = " << *p2 << endl;
     return;
}