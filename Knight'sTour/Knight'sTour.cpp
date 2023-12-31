﻿#include <iostream>
#include <vector>
#include <iomanip>

void print(std::vector<std::vector<int>> vec) {
    for (int k = 0; k < vec.size(); k++) {
        for (int m = 0; m < vec[k].size(); m++) {
            std::cout << std::setw(2) << vec[k][m] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isvalid(int i, int j, std::vector<std::vector<int>>& board) {
    return (i >= 0 && j >= 0 && i <= 7 && j <= 7 && board[i][j] == -1);
}

bool backtrack(int i, int j, std::vector<std::vector<int>> &board, int arrI[], int arrJ[], int index) {
    if (index == 64) {
        return true;
    }

    //print(board);
    for (int k = 0; k < 8; k++) {
        int newi = i + arrI[k];
        int newj = j + arrJ[k];
        if (isvalid(newi, newj, board)) {
            board[newi][newj] = index;
            if (backtrack(newi, newj, board, arrI, arrJ, index + 1))
                return true;
            else
                board[newi][newj] = -1;
        }
        
    }
    return false;
}


void Knightstour(int i, int j) {
    int arrI[8] = { -2, -2, -1, -1,  1, 1,  2, 2 };
    int arrJ[8] = { -1,  1, -2,  2, -2, 2, -1, 1 };
    std::vector<std::vector<int>> board(8, std::vector<int>(8, -1));
    backtrack(i, j, board, arrI, arrJ, 0);
    print(board);
}


int main(){
    Knightstour(2, 1);
}

