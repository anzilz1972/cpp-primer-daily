#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>
#include "wga.h"

//用cin.peek()检测到输入流中的换行符时，在vector中加入一串特殊字符做标记
//之所以记录换行符，主要是为了将内容区分存放在 vector 和 matrix
//vector 包括：std::vector<int>> 、 std::vector<double>、std::vector<std::string>> 等...
//matrix 包括：std::vector<std::vector<int>>  、 std::vector<std::vector<double>>、std::vector<std::vector<std::string>> 等...
const std::string  LineBreakFlag = "&&LineBreak&&";

// 从cin读入数字和字符串，存储在strVec中
void getStr(std::vector<std::string> &strBuffer);

// 从cin读入数字和字符串，并存储在 T（各种vector） 中
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer);

int main()
{
    std::vector<int> vInt;                     //Integer vector,一维存储
    std::vector<std::vector<int>> matrixInt;   //Integer matrix,二维存储
    std::vector<std::string> vStr;                    //string vector,一维存储
    std::vector<std::vector<std::string>> matrixStr;  //string matrix,二维存储

    //从控制台读入一行或N行字符串，存在在strbuff中，用作初始化各类vector
    std::vector<std::string> strbuff;
    getStr(strbuff);


    //初始化 vectorInt
    splitline();
    std::cout << "Display received TEXT AS Interger vector:" << std::endl;
    InitVector(vInt , strbuff);
    for (auto i : vInt) 
        std::cout << i << " ";

    //初始化 matrixInt,形成二维Interger矩阵
    splitline();
    std::cout << "Display received TEXT AS Interger matrix:" << std::endl;
    InitVector(matrixInt , strbuff);

    //初始化 vectorStr
    splitline();
    std::cout << "Display received TEXT AS string vector:" << std::endl;
    InitVector(vStr , strbuff);
    for (auto s : vStr) 
        std::cout << s << " ";

    //初始化 matrixStr,形成二维string矩阵
    splitline();
    std::cout << "Display received TEXT AS string matrix:" << std::endl;
    InitVector(matrixStr , strbuff);

    splitline();
    return 0;
}

// 从cin读入一行或多行字符串，分解成一个个单词后，存储在strVec中
// 两行相邻的单词之间，在strBuffer中插入 "&&Enter&&" 作为 “换行” 标记
void getStr(std::vector<std::string> &strBuffer)
{
    std::string str;

    //输入多个字符串，以EOF结束
    //Windows     环境下，EOF是--> "Ctrl+Z"
    //Linux/macOS 环境下，EOF是--> "Ctrl+D"
    std::cout << " Under windows,     ****** EOF --> Ctrl+Z ******" << std::endl;
    std::cout << " Under Linux/macOS, ****** EOF --> Ctrl+D ******" << std::endl;
    std::cout << "Input some strings , End of EOF:\n" << std::endl;

    while (true)
    {
        std::cin >> str;

        //判断是否读取到EOF
        if (std::cin.eof()) break;

        //如果发生错误，处理后继续
        if (std::cin.fail())
        {
            std::cout << "Input ERROR,Try again!!!" << std::endl;
            //重置错误状态
            std::cin.clear();
            //清空缓冲区的错误输入并继续输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        strBuffer.push_back(str);

        //关键：偷窥缓冲区下一个字符
        //如果下一个字符是换行符，而且tempVec的最后一个元素不是代表换行符的 "&&Enter&&"
        //则在tmpVec中加入特殊字符串"&&Enter&&"，同时消除重复的换行符
        if (std::cin.peek() == '\n' &&  !strBuffer.empty() && strBuffer.back() != LineBreakFlag)
            strBuffer.push_back(LineBreakFlag);
    }
}

// 从cin读入数字和字符串，根据函数参数 v 的类型 T 判定存储方式
// T: 各种vector类型
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer)
{
    std::string vTypeString = "Type others";

    //将sbuffer（vector string）中的element，拷贝到目标 v （类型vector int)中
    //如果element不能转化为整型，直接抛弃
    if constexpr (std::is_same_v<T, std::vector<int>>) 
    {
        vTypeString = "std::vector<int>";
        for (auto s : sbuffer)
        {
            if (s != LineBreakFlag) //显式跳过标记换行
            {
                try{
                    v.push_back(std::stoi(s));
                }
                catch(const std::exception& e){
                    //std::cout << "Element is not interger. " << std::endl;
                }
            }
        }
        return;
    }

    if constexpr(std::is_same_v<T, std::vector<std::vector<int>>>) 
    {
        vTypeString = "std::vector<std::vector<int>>";
        std::cout << "v Type: " << vTypeString << std::endl;
        return;
    }

    //将sbuffer（vector string）中的element，拷贝到目标 v （类型vector string)中
    if constexpr(std::is_same_v<T, std::vector<std::string>>)
    {
        vTypeString = "std::vector<std::string>";
        for (auto s : sbuffer)
            if(s != LineBreakFlag)  v.push_back(s);
        return;
    }


    if constexpr(std::is_same_v<T, std::vector<std::vector<std::string>>>)
    {
        vTypeString = "std::vector<std::vector<std::string>>";
        std::cout << "v Type: " << vTypeString << std::endl;
        return;
    } 
}