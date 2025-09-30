#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include "utils.h"
#include "common.h"
#include "logical_solver.h"
#include "set_board.h"

/*bool Solve(board_t *board, int N_unAssign){
    if(N_unAssign == 0){
        return true;
    }

    int x = board->unAssignInd[N_unAssign-1]->x;
    int y = board->unAssignInd[N_unAssign-1]->y;

    for(int val = 1; val < (board->N+1); val++){
        board->matrix[y][x] = val; // Set guess
        if(ValidateBoard(board, y, x)){
            bool solution;
            solution = Solve(board, N_unAssign - 1);
            if(solution){
                return true;
            }
        }
    }
    board->matrix[y][x] = 0; // No solution, reset value in backtracking
    return false;
}*/
#define DEMO 1

void clear_screen(){
    printf("\033[H\033[J");
}
int steps = 0;

bool Solve(int N, int sqrt_N, char board[N][N], unAssigned_t **unAssignInd, int N_unAssign, bool *solutionFound, int depth, char poss[N][N][N]){
    if(N_unAssign == 0){
        return true;
    }
    int tmp = N_unAssign - 1;
    int x = unAssignInd[tmp]->x;
    int y = unAssignInd[tmp]->y;

    for(int i = 0; i < N; i++){
        steps++;
        if(*solutionFound) break;
        if(poss[y][x][i] == '0') continue;

        board[y][x] = (i+1) + '0'; // Set guess
        clear_screen();
        display_board(N, sqrt_N, board);
        usleep(10310);

        if(validate_board(N, sqrt_N, board, y, x)){
            bool local_solution = false;
                char board_copy[N][N];
                copy_board(N, board, board_copy);
                board_copy[y][x] = (i+1) + '0';
                local_solution = Solve(N, sqrt_N, board_copy, unAssignInd, tmp, solutionFound, depth+1, poss);
                if(local_solution){
                    if(check_entire_board(N, board_copy)){
                        printf("SOLUTION\n");
                        printf("Steps: %d\n", steps);
                    }
                    #if DEMO == 1
                    display_board(N, sqrt_N, board_copy);
                    #endif
                    *solutionFound = true; // Workaround to stop all threads
                }
        }
    }
    board[y][x] = '0'; // No solution, reset value in backtracking
    return false;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <file> <N>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[2]);
    int sqrt_N = sqrt(N);
    char board[N][N];
    set_numbers(N, board, argv[1]);                    // Set numbers from file

    printf("--------------------\n");
    printf("Running %s\n", argv[1]);
    
    #if DEMO == 1
    printf("NOF Unassigned cells before elimination: %d\n", count_unassigned(N, board));
    display_board(N, sqrt_N, board);
    #endif
    bool solution = false;
    double start = get_wall_time();                     // Start timer
    char possibilities[N][N][N];
    set_possibilities(N, sqrt_N, board, possibilities);            // Set possibilities
    eliminate_possibilities(N, sqrt_N, board, possibilities);      // Eliminate possibilities and set logical values
    int N_unAssign = count_unassigned(N, board);

    #if DEMO == 1
    printf("NOF Unassigned cells after elimination: %d\n", N_unAssign);
    #endif
    if(N_unAssign == 0){                                // If no unassigned cells, print solution. Else brute force
        if(check_entire_board(N, board)){
                printf("EARLY SOLUTION\n");
        }else{
            printf("NO SOLUTION\n");
        }
        #if DEMO == 1
        display_board(N, sqrt_N, board);
        #endif
    }else{
        unAssigned_t **unAssignInd = set_unassigned(N, board, N_unAssign); // Set unassigned cells (x, y)
        Solve(N, sqrt_N, board, unAssignInd, N_unAssign, &solution, 0, possibilities);
        if(!solution){
            printf("NO SOLUTION\n");
        }
        destroy_unassigned(unAssignInd, N_unAssign);
    }
    printf("Time: %f\n", get_wall_time() - start);  // End timer and print
    printf("--------------------\n");
    return 0;
}