#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "tools.h"
#include "maze.h"

int main() {
    Maze maze;
    std::string command ="3 3\n0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1";

    if (!maze.ParseCommand(command)) {
        return -1;
    }

    std::string mazeText = maze.Render();
    std::cout << mazeText;

    return 0;
}
