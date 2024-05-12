#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
public:
    static Sudoku& getInstance() {
        static Sudoku instance;
        return instance;
    }

    Sudoku(Sudoku const&) = delete;
    void operator=(Sudoku const&) = delete;

    void init(int grid_size);
    bool is_valid(int row, int col, int num);
    bool solve();
    void display();
    
private:
    Sudoku();
    ~Sudoku();
    int grid_size;
    int **board;
};

#endif // SUDOKU_H