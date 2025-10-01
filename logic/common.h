#ifndef COMMON_H
#define COMMON_H

//extern int N;
extern int sqrt_N;

typedef struct unAssignInd{
    int x;
    int y;
} unAssigned_t;

typedef struct pair{
    int x1;
    int x2;
    int y1;
    int y2;
    int val;
} pair_t;

typedef struct line{
    int val;
    int x_coord;
    int y_coord;
    int dir;
} line_t;
#endif

#include <stdio.h>
#include <time.h>

/**
 * @brief Simple clock function to measure time
 * @return time in seconds
*/
double get_wall_time();

/**
 * @brief Print board
 * 
 * @param N Size of the board (N x N)
 * @param board Sudoku board
*/
void print_board(int N, char board[N][N]);

/**
 * @brief Print all possibilities
 *  
 * @param N Size of the board (N x N)
 * @param poss Array of possibilities
 * @param N_elements Number of elements in the possibilities array
*/
void print_possibilities(int N, char poss[N][N][N]);

/**
 * @brief Print possibilities for a specific cell
 * 
 * @param N Size of the board (N x N)
 * @param sqrt_N Square root of N
 * @param poss Array of possibilities
 * @param y Row
 * @param x Column
*/
void print_precise_possibilities(int N, char poss[N][N][N], int y, int x);

/**
 * @brief Display sudoku board in a more readable format
 * 
 * @param N Size of the board (N x N)
 * @param sqrt_N Square root of N
 * @param board Sudoku board
 */
void display_board(int N, int sqrt_N, char board[N][N]);