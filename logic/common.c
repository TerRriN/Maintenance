#include "common.h"

int N;
int sqrt_N;

double get_wall_time() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + (double)time.tv_nsec / 1e9;
}

void print_board(int N, char board[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf(" %d ", board[i][j] - '0');
        }
        printf("\n");
    }
    printf("\n");
}

void print_possibilities(int N, char poss[N][N][N]){
    int x = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("x: %d, y: %d: [ ", j, i);
            for(int k = 0; k < N; k++){
                x = poss[i][j][k] - '0';
                if(x != 0) printf("%d ", x);
            }
            printf("]\n");
        }
    }
}


void print_precise_possibilities(int N, char poss[N][N][N], int y, int x){
    int x_val = 0;
    printf("x: %d, y: %d: [ ", x, y);
    for(int k = 0; k < N; k++){
        x_val = poss[y][x][k] - '0';
        if(x_val != 0) printf("%d ", x_val);
    }
    printf("]\n");
}

// Helper function to sud_display_board_std
void display_line(int line_length){
    for(int i = 0; i < line_length; i++){
        printf("-");
    }
    printf("\n");
}

void display_board_standard(int N, int sqrt_N, char board[N][N]){
    int x = 0;
    int line = 0;
    int wall = 0;
    int line_length = (N*sqrt_N)+sqrt_N+1;

    display_line(line_length);
    printf("|");
    for(int i = 0; i < N; i++){
        if(line == sqrt_N){
            display_line(line_length);
            line = 0;
        }
        for(int j = 0; j < N; j++){
            if(wall == sqrt_N){
                wall = 0;
                printf("|");
            }
            x = board[i][j] - '0';
            if(x != 0){
                printf(" %d ", x);
            }else{
                printf("   ");
            }
            wall++;
        }
        printf("|");
        printf("\n");
        line++;
    }
    display_line(line_length);
}

void display_board_giant(int N, int sqrt_N, char board[N][N]){
    int x = 0;
    int line = 0;
    int wall = 0;
    int line_length = (4*sqrt_N)*sqrt_N+1+sqrt_N;

    //One cell: 

    display_line(line_length);
    printf("|");
    for(int i = 0; i < N; i++){
        if(line == sqrt_N){
            display_line(line_length);
            line = 0;
        }
        for(int j = 0; j < N; j++){
            if(wall == sqrt_N){
                wall = 0;
                printf("|");
            }
            x = board[i][j] - '0';
            if(x >= 10){
                printf(" %d ", x);
            }else if(x != 0){
                printf("  %d ", x);
            }else{
                printf("    ");
            }
            wall++;
        }
        printf("|");
        printf("\n");
        line++;
    }
    display_line(line_length);
}

void display_board(int N, int sqrt_N, char board[N][N]){
    if(N == 9){
        display_board_standard(N, sqrt_N, board);
    }else{
        display_board_giant(N, sqrt_N, board);
    }
}

/*
| 6  9  3 | 8  7  4 | 5  1  2 |
-------------------------------

| 11   3   4  16 | 15  13   5   7 | 10   2   6   9 |  1  12   8  14 |
---------------------------------------------------------------------

| 18   9  25   1   2 | 11          13  22 |  4      21       5 |     23   7      20 | 15  12   3  14   8 |
----------------------------------------------------------------------------------------------------------
*/