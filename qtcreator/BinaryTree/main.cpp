#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

struct TreeNode {
    int _data;
    int _height;
    TreeNode *_left;
    TreeNode *_right;
    TreeNode(int data) :
        _data(data), _height(1), _left(nullptr), _right(nullptr) {}
    ~TreeNode() {
        // 析构函数会递归调用
        if (_left) {
            delete _left;
        }
        if (_right) {
            delete _right;
        }
    }
};

int Max(int left, int right) {
    return left >= right ? left : right;
}

int Abs(int N) {
    return N < 0 ? -N : N;
}

// 返回以root为树根的最左节点
TreeNode *LeftMostNode(TreeNode* root){
    if (!root) { // 最左节点为空
        return root;
    }

    if (!root->_left) { // root指向最左节点
        return root;
    }
    return LeftMostNode(root->_left);
}

// 返回以root为树根的最右节点
TreeNode *RightMostNode(TreeNode* root){
    if (!root) { // 最右节点为空
        return root;
    }

    if (!root->_right) { // root指向最右节点
        return root;
    }
    return LeftMostNode(root->_right);
}

bool IsLeaf(TreeNode* root) {
    return !root->_left && !root->_right;
}

// 左旋并调节相关节点树高
void LeftRotate(TreeNode* &root) {
    assert(root);
    assert(root->_left);

    TreeNode* left = root->_left;
    root->_left = left->_right;

    int left_right_height = left->_right ? left->_right->_height : 0; // 关键
    int root_right_height = root->_right ? root->_right->_height : 0; // 关键
    root->_height = Max(left_right_height + 1, root_right_height + 1);

    left->_right = root;
    int left_left_height = left->_left ? left->_left->_height : 0; // 关键
    left->_height = Max(root->_height + 1, left_left_height + 1);

    root = left;
}
// 右旋并调节相关节点树高
void RightRotate(TreeNode* &root) {
    assert(root);
    assert(root->_right);

    TreeNode* right = root->_right;
    root->_right = right->_left;

    int right_left_height = right->_left ? right->_left->_height : 0; // 关键
    int root_left_height = root->_left ? root->_left->_height : 0;    // 关键
    root->_height = Max(root_left_height + 1, right_left_height + 1);

    right->_left = root;
    int right_right_height = right->_right ? right->_right->_height : 0; // 关键
    right->_height = Max(root->_height + 1, right_right_height + 1);

    root = right;
}

// 调节root的平衡，返回调节平衡后root的高度
int AdjustNodeBlance(TreeNode* &root) {
    if (!root) {
        return 0;
    }
    int left_height = root->_left ? root->_left->_height : 0;
    int right_height = root->_right ? root->_right->_height : 0;

    // 已经是平衡树
    if (Abs(left_height - right_height) <= 1) {
        return root->_height;
    }

    // 不平衡根据高度差旋转
    if (left_height > right_height) {
        assert(root->_left);

        int left_left_height = root->_left->_left ? root->_left->_left->_height : 0;
        int left_right_height = root->_left->_right ? root->_left->_right->_height : 0;

        if (left_left_height > left_right_height) {
            LeftRotate(root);
        } else if (left_left_height < left_right_height) {
            RightRotate(root->_left);
            LeftRotate(root);
        } else { // 这有在删除时会存在这种现象
            LeftRotate(root);
        }
    } else {
        assert(root->_right);

        int right_left_height = root->_right->_left ? root->_right->_left->_height : 0;
        int right_right_height = root->_right->_right ? root->_right->_right->_height : 0;

        if (right_right_height > right_left_height) {
            RightRotate(root);
        } else if (right_right_height < right_left_height) {
            LeftRotate(root->_right);
            RightRotate(root);
        } else {
            RightRotate(root);
        }
    }

    return root->_height;
}

int InsertBlanceTreeNode(TreeNode* &root, int data) {
    if (!root) {
        root = new TreeNode(data);
        if (!root) {
            return 0;
        }
        return 1;
    }

    int right_height = root->_right ? root->_right->_height : 0;
    if (root->_data < data) {
        right_height = InsertBlanceTreeNode(root->_right, data);
    }

    int left_height = root->_left ? root->_left->_height : 0;
    if (root->_data > data) {
        left_height = InsertBlanceTreeNode(root->_left, data);
    }

    if (Abs(left_height - right_height) <= 1) {
        return root->_height = Max(root->_height, Max(right_height, left_height) + 1);
    }
    // 不用过分纠结新增节点插入到左左，左右，右右，右左等等，直接根据高度差决定旋转方式，然后调节平衡。
    return AdjustNodeBlance(root);
}

int DeleteTreeNode(TreeNode* &root, int data) {
    if (!root) {
        return 0;
    }

    if (root->_data == data) {
        if (IsLeaf(root)) {
            delete root;
            root = nullptr;

            return 0;
        }

        TreeNode* left = LeftMostNode(root->_right);
        if (!left) {
            root->_data = root->_right->_data;
            delete root->_right;
            root->_right = nullptr;
            root->_height -= 1;
        } else {
            root->_data = left->_data;
            root->_height = Max(root->_height, 1 + DeleteTreeNode(root->_right, left->_data));
        }
    } else if (root->_data > data) {
        root->_height = Max(root->_height, 1 + DeleteTreeNode(root->_left, data));
    } else {
        root->_height = Max(root->_height, 1 + DeleteTreeNode(root->_right, data));
    }

    return AdjustNodeBlance(root);
}

