#include <iostream>
#include <string>
#include <vector>
#include "wga.h"


int main()
{
    std::vector<std::string> strBuff;
    std::vector<int> vInt;

    //Input anything include number or string,then put them in vector string
    GetStrToVec(strBuff);
    //Print those strings
    //PrintVector(strBuff);
    //splitline();

    //Conver those strings into a Integer Vector
    //if any string can't be converted,pass it
    InitVector(vInt,strBuff) ;
    //Print Integer Vector
    //PrintVector(vInt);
    //splitline();


    //获取Integer Vector成员数量
    std::vector<int>::size_type  elemNums = vInt.size();
    //std::cout << "Elements: " << elemNums << std::endl;

    //将Interger Vector中前后对称的两个元素相加，并打印
    int idx1 = 0 , idx2 = elemNums-1;
    while (idx1 <= idx2 && elemNums >0)
    {
        if (idx1 == idx2){
                std::cout << "Element[" << idx1 << "] = " << vInt[idx1] << std::endl;
        }
        else{
                std::cout << "Element[" << idx1 << "] + Element[" << idx2 << "] = "
                            << vInt[idx1] + vInt[idx2] << std::endl;
        }
        idx1++;
        idx2--;
    }
    splitline();

    //将Interger Vector中前后衔接的两个元素相加，并打印
    idx1 = 0;
    while (idx1 <= elemNums-1 )
    {
        if (idx1 == elemNums-1){
                std::cout << "Element[" << idx1 << "] = " << vInt[idx1] << std::endl;
        }
        else{
                std::cout << "Element[" << idx1 << "] + Element[" << idx1+1 << "] = "
                            << vInt[idx1] + vInt[idx1+1] << std::endl;
        }
        idx1++;
    }
    splitline();
}
