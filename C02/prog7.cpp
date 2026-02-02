#include <iostream>
#include <string>
#include "wga.h"
using namespace std;

int main()
{

    string astr("jadeblack@WGAMateBookPro:/mnt/f/DevCpp/CppPrimer/C02$");
    string str = astr;

    // for range Statement
    cout << str << endl;
    for (auto &ch : str) ch = 'X';
    cout << str << endl;
    splitline();

    //for loop statement
    str = astr;
    cout << str << endl;
    for (decltype(str.size()) index = 0; index < str.size(); index++)
        str[index] = 'X';
    cout << str << endl;
    splitline();

    //while loop statement
    str = astr;
    decltype(str.size()) index = 0;
    cout << str << endl;
    while ( index < str.size())
        str[index++] = 'X';
    cout << str << endl;
    splitline();


    return 0;
}