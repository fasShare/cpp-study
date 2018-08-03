#include <iostream>
#include <vector>

struct LinkNode {
    int _data;
    struct LinkNode *_next;
    LinkNode(int data) :
        _data(data), _next(nullptr) {}
};

// 头插法
bool InsertNode(LinkNode * &list, int data) {
    if (!list) { // 第一个节点
        list = new LinkNode(data);
        if (!list) {
            return false;
        }
    } else {
        LinkNode *node = new LinkNode(data);
        if (!node) {
            return false;
        }
        node->_next = list;
        list = node;
    }

    return true;
}

void ShowLinklist(LinkNode *list) {
    std::cout << "[ ";
    while (list) {
        std::cout << list->_data << " ";
        list = list->_next;
    }
    std::cout << "]" << std::endl;
}

// 逆序打印链表
static void __ShowLinklistReverse(LinkNode *list) {
    if (!list) {
        return;
    }
    __ShowLinklistReverse(list->_next);
    std::cout << list->_data << " ";
}

void ShowLinklistReverse(LinkNode *list) {
    std::cout << "[ ";
    __ShowLinklistReverse(list);
    std::cout << "]" << std::endl;
}

// 1 -> 2 -> 3
// pr   cur  next
// 翻转链表
void ReverseLinklist(LinkNode * &list) {
    if (!list) {
        return;
    }

    LinkNode *prev = nullptr, *cur = list, *next = nullptr;
    while (cur) {
        next = cur->_next;
        cur->_next = prev;
        prev = cur;
        cur = next;
    }

    list = prev;
}

int main()
{
    LinkNode *listleft = nullptr;

    for (int i = 1; i < 10; i += 2) {
        InsertNode(listleft, i);
    }
    LinkNode *listright = nullptr;

    for (int i = 2; i <= 10; i += 2) {
        InsertNode(listright, i);
    }

    ShowLinklist(listleft);
    ShowLinklist(listright);

    ReverseLinklist(listleft);
    ReverseLinklist(listright);

    ShowLinklist(listleft);
    ShowLinklist(listright);
    return 0;
}
