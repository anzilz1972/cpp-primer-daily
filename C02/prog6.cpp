#include <iostream>
#include <string>
#include "wga.h"
using namespace std;

int main()
{
    string sentence,word;
    string str1,str2;
    char c;
    
    /*********
    cout << "Input a sentence:" << endl;
    getline(cin, sentence);
    cout << sentence << endl;
    splitline();

    cout << "Input a sentence again:" << endl;
    cin >> word;
    cout << word << ' ';
    splitline();

    cout << "Input two strings\nFirst:" << endl;
    getline(cin , str1);
    cout << "Second:" << endl;
    getline(cin , str2);
    cout << ((str1 >= str2) ? str1 : str2) << endl;
    cout << ((str1.length() >= str2.length()) ? str1 : str2) << endl;
    splitline();
    *********/

    cout << "Input some word:" << endl;
    word = "";
    sentence = "";
    while (cin.get(c)) 
    {
        if (c == ' ')  
        {
            sentence += word;
            word = "";
        }
        
        if (c == '\n')
        {
            sentence += word;
            break;
        }
        word += c;
    }
    cout << endl << sentence << endl;
    splitline();
    return 0;
}