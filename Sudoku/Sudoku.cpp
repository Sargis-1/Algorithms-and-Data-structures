#include <iostream>
#include <vector>


void print(std::vector<std::vector<int>> vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



bool issafe(std::vector<std::vector<int>> sudoku, int row, int col, int num) {
    for (int i = 0; i < sudoku.size(); i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num)
            return false;
    }

    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[r + i][c + j] == num)
                return false;
        }
    }

    return true;
}

bool sudokusolver(std::vector<std::vector<int>> sudoku, int row, int col) {
   if (row == sudoku.size() - 1 && col == sudoku.size()) {
        print(sudoku);
        return true;
    }

    if (col == sudoku.size()) {
        ++row;
        col = 0;
    }

    if (sudoku[row][col])    return sudokusolver(sudoku, row, col + 1);

    for (int i = 1; i <= sudoku.size(); i++) {
        if (issafe(sudoku, row, col, i)) {
            sudoku[row][col] = i;
            if(sudokusolver(sudoku, row, col + 1))
                return true;
            sudoku[row][col] = 0;
        }
    }

    return false;


}



int main()
{
    std::vector<std::vector<int>> test = {
    {0, 8, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 3, 6, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 7},
    {0, 5, 0, 0, 6, 8, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 7, 0, 0, 0},
    {9, 0, 0, 5, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    sudokusolver(test, 0, 0);
}

