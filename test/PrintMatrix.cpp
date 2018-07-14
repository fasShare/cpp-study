#include <iostream>
#include <vector>

using namespace std;
vector<int> printMatrix(vector<vector<int> > matrix) {
    vector<int> ret;
    if (matrix.size() == 0) {
        return ret;
    }
    if (matrix[0].size() == 0) {
        return ret;
    }
    int leftupx = 0, leftupy = 0, rightdownx = matrix[0].size() - 1, rightdowny = matrix.size() - 1;
    //cout << "outter -- leftupx=" << leftupx << " leftupy=" << leftupy << " rightdownx=" << rightdownx << " rightdowny=" << rightdowny <<endl; 
    while ((leftupx <= rightdownx) || (leftupy <= rightdowny)) {
        //cout << "leftupx=" << leftupx << " leftupy=" << leftupy << " rightdownx=" << rightdownx << " rightdowny=" << rightdowny <<endl; 
        for (int i = leftupx; i <= rightdownx; ++i) {
            ret.push_back(matrix[leftupy][i]);
        }
        leftupy++;
        if (leftupy > rightdowny) {
            return ret;
        }
        for (int i = leftupy; i <= rightdowny; ++i) {
            ret.push_back(matrix[i][rightdownx]);
        }
        rightdownx--;
        if (leftupx > rightdownx) {
            return ret;
        }
        for (int i = rightdownx; i >= leftupx; --i) {
            ret.push_back(matrix[rightdowny][i]);
        }
        rightdowny--;
        for (int i = rightdowny; i >= leftupy; --i) {
            ret.push_back(matrix[i][leftupx]);
        }
        leftupx++;
    }
    return ret;
}

vector<int> Test(int col, int row) {
    vector<vector<int> > matrix;
    matrix.resize(col);
    int curnum = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        matrix[i];
        for (int j = 0; j < row; ++j) {
            matrix[i].push_back(++curnum);
        }
    }

    return printMatrix(matrix);
}

int main () {
    vector<int> ret = Test(1, 5);
    cout << ret.size() << endl;
//    for (int i = 0; i < ret.size(); ++i) {
//        cout << ret[i] << " ";
//    }
//    cout << endl;
}
