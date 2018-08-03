#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

class HuffMan
{
private:
    struct HuffmanNode {
        HuffmanNode(double weight, char value) :
        _weight(weight), _value(value), _left(nullptr), _right(nullptr) {
        }

        bool operator () (const HuffmanNode& rhs) const {
            std::cout << " in > " << std::endl;
            return this->_weight > rhs._weight;
        }
        ~HuffmanNode() {
            // 会递归的删除的
            if (_left) {
                delete _left;
            }
            if (_right) {
                delete _right;
            }
        }

        double _weight;
        char _value;
        HuffmanNode *_left;
        HuffmanNode *_right;
    };

    struct Greator {
        bool operator() (HuffmanNode* &left, HuffmanNode* &right) const {
            return left->_weight > right->_weight;
        }
    };

public:
    HuffMan() {}
    bool AddHuffmanNode(double weight, char value) {
        HuffmanNode *node = new HuffmanNode(weight, value);
        if (!node) {
            return false;
        }
        _hq.push(node);
        return true;
    }

    ~HuffMan() {
        // 释放内存空间
        while (_hq.size() > 0) {
            HuffmanNode *node = _hq.top();
            _hq.pop();
            delete node;
        }
    }

    std::map<char, std::vector<short>> ToBinaryCode() {
        std::map<char, std::vector<short>> ret;
        if (!buildHuffmanCode()) {
           return ret;
        }

        HuffmanNode *node = _hq.top();

        std::vector<short> binary_set;
        toBinaryCode(node, binary_set, ret);

        return ret;
    }

private:
    bool isLeaf(HuffmanNode *root) {
        return !root->_left && !root->_right;
    }

    void toBinaryCode (HuffmanNode *root, std::vector<short>& binary_set,
                       std::map<char, std::vector<short>>& ret) {
        if (!root) {
            return;
        }
        if (isLeaf(root)) {
            ret[root->_value] = binary_set;
            return;
        }

        binary_set.push_back(0);
        toBinaryCode(root->_left, binary_set, ret);
        binary_set.pop_back();

        binary_set.push_back(1);
        toBinaryCode(root->_right, binary_set, ret);
        binary_set.pop_back();
    }

    bool buildHuffmanCode() {
        if (_hq.size() == 0) {
            return false;
        }

        while (_hq.size() > 1) {
            HuffmanNode *left = _hq.top();
            _hq.pop();
            HuffmanNode *right = _hq.top();
            _hq.pop();

            HuffmanNode *node = new HuffmanNode(left->_weight + right->_weight, 0);
            if (!node) {
                return false;
            }

            node->_left = left;
            node->_right = right;

            _hq.push(node);
        }

        return true;
    }

    // 用Greator最终形成的是小根堆
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Greator> _hq;
};

int main()
{
    HuffMan huff;

    huff.AddHuffmanNode(5, 'a');
    huff.AddHuffmanNode(32, 'b');
    huff.AddHuffmanNode(18, 'c');
    huff.AddHuffmanNode(7, 'd');
    huff.AddHuffmanNode(25, 'e');
    huff.AddHuffmanNode(13, 'f');

    std::map<char, std::vector<short>> ret = huff.ToBinaryCode();

    for (std::map<char, std::vector<short>>::const_iterator iter = ret.begin(); iter != ret.end(); ++iter) {
        char value = iter->first;

        std::cout << value << " : ";
        std::vector<short> bits = iter->second;
        for (size_t index = 0; index < bits.size(); ++index) {
            std::cout << bits[index];
        }
        std::cout << std::endl;
    }

    return 0;
}
