#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <vector>
#include <list>
#include <queue>
#include <assert.h>

/*
 * 类模板具有选择性实例化特点：
 * 编译器总是为所有的虚函数生成代码，对于非虚函数编译器只会为那些在其他类中被实际调用的函数生成代码。
 *
 */

template <typename Data>
class AdjacencyList {
public:
    // 在图的start点以及end点之间插入一条边表的权重为weight,
    // dist表示是否带方向，如果dist == true该path的方向为由start->end
    bool InsertPath(size_t start, size_t end, int weight = 0, bool dist = false);
    // 添加一个图节点，放在index下标处，数据为data
    bool AddAdjacencyNode(size_t index, const Data& data);
    // 显示图信息
    void ShowList() const ;
    // 借助于Dijkstra算法，求单源最短路径，求一个点start到其他所有点的最短路径
    // start到start的长度为0，之所以start到start的路径也返回主要方便通过图节点的下表来去路径长度
    std::vector<int> DijkstraFromStart(size_t start) const ;

    size_t Size() const { return _graph.size(); }

    // 深度拷贝该图
    AdjacencyList<Data> * DeepCopy();
private:
    struct AdjacencyPath;
    struct Gnode;

    bool InsertPathHead(size_t start, AdjacencyPath *path);
private:
    struct AdjacencyPath {
        int adcindex;
        int weight;
        bool dist;
        AdjacencyPath *next;
        AdjacencyPath() :
            adcindex(0), weight(0), next(nullptr) {
        }
    };

    struct Gnode {
        Data data;
        AdjacencyPath *head;
        size_t index;
        Gnode (const Data& d) :
            data(d), head(nullptr) {
        }
    };

    std::vector<Gnode*> _graph;
};

template <typename Data>
std::vector<int> AdjacencyList<Data>::DijkstraFromStart(size_t start) const {
    std::vector<int> ret;

    if (start >= _graph.size()) {
        return ret;
    }

    ret.resize(_graph.size(), -1);
    ret[start] = 0;

    std::queue<Gnode*> gq;
    gq.push(_graph[start]);

    while (!gq.empty()) {
        Gnode* node = gq.front(); gq.pop();
        AdjacencyPath *cur = node->head;
        while (cur) {
            if (ret[cur->adcindex] == -1) { // 未入过栈
                // 入栈
                gq.push(_graph[cur->adcindex]);
                // 更新路径长度
                ret[cur->adcindex] = ret[node->index] + cur->weight;
            } else {
                // 更新路径长度
                int ol = ret[cur->adcindex];
                int nl = ret[node->index] + cur->weight;
                if (nl < ol) {
                    ret[cur->adcindex] = nl;
                    // 更新下面节点的路径长度，放到栈中，因为从栈种弹出的元素我们都会重新更新它的子节点路径长度
                    gq.push(_graph[cur->adcindex]);
                }
            }
            cur = cur->next;
        }
    }

    return ret;
}

template <typename Data>
void AdjacencyList<Data>::ShowList() const {
    for (int i = 0; i < _graph.size(); ++i) {
        assert(_graph[i]);
        std::cout << "[" << i << ", " << _graph[i]->data << "] { ";
        AdjacencyPath *cur = _graph[i]->head;
        while (cur) {
            std::cout << "<" << cur->adcindex << ", " << cur->weight << ", " << cur->dist << "> ";
            cur = cur->next;
        }
        std::cout << "}" << std::endl;
    }
}

template <typename Data>
bool AdjacencyList<Data>::InsertPathHead(size_t start, AdjacencyPath *path) {
    if (!path) {
        return false;
    }

    assert(_graph[start]);

    path->next = _graph[start]->head;
    _graph[start]->head = path;

    return true;
}

template <typename Data>
bool AdjacencyList<Data>::InsertPath(size_t start, size_t end, int weight, bool dist) {
    if (start >= _graph.size() || end >= _graph.size()) {
        return false;
    }

    AdjacencyPath *path = new AdjacencyPath();
    if (!path) {
        return false;
    }

    path->adcindex = end;
    path->weight = weight;
    path->dist = dist;

    return InsertPathHead(start, path);;
}

template <typename Data>
bool AdjacencyList<Data>::AddAdjacencyNode(size_t index, const Data& data) {
    if (index != _graph.size()) {
        return false;
    }
    Gnode *gn = new Gnode(data);
    if (!gn) {
        return false;
    }

    gn->index = index;
    _graph.push_back(gn);

    return true;
}

template <typename Data>
AdjacencyList<Data> * AdjacencyList<Data>::DeepCopy() {
    AdjacencyList<Data> *adj = new AdjacencyList<Data>();
    if (!adj) {
        return adj;
    }

    // 拷贝图节点
    for (size_t index = 0; index < _graph.size(); ++index) {
        Gnode* node = new Gnode(*_graph[index]);
        if (!node) {
            delete adj;
            return adj = nullptr;
        }
        // 防止中间内存分配失败，释放内存影响到原图
        node->head = nullptr;
        adj->_graph.push_back(node);
    }
    // 拷贝边
    for (size_t index = 0; index < _graph.size(); ++index) {
        AdjacencyPath *cur = _graph[index]->head, *pre = nullptr;

        while (cur) {
            AdjacencyPath *path = new AdjacencyPath(*cur);
            if (!path) {
                delete adj;
                return adj = nullptr;
            }
            // 防止中间内存分配失败，释放内存影响到原图
            path->next = nullptr;

            if (!pre) {
                adj->_graph[index]->head = path;
            } else {
                pre->next = path;
            }
            pre = path;
            cur = cur->next;
        }
    }

    return adj;
}

#endif // ADJACENCYLIST_H
