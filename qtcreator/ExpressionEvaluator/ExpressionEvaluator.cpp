#include <stack>
#include <assert.h>
#include <iostream>

#include "ExpressionEvaluator.h"

const std::map<char, int> ExpressionEvaluator::_kOperatorMap = {
    {'(', 0},
    {')', 0},
    {'-', 1},
    {'+', 1},
    {'/', 2},
    {'*', 2},
};

ExpressionEvaluator::ExpressionEvaluator(const std::string& expr) :
    _expr(expr) { }

// 输出后续表达式
std::queue<char> ExpressionEvaluator::GetPostOrderExpr() const {
    std::queue<char> postOrder;
    // 正常情况下在往ops里面放入运算符时应该检查该运算符在OperatorMap中是否存在，可能会导致_kOperatorMap.at方法抛出std::out_of_range，
    // 这里假设不会出现不存在的问题
    std::stack<char> ops;
    // 后序表达式从前向后遍历中序字符串
    for (std::string::size_type index = 0; index < _expr.size(); ++index) {
        if (isNumber(_expr[index])) {
            postOrder.push(_expr[index]);
        } else if (isLeftBracket(_expr[index])) {
            ops.push(_expr[index]);
        } else if (isOperator(_expr[index])) {
            // 如果当前运算符大于栈顶元素，当前运算符直接入栈，否则，弹出栈顶运算符到后续遍历序列，直到栈顶运算符优先级小于当前运算符
            while (!ops.empty() && _kOperatorMap.at(_expr[index]) <= _kOperatorMap.at(ops.top())) {
                postOrder.push(ops.top());
                ops.pop();
            }
            ops.push(_expr[index]);
        } else if (isRightBracket(_expr[index])) {
            // 如果当前元素是右括号，弹出栈内元素，直到遇到左括号
            while (!ops.empty() && !isLeftBracket(ops.top())) {
                postOrder.push(ops.top());
                ops.pop();
            }
            // 弹出左括号
            if (!ops.empty() && isLeftBracket(ops.top())) {
                ops.pop();
            }
        } else {
            assert(false);
        }
    }

    while (!ops.empty()) {
        postOrder.push(ops.top());
        ops.pop();
    }

    return postOrder;
}
// 输出前序表达式
std::stack<char> ExpressionEvaluator::GetPreOrderExpr() const {
    std::stack<char> preOrder;
    // 正常情况下在往ops里面放入运算符时应该检查该运算符在OperatorMap中是否存在，可能会导致_kOperatorMap.at方法抛出std::out_of_range，
    // 这里假设不会出现不存在的问题
    std::stack<char> ops;

    if (_expr.size() == 0) {
        return preOrder;
    }

    // 前序表达式从前向后遍历中序字符串
    for (int index = _expr.size() - 1; index >= 0; --index) {
        if (isNumber(_expr[index])) {
            preOrder.push(_expr[index]);
        } else if (isRightBracket(_expr[index])) {
            ops.push(_expr[index]);
        } else if (isOperator(_expr[index])) {
            // 如果当前运算符大于栈顶元素，当前运算符直接入栈，否则，弹出栈顶运算符到后续遍历序列，直到栈顶运算符优先级小于当前运算符
            while (!ops.empty() && _kOperatorMap.at(_expr[index]) <= _kOperatorMap.at(ops.top())) {
                preOrder.push(ops.top());
                ops.pop();
            }
            ops.push(_expr[index]);
        } else if (isLeftBracket(_expr[index])) {
            // 如果当前元素是右括号，弹出栈内元素，直到遇到左括号
            while (!ops.empty() && !isRightBracket(ops.top())) {
                preOrder.push(ops.top());
                ops.pop();
            }
            // 弹出左括号
            if (!ops.empty() && isRightBracket(ops.top())) {
                ops.pop();
            }
        } else {
            assert(false);
        }
    }

    while (!ops.empty()) {
        preOrder.push(ops.top());
        ops.pop();
    }

    return preOrder;
}

