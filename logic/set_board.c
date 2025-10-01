#include "set_board.h"

void set_numbers_txt(int N, char board[N][N], char *file_name){
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char c;
    int i = 0, j = 0;
    int val = 0;

    while((c = fgetc(file)) != EOF){
        if(c == ' '){
            board[i][j] = val + '0';
            val = 0;
            j++;
        }else if(c == '\n'){
            board[i][j] = val + '0';
            val = 0;
            i++;
            j = 0;
        }else{
            val = val*10 + (c - '0');
        }
    }
    fclose(file);
}

void set_numbers(int N, char board[N][N], char *file_name){
    if(strcmp(ext, ".txt") == 0){
        set_numbers_txt(N, board, file_name);
    }
}