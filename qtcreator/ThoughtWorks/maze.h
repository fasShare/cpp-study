#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Maze {
public:
    // 解析command字符串
    bool ParseCommand(const std::string& command);

    // 输出结果字符串
    std::string Render();

    Maze() :
        _row(-1), _col(-1), _maze(), _result() {}
public:
    // 单元格字符串
    struct Cell {
        int _x;
        int _y;
        Cell(int x, int y) :
            _x(x), _y(y) {}
    };
    // 两个单元格连成的一条路
    struct Route {
        Cell _start;
        Cell _end;
        Route(int x1, int y1, int x2, int y2) :
            _start(x1, y1), _end(x2, y2) {}

    };
    // 把每对连接到一起的Cell解析成一条Route
    bool Parse2Route(const std::string& str);

    // 把路填充到迷宫矩阵里面
    void FullRoute(const Route& l);

    // 把迷宫矩阵里面的内容输出到结果字符串里面
    void FullResult();
private:
    int _row;                             // 迷宫矩阵的行数
    int _col;                             // 迷宫矩阵的列数
    std::vector<std::vector<char>> _maze; // 迷宫矩阵
    std::vector<Route> _lines;            // command中每两个Cell组成的一条路
    std::ostringstream _result;           // 最终的结果字符串
};

#endif // MAZE_H
