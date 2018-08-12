#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <vector>
// 根据d字符串中提供的字符分割字符串
std::vector<std::string> StringSplit(const std::string& str, const std::string& d);

// 判断字符ch是否是一个数字
bool IsDigit(char ch) ;

// 判断字符ch是否是一个正负号
bool IsSign(char ch);

// 判断该字符是否可以转化为有符号整形
bool IsIntStr(const std::string& str);

// 求b的绝对值
int64_t Abs(int64_t b);

// 返回两个数中的最大值
int64_t Max(int64_t left, int64_t right);

// 返回两个数中的最小值
int64_t Min(int64_t left, int64_t right);

// 返回三个数中的最大值
int64_t MaxThree(int64_t mid, int64_t left, int64_t right);

// 从标准输入读入N个空格或者换行分割的相同类型的元素，通过数组返回。
template <typename T>
std::vector<T> ReadNFromCin(size_t n) {
    std::vector<T> ret;
    if (n == 0) {
        return ret;
    }
    ret.resize(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> ret[i];
    }
    return ret;
}

// 在一行里面空格分隔打印数组
template<class T>
void PrintVector(const std::vector<T>& vec) {
    for (const auto &val:vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// 在多行里面空格分隔打印矩阵
template<class T>
void PrintMatrix(const std::vector<std::vector<T>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        PrintVector(vec[i]);
    }
    std::cout << std::endl;
}

// 从cin中读取n行数据
std::vector<std::string> ReadNLineFromCin(int n);

// 先用sp中的任意一个字符去分割str，然后再把分割的每一个单元转化为int
std::vector<int> GetIntVectorFromStr(const std::string& str, const std::string& sp);

// 相当于处理多个字符串的GetIntVectorFromStr
std::vector<std::vector<int>> GetIntMatrixFromStrs(const std::vector<std::string> &strs, const std::string& sp);

// 相当于ReadNLineFromCin + GetIntMatrixFromStrs
std::vector<std::vector<int>> ReadMatrixFromCin(int n, const std::string& sp);

// 从一行中读取N个整数，分隔符为sp里面的任意字符
std::vector<int> GetIntVectorFromCin(const std::string& sp);

// 从一行中读取一个数，在一个程序中使用getline时，最好使用这个函数来读取行数，不然会出现多于的换行
int GetIntFromLine();

#endif // TOOLS_H
