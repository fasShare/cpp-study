#ifndef TOPN_H
#define TOPN_H
#include <algorithm>
#include <queue>
#include <functional>

template <typename T, size_t N, typename Compare = std::greater<T>>
class TopNHeap {
public:
    const T& top() {
        return _heap.top();
    }
    void push(const T& e) {
        if (_size == 0) {
            return;
        }
        if (_heap.size() >= _size) {
            if (cmp(e, _heap.top())) {
                _heap.pop();
                _heap.push(e);
            }
        } else {
            _heap.push(e);
        }
    }

    void pop() {
        _heap.pop();
    }

    bool empty() {
        return _heap.empty();
    }

    size_t size() {
        return _heap.size();
    }

    void BuildFromVector(const std::vector<T>& vec) {
        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
            this->push(*iter);
        }
    }

private:
    Compare cmp;
    const size_t _size = N;
    std::priority_queue<T, std::deque<T>, Compare> _heap;
};

// 保存前Top N个最大数
template <typename T, size_t N>
using BigTopNHeap = TopNHeap<T, N, std::greater<T>>;
// 保存前Top N个最小数
template <typename T, size_t N>
using SmallTopNHeap = TopNHeap<T, N, std::less<T>>;

#endif // TOPN_H
