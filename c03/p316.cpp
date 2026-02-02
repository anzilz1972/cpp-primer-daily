#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <typeinfo>
#include <type_traits>
#include "wga.h"

// 显示对象的类型、容量和成员
/**
 * @brief 显示对象的类型、容量和成员
 * @details 
 */
template <typename T> 
    void PrintInfo(const T &v ,const std::string vname);

int main()
{

    std::vector<int> v1,v2(10),v3(10,42),v4{10},v5{10,42};
    std::vector<std::string> sv6(10),sv7{"10","hi"};
    std::array<int,5> arrInt = {1,2,3,4,5};

    PrintInfo(v1,"v1");
    PrintInfo(v2,"v2");
    PrintInfo(v3,"v3");
    PrintInfo(v4,"v4");
    PrintInfo(v5,"v5");

    PrintInfo(sv6,"sv6");
    PrintInfo(sv7,"sv7");

    PrintInfo(arrInt,"arrInt");

    return 0;
}





// 显示对象的类型、容量和成员
template <typename T> 
    void PrintInfo(const T &v ,const std::string vname)
{
    std::string vTypeString = "Type others";
    if (std::is_same<T, std::vector<int>>::value) vTypeString = "vector<int>";
    if (std::is_same<T, std::vector<std::string>>::value) vTypeString = "vector<string>";
    if (std::is_same<T, std::array<int,5>>::value) vTypeString = "array<int,5>";
    
    std::cout << vname << std::endl 
        << "Type: " << vTypeString << std::endl;
    
    if (v.size() < 1) 
    {
        std::cout << "Size:" << v.size() << "   No elements.";
        splitline();
        return;
    }

    std::cout << "Size:" << v.size() << "    Elements:";
    for (auto const &i : v) 
        std::cout << i << " ";
    splitline();
    return;
}




