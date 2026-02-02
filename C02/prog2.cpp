#include <iostream>
#include <vector>
using namespace std;


//使用“底层const字符数组”传参，防止被修改，建议：void PrintString(const char * p)
//不建议“使用顶层const指针出现只读指针"，除增加程序复杂性和可读性外没有实际意义，如下： 
void PrintString(const char *const ptr)
{
    const char *p = ptr;
    while (*p++) cout << *p;
    return;
}

//返回Vector的引用，避免拷贝
vector<int>& getVector()
{
    static vector<int> data = {1,2,3,4,5,6,7}; // 静态变量生命周期长 
    return data;
}


class stringBuilder
{
private:
    string str;
public:
    //append成员函数返回对象的引用
    stringBuilder& append(const string& s)
    {
        str += s;
        return *this;
    }
    void print() 
    {
        cout << str << endl;
    }
};


int main()
{
    vector<int> vec = getVector(); //直接引用，无拷贝
    vec.push_back(8);
    for (int num : vec) cout << num << ' ';
    cout << endl;

    stringBuilder astr;
    astr.append("hello ").append("world!").print();

    //测试底层const和顶层const
    char bstr[]="This is a const char array!";
    PrintString(bstr);

    return 0;
}