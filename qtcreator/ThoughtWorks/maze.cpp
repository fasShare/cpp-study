#include "maze.h"
#include "tools.h"

// 解析command字符串
bool Maze::ParseCommand(const std::string& command) {
    std::istringstream input;
    input.str(command);

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    if (lines.size() != 2) {
        std::cout << "Incorrect command format.​" << std::endl;
        return false;
    }

    // 处理输入的第一行
    std::vector<std::string> col_row = StringSplit(lines[0], " ");
    if (col_row.size() != 2) {
        std::cout << "Incorrect command format.​" << std::endl;
        return false;
    }

    if (!(IsIntStr(col_row[0]) && IsIntStr(col_row[1]))) {
        std::cout << "Invalid number format​." << std::endl;
        return false;
    }
    _row = std::atoi(col_row[0].c_str());
    _col = std::atoi(col_row[1].c_str());
    if (_row < 0 || _col < 0) {
        std::cout << "Number out of range​." << std::endl;
        return false;
    }

    // 处理输入的第二行
    std::vector<std::string> items = StringSplit(lines[1], ";");
    for (size_t i = 0; i < items.size(); ++i) {
        if (!Parse2Route(items[i])) {
            return false;
        }
    }

    FullResult();
    return true;
}

// 输出结果字符串
std::string Maze::Render() {
    return _result.str();
}

// 把每对连接到一起的Cell解析成一条Route
bool Maze::Parse2Route(const std::string& str) {
    std::vector<std::string> ret = StringSplit(str, " ,");
    if (ret.size() != 4) {
        std::cout << "Incorrect command format​." << std::endl;
        return false;
    }

    int x1 = std::atoi(ret[0].c_str());
    int y1 = std::atoi(ret[1].c_str());
    int x2 = std::atoi(ret[2].c_str());
    int y2 = std::atoi(ret[3].c_str());
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 ||
        x1 >= _row || y1 >= _col || x2 >= _row || y2 >= _col) {
        std::cout << "Number out of range​." << std::endl;
        return false;
    }

    // 每一个 ​ cell​ 只能够直接与相邻正南、正北、正东、正西的 ​ cell​ 连通
    if (Abs(x2 - x1) >= 1 && Abs(y2 - y1) >= 1) {
        std::cout << "Maze format error." << std::endl;
        return false;
    }

    _lines.push_back(Route(2 * x1 + 1, 2 * y1 + 1, 2 * x2 + 1, 2 * y2 + 1));
    return true;
}
// 把路填充到迷宫矩阵里面
void Maze::FullRoute(const Route& l) {
    int x1 = l._start._x, y1 = l._start._y, x2 = l._end._x, y2 = l._end._y;
    if (x1 - x2 == 0) {
        if (y1 > y2) {
            for (int k = y2; k <= y1; ++k) {
                _maze[x1][k] = 'R';
            }
        } else {
            for (int k = y1; k <= y2; ++k) {
                _maze[x1][k] = 'R';
            }
        }
    } else if (y1 - y2 == 0) {
        if (x1 > x2) {
            for (int k = x2; k <= x1; ++k) {
                _maze[k][y1] = 'R';
            }
        } else {
            for (int k = x1; k <= x2; ++k) {
                _maze[k][y1] = 'R';
            }
        }
    }
}

// 把迷宫矩阵里面的内容输出到结果字符串里面
void Maze::FullResult() {
    _maze.resize(2 * _row + 1);
    for (size_t i = 0; i < _maze.size(); ++i) {
        _maze[i].resize(2 * _col + 1, 'W');
    }

    for (size_t i = 0; i < _lines.size(); ++i) {
        FullRoute(_lines[i]);
    }

    for (size_t row = 0; row < _maze.size(); ++row) {
        for (size_t col = 0; col < _maze[row].size(); ++col) {
            _result << "[" << _maze[row][col] << "]";
        }
        _result << std::endl;
    }
}

