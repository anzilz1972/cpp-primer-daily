/*
本代码片段：
  1、测试 std::cin 的各种函数用法
     1）用cin.eof() 判断输入结束
     2）用 cin.fail() 判断输入错误
     3）用 cin.clear() 重置所有错误
     4）用 cin.ignore() 忽略缓冲区所有内容直到换行
  2、测试 vector<int> 对象
*/
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "wga.h"
using namespace std;


int main()
{
    
    vector<int> ivec;

    //输入一系列整数，以EOF结束
    //Windows环境下，EOF是--> "Ctrl+D 加 回车"
    //Linux/macOS 环境下，EOF是--> "Ctrl+D"
    cout << " Under windows,     ****** EOF --> Ctrl+Z + ENTER ******" << endl;
    cout << " Under Linux/macOS, ****** EOF -->     Ctrl+D     ******" << endl;
    cout << "Input some numbers,End of EOF:" << endl;
    int nums;
    while (true)
    {
        cin >> nums;
        //判断是否读取到EOF
        if (cin.eof()) break;

        //判断是否输入错误（诸如类型不匹配等）
        if (cin.fail())
        {
            cout << "Input ERROR,Try again!!!" << endl;
            //重置错误状态
            cin.clear();
            //清空缓冲区的错误输入并继续输入
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        ivec.push_back(nums);
    }

    splitline();

    //输出 Vector 的内容
    cout << endl << ivec.size() << " numbers: " ;
    for (auto i:ivec) cout << i << ' ';
    cout << endl;

    return 0;
}