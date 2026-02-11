#include <iostream>
#include <string>
#include <vector>
#include "wga.h"

int main()
{
    std::vector<std::string> strBuff;
    std::vector<int> vInt;

    //Input anything include number or string,then put them in vector string
    wga::GetStrToVec(strBuff);
    //Print those strings
    //PrintVector(strBuff);
    //splitline();

    //Conver those strings into a Integer Vector
    //if any string can't be converted,pass it
    wga::InitVector(vInt,strBuff) ;
    //Print Integer Vector
    wga::PrintVector(vInt);
    wga::splitline();


    //获取Integer Vector成员数量
    for (auto &elem : vInt)  elem *= 2;    
    wga::PrintVector(vInt);
    return 0;
}