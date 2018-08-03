#include <string>
#include <vector>

// 根据d字符串中提供的字符分割字符串
std::vector<std::string> StringSplit(const std::string& str, const std::string& d) {
    std::string::size_type pos = 0;
    std::vector<std::string> ret;
    while (pos < str.size() && pos != std::string::npos) {
        std::string::size_type start = str.find_first_not_of(d, pos);
        if (start == std::string::npos) {
            break;
        }
        pos = start;
        std::string::size_type end = str.find_first_of(d, pos);
        if (end == std::string::npos) {
            end = str.size();
        }
        pos = end;

        ret.push_back(str.substr(start, end - start));
    }

    return ret;
}

// 判断字符ch是否是一个数字
bool IsDigit(char ch) {
    return '0' <= ch && ch <= '9' ? true : false;
}

// 判断字符ch是否是一个正负号
bool IsSign(char ch) {
    return ch == '-' || ch == '+' ? true : false;
}

// 判断该字符是否可以转化为有符号整形
bool IsIntStr(const std::string& str) {
    for (std::string::size_type index = 0; index < str.size(); ++index) {
        if (IsDigit(str[index]) || (!IsDigit(str[index]) && IsSign(str[index]) && index == 0)) {
            continue;
        }
        return false;
    }
    return true;
}

// 求b的绝对值
int Abs(int b) {
    return b < 0 ? -b : b;
}
