/////////////////////////////////////////////////////////////////////////
//        此代码片段主要研究constexpr的各种用法
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include "wga.h"
using namespace std;

//1、编译期自动计算阶乘//////////////////////////////////////
constexpr int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n-1);
}

//2、用constexpr函数替代宏定义///////////////////////////////
//宏定义缺点：无类型安全易引发错误
#define MAX(a,b) ((a)>(b) ? (a) : (b))
//constexpr 函数替代宏，类型安全作用域可控
constexpr int max(int a, int b)
{
    return (a > b) ? a:b;
}


//3、模板参数需要编译时常量///////////////////////////////
template <int N> struct Array
{
    int data[N];  //N必须是编译时常量
};

//4、字面类型的自定义类，可以在编译期创建对象
class RightTriangle   //定义一个直角三角形
{
public:
    constexpr RightTriangle(double la, double lb) : legA(la),legB(lb),hypotenuse(sqrt(la * la + lb * lb)){}
    constexpr double get_hypotenuse () const 
    { 
        return this->hypotenuse; 
    }
private:
    double legA,legB,hypotenuse;
};

int main()
{
    //定义圆周率
    constexpr double PI = 3.14159;
    cout << "PI= " << PI;
    splitline();

    //使用静态断言验证编译期条件
    constexpr int carNums = 7;
    static_assert(carNums >= 6,"We need  6 cars at least!");
    cout << "We have " << carNums << " cars.";
    splitline();

    //使用constexpr作为模板参数
    constexpr int size = 10;
    Array<size> arr = {0};
    for (int i = 0; i < size; i++) cout << arr.data[i] << ' ';
    splitline();

    //定义数组大小（编译期确定）
    constexpr int arr_size = 10;
    int arrA[arr_size] = {9,8,7,6,5,4,3,2,1,0};    //合法：数组大小为编译期常量
    for (auto num : arrA) cout << num << ' ';
    splitline();

    //定义数组大小（运行期确定）
    int runtime_size = 10;
    int arrB[runtime_size]= {0,1,2,3,4,5,6,7,8,9}; //合法：数组大小为运行期变量
    for (auto& num : arrB) 
    {
        num *= 3;
        cout << num << ' ';
    }
    splitline();

    //编译期计算factorial(10) == 3,628,800
    constexpr int fact_10 = factorial(10);
    static_assert(fact_10 == 3628800,"Factorial calculation error."); 
    cout << "10! = " << fact_10;
    splitline();

    //运行期计算factorial(9) == 3,628,80
    //阶乘函数自动退化为普通函数
    int x = 9;
    int fact_9 = factorial(x);
    //static_assert(fact_9 == 362880,"Factorial calculation error.");
    cout << "9!  = " << fact_9;
    splitline();

    //调用传统宏
    int biggerNum = MAX(10,20);
    cout << "The max num of 10 and 20 is : " << biggerNum;
    splitline();
    //调用constexpr函数，编译期计算出结果
    cout << "The max num of 30 and 40 is : " << max(30,40);
    splitline();

    //编译期创建对象
    constexpr RightTriangle rt1(6,8);
    constexpr double hypotenuse = rt1.get_hypotenuse();
    cout << "The hypotenuse is : " << hypotenuse;
    splitline();


    return 0;
}