#ifndef WGA_H
#define WGA_H

#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//用cin.peek()检测到输入流中的换行符时，在vector中加入一串特殊字符做标记
//之所以记录换行符，主要是为了将内容区分存放在一维vector 和 二维Vector（matrix）中
const std::string  LineBreakFlag = "&&LineBreak&&";


////////////////////////////////////////////////////////////////////////////////
//C++20 Concepts for type safety
//一维vector 包括：std::vector<int>> 、 std::vector<float>> 、std::vector<double>、std::vector<std::string>> ...
template <typename T>
concept Vector1D = std::is_same_v<T, std::vector<int>> ||
                      std::is_same_v<T, std::vector<float>> ||
                      std::is_same_v<T, std::vector<double>> ||
                      std::is_same_v<T, std::vector<std::string>>; 

//二维matrix 包括：std::vector<std::vector<int>>  、 std::vector<std::vector<float>>、
//                std::vector<std::vector<double>>、std::vector<std::vector<std::string>> ...
template <typename T>
concept Vector2D = std::is_same_v<T, std::vector<std::vector<int>>> ||
                      std::is_same_v<T, std::vector<std::vector<float>>> ||
                      std::is_same_v<T, std::vector<std::vector<double>>> || 
                      std::is_same_v<T, std::vector<std::vector<std::string>>> ;

//初始化一维和二维Vectord总入口
//InitVector：引入C++20 concepts，通过对模板函数的显示类型约束，简化代码实现，提高可读性
//T: 一维和二维Vector
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer);

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

// 打印一维和二维Vector
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T>
    void PrintVector(T &v);


////////////////////////////////  C++20 concepts 示例////////////////////////////////////////////////////
//初始化一维和二维Vector总入口
//引入C++20 concepts，通过对模板函数的显示类型约束，简化代码实现，提高可读性
//
// T: 各种vector类型
/**
 * @brief 
 * @details 
 */
template <typename T>
    void InitVector(T &v , const std::vector<std::string> &sbuffer)
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




// 从cin读入一行或多行字符串，分解成一个个单词后，存储在strVec中
// 两行相邻的单词之间，在strBuffer中插入 "&&Enter&&" 作为 “换行” 标记
void GetStrToVec(std::vector<std::string> &strBuffer)
{
    std::string str;

    //输入多个字符串，以EOF结束
    //Windows     环境下，EOF是--> "Ctrl+Z"
    //Linux/macOS 环境下，EOF是--> "Ctrl+D"
    std::cout << " Under windows,     ****** EOF --> Ctrl+Z ******" << std::endl;
    std::cout << " Under Linux/macOS, ****** EOF --> Ctrl+D ******" << std::endl;
    std::cout << "Input some strings , End of EOF:" << std::endl;

    while (std::cin >> str)
    {
        strBuffer.push_back(str);

        //关键：偷窥缓冲区下一个字符
        //如果下一个字符是换行符，而且tempVec的最后一个元素不是代表换行符的 "&&Enter&&"
        //则在tmpVec中加入特殊字符串"&&Enter&&"，同时消除重复的换行符
        if (std::cin.peek() == '\n' &&  !strBuffer.empty() && strBuffer.back() != LineBreakFlag)
        {
            strBuffer.push_back(LineBreakFlag);
            std::cin.get(); //消费掉换行符
        }    
        
        //如果发生错误，处理后继续
        if (std::cin.bad())
        {
            std::cout << "Input ERROR,Try again!!!" << std::endl;
            //重置错误状态
            std::cin.clear();
            //清空缓冲区的错误输入并继续输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
}


////////////////////////////////////////////////////////////////////////
/////////////////////////////画一条可爱的分割线//////////////////////////
void splitline()
{
    std::cout << std::endl << "------------------------------------------------------" << std::endl;
    return;
}

////////////////////////////////////////////////////////////////////////
//使用万能引用 T&& ,推导参数类型
template <typename T>
void printType(T&& value) //万能引用 Universal Reference
{
    // 推导参数类型（支持左值/右值）
    std::cout << typeid(decltype(value)).name() << std::endl;
}

#endif

