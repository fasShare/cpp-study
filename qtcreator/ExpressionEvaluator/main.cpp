#include <iostream>
#include <queue>

#include "ExpressionEvaluator.h"

int main()
{
    ExpressionEvaluator expr("1+(2-3/4)*5");

    std::queue<char> opq = expr.GetPostOrderExpr();

    while (!opq.empty()) {
        std::cout << opq.front();
        opq.pop();
    }

    std::cout << std::endl << "------------------------" << std::endl;

    std::stack<char> pre = expr.GetPreOrderExpr();
    while (!pre.empty()) {
        std::cout << pre.top();
        pre.pop();
    }

    std::cout << std::endl;

    return 0;
}