static void __ShowTree(TreeNode* root, int tabs) {
    if(!root) {
        return;
    }
    __ShowTree(root->_left, tabs + 1);
    for (int i = 0; i < tabs; ++i) {
        std::cout << "\t";
    }
    std::cout << root->_data << "(" << root->_height << ")" << std::endl;
    __ShowTree(root->_right, tabs + 1);
}
// 中序显示二叉树 数据后面跟的有树高
void ShowTree(TreeNode *root) {
    __ShowTree(root, 0);
}

// 计算树高
int TreeHeight(TreeNode *root) {
    if (!root) {
        return 0;
    }
    return Max(TreeHeight(root->_left), TreeHeight(root->_right)) + 1;
}

static int __IsBlanceTree(TreeNode *root) {
    if (!root) {
        return 0;
    }
    int left = __IsBlanceTree(root->_left);
    if (left == -1) {
        return -1;
    }
    int right = __IsBlanceTree(root->_right);
    if (right == -1) {
        return -1;
    }

    if (Abs(left - right) > 1) {
        return -1;
    }

    return Max(left, right) + 1;
}
// 判断是否是平衡二叉树
bool IsBlanceTree(TreeNode *root) {
    if (!root) {
        return false;
    }

    return __IsBlanceTree(root) == -1 ? false : true;
}

// 中序遍历节点值递增，约定：空节点本身就是二分查找树
static bool __IsBinarySearchTree(TreeNode* root, int& lastVal, bool& isfirst) {
    // 空节点不更新lastVal和isfirst，直接返回true
    if (!root) {
        return true;
    }

    if (!__IsBinarySearchTree(root->_left, lastVal, isfirst)) {
        return false;
    }
    if (isfirst) {
        isfirst = false;
        lastVal = root->_data;
    } else {
        if (root->_data <= lastVal) {
            // 不满足递增关系
            return false;
        }
        // 用当前节点更新lastVal，用于下次节点比较
        lastVal = root->_data;
    }
    if (!__IsBinarySearchTree(root->_right, lastVal, isfirst)) {
        return false;
    }

    return true;
}

// 是否是二分查找树（二分查找树 VS 平衡二叉树）
bool IsBinarySearchTree (TreeNode* root) {
    if (!root) {
        return true;
    }
    int lastval = 0;
    bool isfirst = true;
    return __IsBinarySearchTree(root, lastval, isfirst);
}

// 中序遍历过程中查找下一个将要遍历的节点
TreeNode* FindNextInBinarySearchTree(TreeNode* root, int next) {
    if (!root) {
        return nullptr;
    }

    TreeNode *nextnode = nullptr;

    while (root) {
        if (root->_data > next) {
            // 一定要在出现较大值时才去修改prenode
            nextnode = root;
            root = root->_left;
        } else {
            root = root->_right;
        }
    }
    return nextnode;
}

// 中序遍历过程中查找遍历该值时的前一个节点
TreeNode *FindPreInBinarySearchTree(TreeNode *root, int pre) {
    if (!root) {
        return nullptr;
    }

    TreeNode *prenode = nullptr;

    while (root) {
        if (root->_data < pre) {
            prenode = root;
            root = root->_right;
        } else {
            root = root->_left;
        }
    }

    return prenode;
}

// 最近公共祖先，如果left或则right不存在将会返回指向存在节点的node指针
TreeNode *LowestCommonAncestor(TreeNode *root, int left, int right) {
    if (!root) {
        return root;
    }

    if (root->_data == left || root->_data == right) {
        return root;
    }

    TreeNode *pleft = LowestCommonAncestor(root->_left, left, right);
    TreeNode *pright = LowestCommonAncestor(root->_right, left, right);

    // 当前节点是left和right的LCA
    if (pleft && pright) {
        return root;
    }

    // 有可能返回为nullptr，说明没有在当前节点以及其左右节点下找到left和right的LCA
    return pleft == nullptr ? pright : pleft;
}

int main()
{
    TreeNode *node = nullptr;
    std::vector<int> node_data = {7, 9, 3, 5, 0, 6, 4 , 1, 22, 33, 44, 55, 34, 35, 23, 32, 36, 12, 13, 21};

    for (auto &iter : node_data) {
        InsertBlanceTreeNode(node, iter);
    }

    ShowTree(node);

    std::cout << "tree height:" << TreeHeight(node) << std::endl;
    std::cout << "is blance tree:" << IsBlanceTree(node) << std::endl;
    std::cout << "is binary tree:" << IsBinarySearchTree(node) << std::endl;

    TreeNode *next = FindNextInBinarySearchTree(node, 7);
    if (next) {
        std::cout << "next data:" << next->_data << std::endl;
    }

    TreeNode *pre = FindPreInBinarySearchTree(node, 7);
    if (pre) {
        std::cout << "pre data:" << pre->_data << std::endl;
    }

    TreeNode *lca = LowestCommonAncestor(node, 0, -1);
    if (lca) {
        std::cout << "lca:" << lca->_data << std::endl;
    }


    std::cout << "height:" << DeleteTreeNode(node, 1) << std::endl;
    std::cout << "height:" << DeleteTreeNode(node, 32) << std::endl;
    std::cout << "height:" << DeleteTreeNode(node, 44) << std::endl;
    ShowTree(node);

    return 0;
}
