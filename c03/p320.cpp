#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>
#include "wga.h"



// 打印一维和二维矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void PrintVector(T &v);


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




////////////////////////////////////////////////////////////////////////////////
// C++20 Concepts for type safety
template <typename T>
concept Vector1D = std::is_same_v<T, std::vector<int>> ||
                      std::is_same_v<T, std::vector<float>> ||
                      std::is_same_v<T, std::vector<double>> ||
                      std::is_same_v<T, std::vector<std::string>>; 

template <typename T>
concept Vector2D = std::is_same_v<T, std::vector<std::vector<int>>> ||
                      std::is_same_v<T, std::vector<std::vector<float>>> ||
                      std::is_same_v<T, std::vector<std::vector<double>>> || 
                      std::is_same_v<T, std::vector<std::vector<std::string>>> ;

//初始化一维和二维Vector
//InitVector_new：引入C++20 concepts，通过对模板函数的显示类型约束，简化代码实现，提高可读性
//T: 一维和二维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector_new(T &v , const std::vector<std::string> &sbuffer);

//初始化一维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector1D(T &v , const std::vector<std::string> &sbuffer);

//初始化二维Vector（Matrix）
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector2D(T &v , const std::vector<std::string> &sbuffer);


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
    //=============以下使用InitVector_new函数，初始化一维和二维Vector=======================
    //===================================================================================
    std::cout << "=====================================================================================" << std::endl;
    std::cout << "=================== now use InitVector_new() to Init vector =========================" << std::endl;
    std::cout << "=====================================================================================" << std::endl;

    //初始化 vectorInt
    splitline();
    std::cout << "Display received TEXT AS Interger vector:" << std::endl;
    InitVector_new(vInt , strbuff);
    PrintVector(vInt);
    
    //初始化 vectorFloat
    splitline();
    std::cout << "Display received TEXT AS Float vector:" << std::endl;
    InitVector_new(vFloat , strbuff);
    PrintVector(vFloat);

    //初始化 vectorDouble
    splitline();
    std::cout << "Display received TEXT AS Double vector:" << std::endl;
    InitVector_new(vDouble , strbuff);
    PrintVector(vDouble);

    //初始化 vectorStr
    splitline();
    std::cout << "Display received TEXT AS string vector:" << std::endl;
    InitVector_new(vStr , strbuff);
    PrintVector(vStr);

    //初始化 matrixInt,形成二维Interger矩阵
    splitline();
    std::cout << "Display received TEXT AS Interger matrix:" << std::endl;
    InitVector_new(matrixInt , strbuff);
    PrintVector(matrixInt);

    //初始化 matrixInt,形成二维float矩阵
    splitline();
    std::cout << "Display received TEXT AS Float matrix:" << std::endl;
    InitVector_new(matrixFloat , strbuff);
    PrintVector(matrixFloat);

    //初始化 matrixInt,形成二维Double矩阵
    splitline();
    std::cout << "Display received TEXT AS Double matrix:" << std::endl;
    InitVector_new(matrixDouble , strbuff);
    PrintVector(matrixDouble);

    //初始化 matrixStr,形成二维string矩阵
    splitline();
    std::cout << "Display received TEXT AS string matrix:" << std::endl;
    InitVector_new(matrixStr , strbuff);
    PrintVector(matrixStr);
    
    return 0;
}




// 打印一维和二维矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void PrintVector(T &v)
{
    if constexpr (Vector1D<T>)
    {
        for (const auto &elem : v)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
    else if constexpr (Vector2D<T>)
    {
        for (const auto &row : v)
        {
            for (const auto &elem : row)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
    }
}



////////////////////////////////  C++20 concepts 示例////////////////////////////////////////////////////
//初始化一维和二维Vector
//引入C++20 concepts，通过对模板函数的显示类型约束，简化代码实现，提高可读性
//
// T: 各种vector类型
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector_new(T &v , const std::vector<std::string> &sbuffer)
{
    if constexpr (Vector1D<T>)
    {
        //用sbuffer中存储的string,初始化一维vector v
        InitVector1D(v , sbuffer);
    }
    else if constexpr (Vector2D<T>)
    {
        //用sbuffer中存储的string,初始化二维vector v
        InitVector2D(v , sbuffer);
    }
    return;
}


//初始化一维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector1D(T &v , const std::vector<std::string> &sbuffer)
{
    using ElementType = typename T::value_type;
    //将sbuffer（vector string）中的element，拷贝到目标 v 中
    //如果element不是std::string，且不能转化为 T::value_type::value_type，直接抛弃
    v.clear();
    for (auto &elem : sbuffer)
    {
        if (elem == LineBreakFlag) continue; //跳过LineBreakFlag，继续处理下一个element
        if constexpr (std::is_same_v<ElementType, std::string>){
            //Vector的elem类型是string:直接添加
            v.push_back(elem);
        }
        else if constexpr (std::is_same_v<ElementType, int>){
            //Vector的elem是：interger
            try{
                v.push_back(std::stoi(elem));
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e .what() << std::endl;
            }
        }
        else if constexpr (std::is_same_v<ElementType, float>){
            //Vector的elem是：float
            try{
                v.push_back(std::stof(elem)); 
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e .what() << std::endl;
            }
        }
        else if constexpr (std::is_same_v<ElementType, double>){
            //Vector的elem是：double
            try{
                v.push_back(std::stod(elem)); 
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e .what() << std::endl;
            }
        }
    }
    return;
}

//初始化二维Vector（Matrix）
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector2D(T &v , const std::vector<std::string> &sbuffer)
{
    using RowType = typename T::value_type;
    using ElementType = typename RowType::value_type;
    RowType currentRow;
    
    v.clear();
    currentRow.clear();
    for (const auto& s : sbuffer)
    {
        //读到LineBreakFlag,将当前Vector追加到Matrix
        if (s == LineBreakFlag){
            if (!currentRow.empty()) 
            {
                v.push_back(currentRow);
                currentRow.clear();
            }
            continue;
        }

        //读到非LineBreakFlag,按照currentRow的元素类型进行处理
        if constexpr (std::is_same_v<ElementType, std::string>){
            //currentRow的元素类型为string：直接追加到currentRow
            currentRow.push_back(s);
        }
        else if constexpr(std::is_same_v<ElementType, int>){
            //currentRow的元素类型为int：转换后追加到currentRow
            try{
                currentRow.push_back(std::stoi(s));
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e.what() << '\n';
            }
        }
        else if constexpr(std::is_same_v<ElementType, float>){
            //currentRow的元素类型为float：转换后追加到currentRow
            try{
                currentRow.push_back(std::stof(s));
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e.what() << '\n';
            }
        }
        else if constexpr(std::is_same_v<ElementType, double>){
            //currentRow的元素类型为double：转换后追加到currentRow
            try{
                currentRow.push_back(std::stod(s));
            }
            catch(const std::exception& e){
                //std::cout << "Error: " <<e.what() << '\n';
            }
        }
    }

    //当前currentRow可能未追加到Matrix中，完成追加
    if (!currentRow.empty()) v.push_back(currentRow);
    return;
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

