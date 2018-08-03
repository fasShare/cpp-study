#include <iostream>
#include <string>

#include <AdjacencyList.h>

using namespace std;

int main() {
    AdjacencyList<string> *pg = nullptr;

    {
        AdjacencyList<string> graph;

        graph.AddAdjacencyNode(0, "first");
        graph.AddAdjacencyNode(1, "second");
        graph.AddAdjacencyNode(2, "third");
        graph.AddAdjacencyNode(3, "fourth");
        graph.AddAdjacencyNode(4, "fifth");

        graph.InsertPath(0, 1, 2, true);
        graph.InsertPath(0, 2, 5, true);
        graph.InsertPath(1, 2, 2, true);
        graph.InsertPath(1, 3, 6, true);
        graph.InsertPath(2, 3, 7, true);
        graph.InsertPath(3, 2, 2, true);
        graph.InsertPath(2, 4, 1, true);
        graph.InsertPath(3, 4, 4, true);


        graph.ShowList();

        std::vector<int> ret = graph.DijkstraFromStart(0);
        std::cout << "ret size:" << ret.size() << std::endl;
        for (size_t index = 0; index < ret.size(); ++index) {
            std::cout << ret[index] << std::endl;
        }

        pg = graph.DeepCopy();
    }

    // 执行到这里graph已经被销毁，如果pg还能用，说明深度拷贝成功
    pg->ShowList();
    std::vector<int> ret = pg->DijkstraFromStart(0);
    std::cout << "ret size:" << ret.size() << std::endl;
    for (size_t index = 0; index < ret.size(); ++index) {
        std::cout << ret[index] << std::endl;
    }

    return 0;
}
