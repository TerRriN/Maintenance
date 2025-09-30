#include "common.h"
#include <stdbool.h>

/**
 * @brief Check if there are duplicate numbers in a row
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
 * @param y Row
 * @return True if there are duplicates, otherwise false
*/
bool duplicate_numbers_in_row(int N, char board[N][N], int y, int x);

/**
 * @brief Check if there are duplicate numbers in a column
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
 * @param x Column
 * @return True if there are duplicates, otherwise false
*/
bool duplicate_numbers_in_col(int N, char board[N][N], int y, int x);

/**
 * @brief Check if there are duplicate numbers in a box
 * 
 * @param N Size of the board (N x N)
 * @param sqrt_N Square root of N
 * @param board Sudoku board
 * @param y Row
 * @param x Column
 * @return True if there are duplicates, otherwise false
*/
bool duplicate_numbers_in_box(int N, int sqrt_N, char board[N][N], int y, int x);

/**
 * @brief Validate board
 *  
 * @param N Size of the board (N x N)
 * @param sqrt_N Square root of N
 * @param board Sudoku board
 * @param y Row
 * @param x Column
 * @return True if board is valid, otherwise false
*/
bool validate_board(int N, int sqrt_N, char board[N][N], int y, int x);

/**
 * @brief Check if the entire board is valid
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
 * @return True if board is valid, otherwise false
*/
bool check_entire_board(int N, char board[N][N]);

/**
 * @brief Compare to hardcoded solution
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
 * @return True if board is equal to hardcoded solution, otherwise false
 */
bool compare_to_solution(int N, char board[N][N]);