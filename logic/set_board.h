#include "common.h"
#include <string.h>

/**
 * @brief Set numbers from file to board
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
 * @param file_name File name
*/
void set_numbers(int N, char board[N][N], char *file_name);