#ifndef TOOLS_H
#define TOOLS_H

// 根据d字符串中提供的字符分割字符串
std::vector<std::string> StringSplit(const std::string& str, const std::string& d);

// 判断字符ch是否是一个数字
bool IsDigit(char ch) ;

// 判断字符ch是否是一个正负号
bool IsSign(char ch);

// 判断该字符是否可以转化为有符号整形
bool IsIntStr(const std::string& str);

// 求b的绝对值
int Abs(int b);
#endif // TOOLS_H
