#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
#include <map>
#include <queue>
#include <stack>

/*
整体思想:
中缀表达式转换前缀表达式的操作过程为：
    首先设定一个操作符栈，从右到左顺序扫描整个中缀表达式，如果是操作数，则直接归入前缀表达式；如果是操作符，则检测器是否是右括号，如果是右括号，则直接将其入栈；如果是左括号，则将栈中的操作符依次弹栈，归入前缀表达式，直至遇到右括号，将右括号弹栈，处理结束；如果是其他操作符，则检测栈顶操作符的优先级与当前操作符的优先级关系，如果栈顶操作符优先级大于当前操作符的优先级，则弹栈，并归入前缀表达式，直至栈顶操作符优先级小于等于当前操作符优先级，这时将当前操作符压栈。
    当扫描完毕整个中缀表达式后，检测操作符栈是否为空，如果不为空，则依次将栈中操作符弹栈，归入前缀表达式。最后，将前缀表达式翻转，得到中缀表达式对应的前缀表达式。

中缀表达式转换为其对应的后缀表达式
    设置一个操作符栈，如果遇到操作数，则直接将操作数放进后缀表达式中，如果遇到非操作数，则：如果是左括号，则将左括号入栈；如果是右括号，则从操作符栈中将操作符弹栈，放入后缀表达式中，直至栈空或遇到栈中的左括号，并将左括号弹栈；如果是其他操作符，则比较其优先级与栈中操作符优先级情况，如果栈中的操作符的优先级大于等于当前操作符，则将栈中操作符弹栈，直至栈空，或栈中操作符优先级小于当前操作符的优先级，将当前操作符压栈。当从左到右顺序扫描完整个中缀表达式后，检测操作符栈，如果非空，则依次弹栈，将弹出的操作符依次压入到后缀表达式中。最终，得到中缀表达式对应的后缀表达式。
*/

class ExpressionEvaluator
{
public:
    // 通过中序表达式构造对象，只能计算一位数
    ExpressionEvaluator(const std::string& expr);
    // 输出后续表达式
    std::queue<char> GetPostOrderExpr() const;
    // 输出前序表达式
    std::stack<char> GetPreOrderExpr() const;
private:

    bool isNumber(char ch) const {
        return ch >= '0' && ch <= '9';
    }

    bool isLeftBracket(char expr) const {
        return expr == '(';
    }

    bool isRightBracket(char expr) const {
        return expr == ')';
    }

    bool isOperator(char expr)  const {
        return _kOperatorMap.find(expr) != _kOperatorMap.end() && !isLeftBracket(expr) && !isRightBracket(expr);
    }

private:
    static const std::map<char, int> _kOperatorMap;
    std::string _expr;
};

#endif // EXPRESSIONEVALUATOR_H
