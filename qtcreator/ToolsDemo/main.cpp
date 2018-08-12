#include <iostream>

#include "tools.h"
#include "topn.h"

using namespace std;

int main()
{
    vector<vector<int>> result;

    int N =  GetIntFromLine();

    result = ReadMatrixFromCin(N, ", ");

    std::cout << "--------------------------" << std::endl;

    PrintMatrix(result);

    return 0;
}
