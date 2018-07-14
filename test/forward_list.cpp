#include <forward_list>
#include <iostream>

int main () {
    std::forward_list<int> ilist;

    ilist.push_front(1);
    ilist.push_front(2);
    ilist.push_front(3);
    ilist.push_front(4);
    ilist.push_front(5);
    // no size method
    std::cout << "size:" << ilist.size() << std::endl;

    for (auto value : ilist) {
        std::cout << value << std::endl;
    }
}
