#include "sudoku.h"

void Sudoku::init(int block_size) {
    if (board != nullptr) {
        for (int i = 0; i < block_size * block_size; i++) {
            delete[] board[i];
        }
        delete[] board;
    }
    
    int size = block_size * block_size;
    this->block_size = block_size;
    this->board = new int*[size];
    for (int i = 0; i < size; i++) {
        this->board[i] = new int[size];
        for (int j = 0; j < size; j++) {
            this->board[i][j] = 0;
        }
    }
}

bool Sudoku::is_valid(int row, int col, int num) {
    for (int i = 0; i < block_size * block_size; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    int start_row = row - row % block_size;
    int start_col = col - col % block_size;
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            if (board[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::solve() {
    int size = block_size * block_size;
    int *possible_nums = new int[size];
    for (int i = 0; i < size; i++) {
        possible_nums[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                std::shuffle(possible_nums, possible_nums + size, g);
                for (int k = 0; k < size; k++) {
                    if (is_valid(i, j, possible_nums[k])) {
                        board[i][j] = possible_nums[k];
                        if (solve()) return true;
                        board[i][j] = 0;
                    }
                }
                delete[] possible_nums;
                return false;
            }
        }
    }
    delete[] possible_nums;
    return true;
}

void Sudoku::clear() {
    int size = block_size * block_size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

void Sudoku::display() {
    int size = block_size * block_size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}