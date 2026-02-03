#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>
#include "wga.h"




////////////////////////////////////////////////////////////////////////////////
// 初始化一维和二维Vector
// InitVector_old: 未引入C++20 concepts，代码比较复杂、可读性差
// T: 一维和二维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector_old(T &v , const std::vector<std::string> &sbuffer);


int main()
{
    std::vector<int> vInt;                     //Integer vector,一维存储
    std::vector<std::vector<int>> matrixInt;   //Integer matrix,二维存储

    std::vector<float> vFloat;                     //float vector,一维存储
    std::vector<std::vector<float>> matrixFloat;   //float matrix,二维存储

    std::vector<double> vDouble;                     //double vector,一维存储
    std::vector<std::vector<double>> matrixDouble;   //double matrix,二维存储

    std::vector<std::string> vStr;                    //string vector,一维存储
    std::vector<std::vector<std::string>> matrixStr;  //string matrix,二维存储

    //从控制台读入一行或N行字符串，存在在strbuff中，用作初始化各类vector
    std::vector<std::string> strbuff;
    GetStrToVec(strbuff);

    for (auto const &elem : strbuff)
    {
        std::cout << elem << " ";
        if (elem == LineBreakFlag)
            std::cout << std::endl;
    }    

    //===================================================================================
    //=============以下使用InitVector_old函数，初始化一维和二维Vector=======================
    //===================================================================================
    std::cout << "=====================================================================================" << std::endl;
    std::cout << "=================== now use InitVector_old() to Init vector =========================" << std::endl;
    std::cout << "=====================================================================================" << std::endl;

    /*
    //初始化 vectorInt
    splitline();
    std::cout << "Display received TEXT AS Interger vector:" << std::endl;
    InitVector_old(vInt , strbuff);
    PrintVector(vInt);

    //初始化 vectorStr
    splitline();
    std::cout << "Display received TEXT AS string vector:" << std::endl;
    InitVector_old(vStr , strbuff);
    PrintVector(vStr);

    //初始化 matrixInt,形成二维Interger矩阵
    splitline();
    std::cout << "Display received TEXT AS Interger matrix:" << std::endl;
    InitVector_old(matrixInt , strbuff);
    PrintVector(matrixInt);

    //初始化 matrixStr,形成二维string矩阵
    splitline();
    std::cout << "Display received TEXT AS string matrix:" << std::endl;
    InitVector_old(matrixStr , strbuff);
    PrintVector(matrixStr);
    */


    //===================================================================================
    //=============以下使用InitVector函数，初始化一维和二维Vector=======================
    //===================================================================================
    std::cout << "=====================================================================================" << std::endl;
    std::cout << "=================== now use InitVector() to Init vector =========================" << std::endl;
    std::cout << "=====================================================================================" << std::endl;

    //初始化 vectorInt
    splitline();
    std::cout << "Display received TEXT AS Interger vector:" << std::endl;
    InitVector(vInt , strbuff);
    PrintVector(vInt);
    
    //初始化 vectorFloat
    splitline();
    std::cout << "Display received TEXT AS Float vector:" << std::endl;
    InitVector(vFloat , strbuff);
    PrintVector(vFloat);

    //初始化 vectorDouble
    splitline();
    std::cout << "Display received TEXT AS Double vector:" << std::endl;
    InitVector(vDouble , strbuff);
    PrintVector(vDouble);

    //初始化 vectorStr
    splitline();
    std::cout << "Display received TEXT AS string vector:" << std::endl;
    InitVector(vStr , strbuff);
    PrintVector(vStr);

    //初始化 matrixInt,形成二维Interger矩阵
    splitline();
    std::cout << "Display received TEXT AS Interger matrix:" << std::endl;
    InitVector(matrixInt , strbuff);
    PrintVector(matrixInt);

    //初始化 matrixInt,形成二维float矩阵
    splitline();
    std::cout << "Display received TEXT AS Float matrix:" << std::endl;
    InitVector(matrixFloat , strbuff);
    PrintVector(matrixFloat);

    //初始化 matrixInt,形成二维Double矩阵
    splitline();
    std::cout << "Display received TEXT AS Double matrix:" << std::endl;
    InitVector(matrixDouble , strbuff);
    PrintVector(matrixDouble);

    //初始化 matrixStr,形成二维string矩阵
    splitline();
    std::cout << "Display received TEXT AS string matrix:" << std::endl;
    InitVector(matrixStr , strbuff);
    PrintVector(matrixStr);
    
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  未使用 C++20 concepts 示例////////////////////////////////////////////////////
// 初始化一维和二维Vector
// 未引入C++20 concepts，代码比较复杂、可读性差
// T: 一维和二维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector_old(T &v , const std::vector<std::string> &sbuffer)
{
    std::string vTypeString = "Type others";

    v.clear();
    if constexpr (std::is_same_v<T, std::vector<int>>) 
    {
        //将sbuffer（vector string）中的element，拷贝到目标 v （类型vector int)中
        //如果element不能转化为整型，直接抛弃
        vTypeString = "std::vector<int>";
        for (auto &s : sbuffer)
        {
            if (s != LineBreakFlag) //显式跳过标记换行
            {
                try{
                    v.push_back(std::stoi(s));
                }
                catch(const std::exception& e){
                    std::cout << "Error: " << e.what() << '\n';
                }
            }
        }
    }
    else if constexpr(std::is_same_v<T, std::vector<std::vector<int>>>) 
    {
        //将sbuffer（vector string）中的element，拷贝到目标v （类型vector<vector<int>> )中        
        vTypeString = "std::vector<std::vector<int>>";
        std::vector<int> currentRow;

        for (auto &elem : sbuffer)
        {
            if((elem == LineBreakFlag) && (!currentRow.empty()))
            {
                v.push_back(currentRow);;
                currentRow.clear();
                continue;
            }
            try{
                currentRow.push_back(std::stoi(elem));
            }
            catch(const std::exception& e){
                    std::cout << "Error: " << e.what() << '\n';
            }
        }
    }
    else if constexpr(std::is_same_v<T, std::vector<std::string>>)
    {
        //将sbuffer（vector string）中的element，拷贝到目标 v （类型vector string)中        
        vTypeString = "std::vector<std::string>";
        for (auto &s : sbuffer)
            if(s != LineBreakFlag)  v.push_back(s);
    }
    else if constexpr(std::is_same_v<T, std::vector<std::vector<std::string>>>)
    {
        //将sbuffer（vector string）中的element，拷贝到目标v （类型vector<vector<int>> )中        
        vTypeString = "std::vector<std::vector<std::string>>";
        std::vector<std::string> currentRow;

        for (auto &elem : sbuffer)
        {
            if((elem == LineBreakFlag) && (!currentRow.empty()))
            {
                v.push_back(currentRow);;
                currentRow.clear();
                continue;
            }
            currentRow.push_back(elem);
        }
    } 
}

