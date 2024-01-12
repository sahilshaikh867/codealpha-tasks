#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in a particular cell
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Check if the number is not present in the current row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if the number is not present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    // If the number is not present in the current row, column, and subgrid, it's safe to place
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // Check if the cell is empty (contains 0)
            if (grid[row][col] == 0) {
                // Try placing numbers 1 to 9 in the cell
                for (int num = 1; num <= 9; num++) {
                    // Check if it's safe to place the number in the cell
                    if (isSafe(grid, row, col, num)) {
                        // Place the number in the cell
                        grid[row][col] = num;

                        // Recursively try to solve the rest of the puzzle
                        if (solveSudoku(grid)) {
                            return true; // If a solution is found, return true
                        }

                        // If placing the current number doesn't lead to a solution, backtrack
                        grid[row][col] = 0;
                    }
                }

                // If no number can be placed in the current cell, backtrack
                return false;
            }
        }
    }

    // If all cells are filled, the puzzle is solved
    return true;
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku Puzzle:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSudoku Solution:" << endl;
        printGrid(grid);
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}

