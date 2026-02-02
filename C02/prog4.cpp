/////////////////////////////////////////////////////////////////////////
//        此代码片段主要研究auto和decltype的各种用法
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>
#include "wga.h"
using namespace std;

//double add(double a, double b){return a + b;}


//模板函数返回类型推导
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
    return t + u;
}


//处理重载函数
void func(int){return;}
void func(double){return;}
decltype(func(0)) f1(){}      //推导为void(int)
decltype(func(0.0)) f2(){}    //推导为void(double)



//推导容器元素类型
template <typename Container>
void print_first(const Container& c)
{
    using ValueType = decltype(c.begin()[0]);
    ValueType FE = static_cast<ValueType>(c.begin()[0]);
    cout << "First element: " << FE << endl;
    printType(FE);
}


int main()
{
    ///////////////////      auto     ///////////////////////////////////
    vector<int> nums = {1,2,3,4,5,6,7,8};

    //使用auto简化迭代器声明
    auto it = nums.begin();  //编译器自动推导为迭代器类型
    int i =0;
    while (it != nums.end())
    {
        cout << nums.at(i++) << ' ';
        it++;
    }
    splitline();

    //auto在range-base-for循环中的常规用法
    for (auto num : nums) cout << num << ' ';
    splitline();

    for (auto& num : nums) num *=2;
    for (auto num : nums) cout << num << ' ';
    splitline();

    printType(nums);
    printType(it);
    printType(i);
    splitline();

    //使用auto处理lambda表达式
    auto compare = [](int a, int b){return a < b;}; //auto推导lambda函数类型
    vector<int> data = {8,3,45,7,2,9};
    sort(data.begin(),data.end(),compare);
    for (auto x: data) cout << x << ' ';
    splitline();

    ///////////////////      decltype     ///////////////////////////////////
    int a = 10;
    const int &b = a;
    decltype(a) x = 20;      //x 推导为 int
    decltype(b) y = x;       //y 推导为 const int&
    decltype(a + 5) z =30;   //z 推导为 int
    printType(x);
    printType(y);
    printType(z);
    splitline();

    //模板函数返回类型推导
    string astr = "hello ", bstr = "world!";
    auto res = add(astr , bstr); //推导res返回类型为string
    cout << res << " \nType name -> ";
    printType(res);
    splitline();

    //打印重载函数返回类型
    printType(f1);
    printType(f2);
    splitline();


    //推导容器元素类型
    vector<double> vec = {1.1,2.2,3.3,4.4,3.14159};
    print_first(vec);
    splitline();

    return 0;
}


