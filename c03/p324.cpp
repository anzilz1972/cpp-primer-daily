#include <iostream>
#include <vector>
#include <string>
#include "wga.h"


int main()
{
    std::vector<std::string>  strBuff;
    std::vector<int> vInt;
    std::vector<int>::const_iterator it1,it2;

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

    //将Interger Vector中前后对称的两个元素相加，并打印
    splitline();
    it1 = vInt.cbegin();
    it2 = vInt.cend()-1;
    while (it1 <= it2)
    {
        if (it1 == it2){
            std::cout << "Lonely Element: " << *it1 << std::endl;
       }
       else{
            std::cout << *it1 << " Add " << *it2 
                 << " Equals: " << *it1 + *it2 <<std::endl;
       }
       it1++;
       it2--;
    }
    
    //将Interger Vector中前后衔接的两个元素相加，并打印
    splitline();
    it1 = vInt.cbegin();
    it2 = vInt.cbegin()+1;
    while (it2 != vInt.cend())
    {
        std::cout << *it1 << " Add " << *it2 
                 << " Equals: " << *it1 + *it2 <<std::endl;
        it1++;
        it2++;
        
    }
    std::cout << "Last Element:" << *it1 << std::endl;
    return 0;
}