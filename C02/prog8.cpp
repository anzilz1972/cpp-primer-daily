#include <iostream>
#include <string>
#include "wga.h"
using namespace std;
int main()
{
    string astr = "", bstr;

    cout << "Input a string that include some  punctuation characters below:" << endl;
    getline(cin , bstr);

    for (auto ch : bstr) if(!ispunct(ch)) astr += ch;
    cout << astr << endl;

    return 0;
}