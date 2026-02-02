#ifndef WGA_H
#define WGA_H

#include <iostream>
#include <typeinfo>

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

