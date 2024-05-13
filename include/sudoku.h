#ifndef SUDOKU_H
#define SUDOKU_H

#include <random>
#include <algorithm>
#include <iostream>

class Sudoku {
public:
    Sudoku() : block_size(0), board(nullptr) {}
    ~Sudoku() {
        if (board != nullptr) {
            for (int i = 0; i < block_size * block_size; i++) {
                delete[] board[i];
            }
            delete[] board;
        }
    }
    int get_block_size() { return block_size; }
    int get_cell(int row, int col) { return board[row][col]; }
    void init(int block_size);
    bool is_valid(int row, int col, int num);
    bool solve();
    void display();
    void clear();
    
private:
    int block_size;
    int **board;
};

#endif // SUDOKU_H