#include <string>
#include <vector>
#include <iostream>

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
int64_t Abs(int64_t b) {
    return b < 0 ? -b : b;
}

// 返回两个数中的最大值
int64_t Max(int64_t left, int64_t right) {
    return left >= right ? left : right;
}

// 返回三个数中的最大值
int64_t MaxThree(int64_t mid, int64_t left, int64_t right) {
    return Max(mid, Max(left, right));
}

// 返回两个数中的最小值
int64_t Min(int64_t left, int64_t right) {
    return left <= right ? left : right;
}

// 从一行中读取一个数，在一个程序中使用getline时，最好使用这个函数来读取行数，不然会出现多于的换行
int GetIntFromLine() {
    std::string line;
    std::getline(std::cin, line);
    return std::atoi(line.c_str());
}

// 从cin中读取n行数据
std::vector<std::string> ReadNLineFromCin(int n) {
    std::vector<std::string> strs;
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        strs.push_back(line);
    }
    return strs;
}

// 先用sp中的任意一个字符去分割str，然后再把分割的每一个单元转化为int
std::vector<int> GetIntVectorFromStr(const std::string& str, const std::string& sp) {
    std::vector<int> ret;
    auto sps = StringSplit(str, sp);
    for (size_t ks = 0; ks < sps.size(); ++ks) {
        ret.push_back(std::atoi(sps[ks].c_str()));
    }
    return std::move(ret);
}

// 相当于处理多个字符串的GetIntVectorFromStr
std::vector<std::vector<int>> GetIntMatrixFromStrs(const std::vector<std::string> &strs, const std::string& sp) {
    std::vector<std::vector<int>> ret;
    ret.resize(strs.size());
    for (size_t i = 0; i < strs.size(); ++i) {
        auto sps = StringSplit(strs[i], sp);
        for (size_t ks = 0; ks < sps.size(); ++ks) {
            ret[i].push_back(std::atoi(sps[ks].c_str()));
        }
    }
    return std::move(ret);
}

// 从一行中读取N个整数，分隔符为sp里面的任意字符
std::vector<int> GetIntVectorFromCin(const std::string& sp) {
    auto str = ReadNLineFromCin(1);
    return GetIntVectorFromStr(str[0], sp);
}

// 相当于ReadNLineFromCin + GetIntMatrixFromStrs
std::vector<std::vector<int>> ReadMatrixFromCin(int n, const std::string& sp) {
    return GetIntMatrixFromStrs(ReadNLineFromCin(n), sp);
}
