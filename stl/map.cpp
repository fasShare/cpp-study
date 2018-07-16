/*************************************************************************
    > File Name: map.cpp
    > Author: fas
    > Created Time: 2018年07月16日 星期一 16时36分22秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <string>

int main(int argc, char** atgv) {
    std::map<int, std::string> ms;

    ms[1] = "shang";
    ms[3] = "xiao";
    ms[2] = "fei";
    ms[4] = "nuo";
    ms[5] = "900";
    ms[7] = "@";
    ms[9] = "163.com";

    auto lower_iter = ms.lower_bound(4);
    for (auto iter = lower_iter; iter != ms.end(); ++iter) {
        std::cout << "key:" << iter->first << " value:" << iter->second << std::endl;
    }

    return 0;
}
