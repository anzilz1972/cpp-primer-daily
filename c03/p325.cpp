#include <iostream>
#include <string>
#include <vector>
#include "wga.h"

int main()
{
    std::vector<std::string> strBuff; 
    std::vector<int> grade;         
    std::vector<unsigned> scores(11,0);  //分数段统计，初始值都为0
    std::vector<unsigned>::iterator it;

    //从cin读入字符串,缓存在strBuff
    GetStrToVec(strBuff);

    //将字符串转换为分数后进行存储
    InitVector(grade,strBuff);

    //用scores统计不同分数段
    for (auto &gd : grade)
    {
        it = scores.begin()+ gd/10;
        (*it) = (*it) + 1;
    }


    int idx = 0;
    do
    {
        //输出99分以下的统计结果
        std::cout << "[" << idx * 10 << "] To [" << idx * 10 + 9 << "]: "
            << scores[idx] << std::endl;            
    } while (++idx < scores.size()-1);

    //单独输出100分的统计结果
    std::cout << "[" << idx * 10 << "]: " << scores[idx] << std::endl;            
    return 0;
}