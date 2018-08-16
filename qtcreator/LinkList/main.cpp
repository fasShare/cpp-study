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

// merge两个链表，递归方式
LinkNode *MergeRecursive(LinkNode *left, LinkNode *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->_data >= right->_data) {
        right->_next = MergeRecursive(right->_next, left);
        return right;
    } else {
        left->_next = MergeRecursive(left->_next, right);
        return left;
    }
}

// merge两个链表，遍历方式
LinkNode *MergeLinklist(LinkNode *left, LinkNode *right) {
    LinkNode *ret = nullptr, *cur = nullptr;

    while (left && right) {
        if (left->_data <= right->_data) {
            if (!cur) {
                cur = ret = left;
            } else {
                cur->_next = left;
                cur = cur->_next;
            }
            left = left->_next;

        } else {
            if (!cur) {
                cur = ret = right;
            } else {
                cur->_next = right;
                cur = cur->_next;
            }
            right = right->_next;
        }
    }

    if (left) {
        if (!cur) {
            ret = left;
        } else {
            cur->_next = left;
        }
    }

    if (right) {
        if (!cur) {
            ret = right;
        } else {
            cur->_next = right;
        }
    }

    return ret;
}

LinkNode* Clone(LinkNode* pHead) {
        if (!pHead) {
            return nullptr;
        }

        LinkNode* cur = pHead;
        LinkNode* ret = nullptr;
        while (cur) { // 拷贝cur
            // 分配失败直接抛异常
            LinkNode* node = new LinkNode(cur->_data);
            // 把node插入到cur后面
            node->_next = cur->_next;
            cur->_next = node;

            cur = node->_next;
        }

        // 拷贝random
        cur = pHead;
        while (cur) {  // cur不空，必有cur->next != nullptr
            LinkNode* cur_next = cur->_next;

            //if (cur->random) {
            //    cur_next->random = cur->random->next;
            //}

            cur = cur_next->_next;
        }

        // 分裂两个链表
        cur = pHead;
        LinkNode* ret_cur = nullptr;
        if (cur) {
            ret = cur->_next;
            ret_cur = ret;
        }

        while (cur && ret_cur) {
            cur->_next = ret_cur->_next;
            if (cur->_next) {
                ret_cur->_next = cur->_next->_next;
            }

            cur = cur->_next;
            ret_cur = ret_cur->_next;
        }

        return ret;
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

    std::cout << "after clone:" << std::endl;
    ShowLinklist(Clone(listleft));
    ShowLinklist(listleft);

    //ShowLinklist(MergeRecursive(listleft, listright));
    //ShowLinklist(MergeLinklist(listleft, listright));
    return 0;
}
