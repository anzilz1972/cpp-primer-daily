#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>
#include "wga.h"  // Temporarily commented for testing

// Temporary splitline function for testing
/*
void splitline() {
    std::cout << "----------------------------------------" << std::endl;
}
*/



//用cin.peek()检测到输入流中的换行符时，在vector中加入一串特殊字符做标记
//之所以记录换行符，主要是为了将内容区分存放在 vector 和 matrix
//vector 包括：std::vector<int>> 、 std::vector<double>、std::vector<std::string>> 等...
//matrix 包括：std::vector<std::vector<int>>  、 std::vector<std::vector<double>>、std::vector<std::vector<std::string>> 等...
const std::string  LineBreakFlag = "&&LineBreak&&";

// C++20 Concepts for type safety
template<typename T>
concept Vector1D = std::is_same_v<T, std::vector<int>> || 
                   std::is_same_v<T, std::vector<float>> ||
                   std::is_same_v<T, std::vector<double>> ||
                   std::is_same_v<T, std::vector<std::string>>;

template<typename T>
concept Vector2D = std::is_same_v<T, std::vector<std::vector<int>>> || 
                   std::is_same_v<T, std::vector<std::vector<float>>> || 
                   std::is_same_v<T, std::vector<std::vector<double>>> || 
                   std::is_same_v<T, std::vector<std::vector<std::string>>>;



// Helper functions for optimized processing
template<typename T>
    constexpr bool shouldSkipElement(const std::string& s) 
{
    return s == LineBreakFlag;
}

// 从cin读入数字和字符串，存储在strVec中
void getStr(std::vector<std::string> &strBuffer);


// 转换字符串为INT类型，并安全地向 Vector1D<int> 全添加元素
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template<typename T>
    void safeConvertAndAdd(T& vec, const std::string& s);

// 构造 Vector2D<T> 矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template<typename T>
    void buildMatrix(T& matrix, const std::vector<std::string>& buffer);

// 构造一维和二维矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer);

// 打印一维和二维矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void PrintVector(T &v);


int main()
{
    std::vector<int> vInt;                     //Integer vector,一维存储
    std::vector<std::vector<int>> matrixInt;   //Integer matrix,二维存储
    std::vector<std::string> vStr;                    //string vector,一维存储
    std::vector<std::vector<std::string>> matrixStr;  //string matrix,二维存储

    //从控制台读入一行或N行字符串，存在在strbuff中，用作初始化各类vector
    std::vector<std::string> strbuff;
    getStr(strbuff);


    //初始化 vector Int
    InitVector(vInt , strbuff);
    //打印 vector Int
    splitline();
    std::cout << "Display received TEXT AS Interger vector:" << std::endl;
    PrintVector(vInt);
    

    //初始化 matrixInt,形成二维Interger矩阵
    InitVector(matrixInt , strbuff);
    //打印matrix Int
    splitline();
    std::cout << "Display received TEXT AS Interger matrix:" << std::endl;
    PrintVector(matrixInt);


    //初始化 vector String
    InitVector(vStr , strbuff);
    //打印 vector string
    splitline();
    std::cout << "Display received TEXT AS string vector:" << std::endl;
    PrintVector(vStr);

    //初始化 matrixStr,形成二维string矩阵
    InitVector(matrixStr , strbuff);
    // 打印matrix string
    splitline();
    std::cout << "Display received TEXT AS string matrix:" << std::endl;
    PrintVector(matrixStr);

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
    std::cout << "Input some strings , End of EOF:" << std::endl;

    // Simplified input loop with better error handling
    while (std::cin >> str) 
    {
        strBuffer.push_back(str);
        
        // Check for newline and add break flag
        if (std::cin.peek() == '\n' && !strBuffer.empty() && strBuffer.back() != LineBreakFlag) 
        {
            strBuffer.push_back(LineBreakFlag);
            std::cin.get(); // Consume the newline
        }
    }
    
    // Handle error state if needed
    if (std::cin.bad()) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


// 转换字符串为INT类型，并安全地向 Vector1D<int> 全添加元素
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template<typename T>
    void safeConvertAndAdd(T& vec, const std::string& s) 
{
    try {
        if constexpr (std::is_same_v<T, std::vector<int>>) {
            vec.push_back(std::stoi(s));
        }
    } catch (const std::invalid_argument&) {
        // Silently ignore invalid arguments
    } catch (const std::out_of_range&) {
        // Silently ignore out of range values
    }
}

// 构造 Vector2D<T> 矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template<typename T>
    void buildMatrix(T& matrix, const std::vector<std::string>& buffer)
{
    using RowType = typename T::value_type;
    using ElementType = typename RowType::value_type;
    
    RowType currentRow;
    
    for (const auto& s : buffer) 
    {
        if (s == LineBreakFlag) 
        {
            if (!currentRow.empty()) 
            {
                matrix.push_back(currentRow);
                currentRow.clear();
            }
        }
        else 
        {
            if constexpr (std::is_same_v<ElementType, int>) 
            {
                try {
                    currentRow.push_back(std::stoi(s));
                } catch (...) {
                    // Ignore conversion failures for matrix elements
                }
            } 
            else 
            {
                currentRow.push_back(s);
            }
        }
    }
    // Add the last row if it has elements
    if (!currentRow.empty()) {
        matrix.push_back(currentRow);
    }
}

// 构造一维和二维矩阵
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer)
{
    if constexpr (Vector1D<T>) 
    {
        // Handle 1D vectors
        for (const auto& s : sbuffer) 
        {
            if (!shouldSkipElement<T>(s)) 
            {
                if constexpr (std::is_same_v<T, std::vector<int>>) 
                {
                    safeConvertAndAdd(v, s);
                } else {
                    v.push_back(s);
                }
            }
        }
    } 
    else if constexpr (Vector2D<T>) 
    {
        buildMatrix(v, sbuffer);
    }
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
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    else if constexpr (Vector2D<T>)
    {
        for (const auto &row : v)
        {
            for (const auto &elem : row)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
}

