#include <CUnit/Basic.h>
#include "logical_solver.h"
#include "set_board.h"
#include "utils.h"

int init_suite(void)
{
    printf("\n");
    return 0;
}
int clean_suite(void) { return 0; }

static char test_board_empty_9[9][9] = {
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'},
    {'0','0','0', '0','0','0', '0','0','0'}
};

static char test_board_partial_9[9][9] = {
    {'5','3','0', '0','7','0', '0','0','0'},
    {'6','0','0', '1','9','5', '0','0','0'},
    {'0','9','8', '0','0','0', '0','6','0'},
   
    {'8','0','0', '0','6','0', '0','0','3'},
    {'4','0','0', '8','0','3', '0','0','1'},
    {'7','0','0', '0','2','0', '0','0','6'},
   
    {'0','6','0', '0','0','0', '2','8','0'},
    {'0','0','0', '4','1','9', '0','0','5'},
    {'0','0','0', '0','8','0', '0','7','9'}
};

static char test_board_full_9[9][9] = {
    {'5','3','4', '6','7','8', '9','1','2'},
    {'6','7','2', '1','9','5', '3','4','8'},
    {'1','9','8', '3','4','2', '5','6','7'},
    {'8','5','9', '7','6','1', '4','2','3'},
    {'4','2','6', '8','5','3', '7','9','1'},
    {'7','1','3', '9','2','4', '8','5','6'},
    {'9','6','1', '5','3','7', '2','8','4'},
    {'2','8','7', '4','1','9', '6','3','5'},
    {'3','4','5', '2','8','6', '1','7','9'}
};

static char test_board_empty_16[16][16] = {
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}, 
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
};
//get char value, translate to int, translate back into new char value
static char test_board_partial_16[16][16] = {
    {'2','0','9','0','8','0','=','0','<','0','>','0',':','0','?','0'},
    {'4','0','?','0','3','0','9','0','=','0','8','0','@','0','>','0'},
    {'1','0','6','0','?','0','5','0',';','0',':','0','3','0','8','0'},
    {'@','0','8','0','>','0',':','0','4','0','2','0','9','0','5','0'},
    
    {'<','0','@','0',':','0','?','0','8','0','5','0','6','0',';','0'},
    {'6','0','1','0','5','0','8','0','9','0','4','0','>','0','3','0'},
    {'>','0','4','0','6','0','1','0','@','0','7','0','8','0','2','0'},
    {'3','0',':','0','4','0','2','0','6','0','=','0','1','0','@','0'},
    
    {'=','0','2','0','7','0','>','0','3','0','?','0','<','0','1','0'},
    {'5','0','>','0','2','0','<','0',':','0',';','0','?','0','7','0'},
    {'7','0',';','0','@','0','3','0','5','0','9','0','2','0',':','0'},
    {':','0','3','0','9','0',';','0','2','0','<','0','4','0','=','0'},
    
    {';','0','=','0','1','0','7','0','?','0','6','0','5','0','<','0'},
    {'?','0','7','0','<','0','6','0','1','0','@','0',';','0','9','0'},
    {'8','0','5','0','=','0','@','0','>','0','<','0','7','0','4','0'},
    {'9','0','<','0',';','0','4','0','7','0','3','0','=','0','6','0'}
};


static char test_board_full_16[16][16] = {
    {'2',';','9','5','8','@','=','4','<','3','>','7',':','6','?','1'},
    {'4','<','?',';','3','6','9',';','=','5','8','1','@','7','>','2'},
    {'1','>','6','7','?','2','5','<',';','9',':','@','3','=','8','4'},
    {'@','=','8','3','>','1',':','7','4','6','2','?','9',';','5','<'},
    {'<','2','@','9',':','>','?','=','8','1','5','3','6','4',';','7'},
    {'6','7','1',';','5','<','8','@','9','?','4','2','>',';','3','='},
    {'>','5','4','=','6',';','1','3','@','<','7',':','8','9','2','?'},
    {'3','8',':','?','4','7','2','9','6','>','=',';','1','<','@','5'},
    {'=','9','2','@','7','8','>',';','3','4','?','6','<','5','1',';'},
    {'5','4','>','6','2','=','<','1',':','@',';','8','?','3','7','9'},
    {'7','1',';','<','@','4','3','?','5','=','9','>','2','8',':','6'},
    {':','?','3','8','9','5',';','6','2','7','<','1','4','>','=','@'},
    {';',';','=','>','1','9','7','8','?','2','6','4','5','@','<','3'},
    {'?','3','7','4','<',':','6','5','1','8','@','=',';','2','9','>'},
    {'8','6','5','1','=','3','@','2','>',';','<','9','7','?','4',':'},
    {'9','@','<','2',';','?','4','>','7',':','3','5','=','1','6','8'}
};

static char test_board_empty_25[25][25] = {
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
};

static char test_board_partial_25[25][25] = {
    {'1','0','4','0','I','0','C','0','A','0','E','0','B','0','F','0','<','0','3','0','2','0','=','0','5'},
    {'5','0','C','0','H','0','F','0','9','0','@','0','7','0','A','0','E','0','>','0',':','0','4','0','?'},
    {'A','0','6','0','I','0','5','0','D','0',':','0','1','0','4','0','H','0','?','0','<','0','F','0','9'},
    {'@','0','E','0','<','0','2','0',';','0','5','0','?','0','<','0','D','0','F','0','9','0','I','0','3'},
    {':','0','?','0','F','0','1','0','6','0','G','0','I','0','3','0','5','0',';','0','8','0','D','0','A'},
    {'<','0',';','0','6','0','=','0','H','0','7','0','8','0','E','0','C','0','4','0','F','0','2','0','B'},
    {'8','0','=','0','9','0','4','0','<','0','?','0','5','0','D','0','A','0','B','0','1','0','7','0','6'},
    {'4','0','>','0','7','0','3','0','E','0','I','0','G','0','=','0','@','0','5','0','@','0',';','0','<'},
    {'F','0','H','0','G','0','D','0','1','0',':','0','4','0','>','0','2','0','5','0','C','0','I','0','9'},
    {'D','0','2','0','5','0','8','0','>','0','9','0','<','0','C','0','1','0','7','0','3','0','E','0','4'},
    {'=','0','3','0',':','0','G','0','4','0','F','0','A','0','H','0','7','0','9','0','<','0','6','0',';'},
    {'>','0','1','0','<','0','@','0','?','0','2','0','D','0',':','0','4','0','A','0','E','0','5','0','F'},
    {'7','0',';','0','D','0','E','0','9','0','4','0','<','0','2','0','>','0','5','0','=','0',':','0','B'},
    {'2','0','9','0',';','0',':','0','8','0','>','0','3','0','<','0','B','0','G','0','4','0','3','0','D'},
    {'6','0','D','0','4','0','<','0','5','0','B','0','G','0','9','0','2','0','I','0','7','0','H','0','>'},
    {'E','0','<','0','@','0',':','0','3','0','H','0','9','0',';','0','6','0','>','0','8','0','5','0','C'},
    {'9','0','8','0','1','0','I','0','D','0','A','0','3','0','B','0','@','0','5','0',';','0','?','0',':'},
    {'G','0','F','0','?','0','5','0','>','0','6','0','@','0',';','0','1','0','=','0','4','0','C','0','H'},
    {'I','0','6','0',';','0','1','0','8','0','=','0','C','0',':','0','<','0','D','0','B','0','@','0','A'},
    {'3','0','A','0','C','0','?','0','G','0',';','0','I','0','5','0','E','0','8','0','7','0','1','0','='},
    {'C','0','G','0','?','0','I','0','>','0','3','0','=','0',':','0','5','0','H','0','<','0','E','0','B'},
    {'?','0','5','0','>','0','7','0','C','0','D','0',';','0','I','0','9','0','<','0','B','0','6','0','1'},
    {';','0','7','0','D','0','6','0','2','0','H','0','=','0','1','0','I','0','8','0','>','0','9','0',':'},
    {'B','0','I','0','2','0','>','0','=','0','4','0','E','0','5','0','G','0','6','0','?','0','8','0','3'},
    {'H','0',':','0','=','0','9','0','@','0','C','0','6','0','8','0','>','0','2','0','G','0',';','0','1'}
};

static char test_board_full_25[25][25] = {
    {'7','G','5','?','4','B',';','I','<','E','F','H','D','9',':','1','C','3','8','=','A','6','>','2','@'},
    {'<','C','9','2','@','F','3','1',':','8','E','=','5','B','I','A','7','6','G','>','D','?','4','H',';'},
    {'3','D','6','B','H','7','5','G','=','A','C','?','>',';','1','4','F','@','9','2','I','8','<',':','E'},
    {'A','=','>','E','F','6','@','?','D','H','<','3','2','4','8','I','5',':','B',';','9','7','1','C','G'},
    {'8','I','1',':',';','2','C','4','9','>','G','6','7','@','A','E','?','H','D','<','5','F','B','3','='},
    {'H','7',';','4','G','@','F','8','2','?','6','E','C','3','D','=','A','<','I','1','>','B','9','5',':'},
    {'?',';','F','5','9','<','E','=','C','I','@','B','H','G',';','6','4','>','3','7','2','1','D','8','A'},
    {'D','8','@','I','<','>','4','6','7','B','A','F','=','1','2','5','G','9','H',':','?','3',';','E','C'},
    {'C','3','E','>','=','G','D',';','A','1',':','7','9','?','5','8','B','F','2','@','4','I','H','6','<'},
    {'B','2','A','1','6','9',':','3','H','5','>','8','4','I','<','?','D',';','C','E','7','@','G','=','F'},
    {'5','<','I','H','>','E','1','C','4','6','D','G','3','8','?','@','2','B','7','F',':','A','=',';','9'},
    {'6','1','B','=','A','D','G','H','@','2',';','I','E',':','7','9','<','8','5','4','3','>','C','F','?'},
    {'F','?',';','D','E','I','B','5','8','=','1','@','<','>','9','H','3','C',';','A','G','2','6','4','7'},
    {'2',';','3','@','8','A','7','F','>','9','4','C','B','H','=','G',':','?','1','6','<','D','E','I','5'},
    {'4','9','C','G','7',':','?','<',';','3','5','2','F','A','6','D','>','=','E','I','B','H','8','@','1'},
    {'9','@','2','A','3',';','6','D','E','F','7','4','?','C','B','>','I','5','=','H','1','G',':','<','8'},
    {'I','4','8','6','1','?','A','@','3','C','9','D',';','<','F','B','E','7',':','G','H','=','5','>','2'},
    {';','F','D','C','?','=','2','>','G','<','I','1',':','5','H','3','8','A','6','9','E','4','@','7','B'},
    {':','H','G','<','B','5','9','7','I','4','=','>','8','2','E','F','1','D','@','C','6',';','A','?','3'},
    {'E','>','=','7','5','H','8','B','1',':','3','A','@','6','G','<',';','2','4','?','C','9','F','D','I'},
    {'G','B','?','8','C','3','<','E','5',';','2','9','6','F','>','7','@','4','A','D','=',':','I','1','H'},
    {'=','E','<','3','2','1','>','9','6','7','B',';','G','D','C',':','H','I','F','8','@','5','?','A','4'},
    {'@','6','4','9','I','C','H','A','B','D','8',':','1','7','3',';','=','E','?','5','F','<','2','G','>'},
    {'1','5','7','F',':','8','I','2','?','@','H','<','A','=','4','C','6','G','>','B',';','E','3','9','D'},
    {'>','A','H',';','D','4','=',':','F','G','?','5','I','E','@','2','9','1','<','3','8','C','7','B','6'}

};

void test_unassigned(){
    int N = 9;
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_full_9), 0);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_partial_9), 51);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_empty_9), 81);

    N = 16;
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_full_16), 0);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_partial_16), 128);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_empty_16), 256);

    N = 25;
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_full_25), 0);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_partial_25), 300);
    CU_ASSERT_EQUAL(count_unassigned(N, test_board_empty_25), 625);
}

void test_set_destroy_unassigned(){
    int N = 9;
    int n_unassigned = count_unassigned(N, test_board_partial_9);
    unAssigned_t **unassigned = set_unassigned(N, test_board_partial_9, n_unassigned);
    CU_ASSERT_PTR_NOT_NULL(unassigned);
    //First unassigned cell is at (0,2)
    CU_ASSERT_EQUAL(unassigned[0]->x, 2);
    CU_ASSERT_EQUAL(unassigned[0]->y, 0);
    //Last unassigned cell is at (8,6)
    CU_ASSERT_EQUAL(unassigned[n_unassigned-1]->x, 6);
    CU_ASSERT_EQUAL(unassigned[n_unassigned-1]->y, 8);
    destroy_unassigned(unassigned, n_unassigned);

    N = 16;
    n_unassigned = count_unassigned(N, test_board_partial_16);
    unAssigned_t **unassigned16 = set_unassigned(N, test_board_partial_16, n_unassigned);
    CU_ASSERT_PTR_NOT_NULL(unassigned16);
    //First unassigned cell is at (0,1)
    CU_ASSERT_EQUAL(unassigned16[0]->x, 1);
    CU_ASSERT_EQUAL(unassigned16[0]->y, 0);
    //Last unassigned cell is at (15,15)
    CU_ASSERT_EQUAL(unassigned16[n_unassigned-1]->x, 15);
    CU_ASSERT_EQUAL(unassigned16[n_unassigned-1]->y, 15);
    destroy_unassigned(unassigned16, n_unassigned);

    N = 25;
    n_unassigned = count_unassigned(N, test_board_partial_25);
    unAssigned_t **unassigned25 = set_unassigned(N, test_board_partial_25, n_unassigned);
    CU_ASSERT_PTR_NOT_NULL(unassigned25);
    //First unassigned cell is at (0,1)
    CU_ASSERT_EQUAL(unassigned25[0]->x, 1);
    CU_ASSERT_EQUAL(unassigned25[0]->y, 0);
    //Last unassigned cell is at (24,23)
    CU_ASSERT_EQUAL(unassigned25[n_unassigned-1]->x, 23);
    CU_ASSERT_EQUAL(unassigned25[n_unassigned-1]->y, 24);
    destroy_unassigned(unassigned25, n_unassigned);
}


void test_set_possibilities(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(possibilities[3][4], "123456789", 9));

    set_possibilities(N, sqrt_N, test_board_partial_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(possibilities[0][2], "120400000", 9));

    set_possibilities(N, sqrt_N, test_board_full_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(possibilities[5][5], "000000000", 9));

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(possibilities16[7][12], "123456789:;<=>?@ABCD", 16));

    set_possibilities(N, sqrt_N, test_board_partial_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(possibilities16[0][0], "0000000000000000ABCD", 16));

    set_possibilities(N, sqrt_N, test_board_full_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(possibilities16[10][10], "0000000000000000", 16));

    N = 25;
    sqrt_N = 5;
    char possibilities25[N][N][N];
    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(possibilities25[12][20], "123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ", 25));

    set_possibilities(N, sqrt_N, test_board_partial_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(possibilities25[0][0], "0000000000000000000000000ABCDEFGHIJKLMNOPQRSTUVWXYZ", 25));

    set_possibilities(N, sqrt_N, test_board_full_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(possibilities25[20][20], "0000000000000000000000000", 25));
}
    
void test_update_possibilities(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];
    char temp_possibilities[N][N][N];
    
    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    memcpy(temp_possibilities, possibilities, sizeof(possibilities));
    test_board_empty_9[0][0] = '1'; //Set cell (0,0) to 1
    update_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities, possibilities, sizeof(possibilities)));
    test_board_empty_9[0][0] = '0'; //Reset cell (0,0) to 0

    set_possibilities(N, sqrt_N, test_board_partial_9, possibilities);
    memcpy(temp_possibilities, possibilities, sizeof(possibilities));
    test_board_partial_9[0][2] = '4'; //Set cell (0,2) to 4
    update_possibilities(N, sqrt_N, test_board_partial_9, possibilities);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities, possibilities, sizeof(possibilities)));
    test_board_partial_9[0][2] = '0'; //Reset cell (0,2) to 0

    set_possibilities(N, sqrt_N, test_board_full_9, possibilities);
    memcpy(temp_possibilities, possibilities, sizeof(possibilities));
    test_board_full_9[8][8] = '0'; //Set cell (8,8) to 0
    update_possibilities(N, sqrt_N, test_board_full_9, possibilities);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities, possibilities, sizeof(possibilities)));
    test_board_full_9[8][8] = '9'; //Reset cell (8,8) to 9

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    char temp_possibilities16[N][N][N];
    
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    memcpy(temp_possibilities16, possibilities16, sizeof(possibilities16));
    test_board_empty_16[0][0] = '1'; //Set cell (0,0) to 1
    update_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities16, possibilities16, sizeof(possibilities16)));
    test_board_empty_16[0][0] = '0'; //Reset cell (0,0) to 0

    set_possibilities(N, sqrt_N, test_board_partial_16, possibilities16);
    memcpy(temp_possibilities16, possibilities16, sizeof(possibilities16));
    test_board_partial_16[0][1] = '2'; //Set cell (0,0) to 2
    update_possibilities(N, sqrt_N, test_board_partial_16, possibilities16);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities16, possibilities16, sizeof(possibilities16)));
    test_board_partial_16[0][1] = '0'; //Reset cell (0,1) to 0

    set_possibilities(N, sqrt_N, test_board_full_16, possibilities16);
    memcpy(temp_possibilities16, possibilities16, sizeof(possibilities16));
    test_board_full_16[15][15] = '0'; //Set cell (15,15) to 0
    update_possibilities(N, sqrt_N, test_board_full_16, possibilities16);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities16, possibilities16, sizeof(possibilities16)));
    test_board_full_16[15][15] = '8'; //Reset cell (15,15) to 8

    N = 25;
    sqrt_N = 5;
    char possibilities25[N][N][N];
    char temp_possibilities25[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    memcpy(temp_possibilities25, possibilities25, sizeof(possibilities25));
    test_board_empty_25[0][0] = '1'; //Set cell (0,0) to 1
    update_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities25, possibilities25, sizeof(possibilities25)));
    test_board_empty_25[0][0] = '0'; //Reset cell (0,0) to 0

    set_possibilities(N, sqrt_N, test_board_partial_25, possibilities25);
    memcpy(temp_possibilities25, possibilities25, sizeof(possibilities25));
    test_board_partial_25[0][0] = '2'; //Set cell (0,0) to 2
    update_possibilities(N, sqrt_N, test_board_partial_25, possibilities25);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities25, possibilities25, sizeof(possibilities25)));
    test_board_partial_25[0][0] = '1'; //Reset cell (0,0) to 1

    set_possibilities(N, sqrt_N, test_board_full_25, possibilities25);
    memcpy(temp_possibilities25, possibilities25, sizeof(possibilities25));
    test_board_full_25[24][24] = '0'; //Set cell (24,24) to 0
    update_possibilities(N, sqrt_N, test_board_full_25, possibilities25);
    CU_ASSERT_NOT_EQUAL(0, memcmp(temp_possibilities25, possibilities25, sizeof(possibilities25)));
    test_board_full_25[24][24] = '6'; //Reset cell (24,24) to 6
}    

void test_the_lucky_one(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];
    char temp_board[9][9];
    
    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    memcpy(temp_board, test_board_empty_9, sizeof(test_board_empty_9));
    the_lucky_one(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_board, test_board_empty_9, sizeof(test_board_empty_9)));


    memcpy(temp_board, test_board_full_9, sizeof(test_board_full_9));
    test_board_full_9[3][7] = '0'; //Set cell (3,7) to 0
    set_possibilities(N, sqrt_N, test_board_full_9, possibilities);
    the_lucky_one(N, sqrt_N, test_board_full_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_board, test_board_full_9, sizeof(test_board_full_9)));

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    char temp_board16[16][16];
    
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    memcpy(temp_board16, test_board_empty_16, sizeof(test_board_empty_16));
    the_lucky_one(N, sqrt_N, test_board_empty_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_board16, test_board_empty_16, sizeof(test_board_empty_16)));

    memcpy(temp_board16, test_board_full_16, sizeof(test_board_full_16));
    test_board_full_16[5][10] = '0'; //Set cell (5,10) to 0
    set_possibilities(N, sqrt_N, test_board_full_16, possibilities16);
    the_lucky_one(N, sqrt_N, test_board_full_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_board16, test_board_full_16, sizeof(test_board_full_16)));

    N = 25;
    sqrt_N = 5;
    char possibilities25[N][N][N];
    char temp_board25[25][25];

    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    memcpy(temp_board25, test_board_empty_25, sizeof(test_board_empty_25));
    the_lucky_one(N, sqrt_N, test_board_empty_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(temp_board25, test_board_empty_25, sizeof(test_board_empty_25)));

    memcpy(temp_board25, test_board_full_25, sizeof(test_board_full_25));
    test_board_full_25[12][20] = '0'; //Set cell (12,20) to 0
    set_possibilities(N, sqrt_N, test_board_full_25, possibilities25);
    the_lucky_one(N, sqrt_N, test_board_full_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(temp_board25, test_board_full_25, sizeof(test_board_full_25)));

}

void test_the_easy_one(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];
    char temp_board[9][9];

    memcpy(temp_board, test_board_empty_9, sizeof(test_board_empty_9));
    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    the_easy_one(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_board, test_board_empty_9, sizeof(test_board_empty_9)));

    memcpy(temp_board, test_board_full_9, sizeof(test_board_full_9));
    test_board_full_9[1][1] = '0'; //Set cell (1,1) to 0
    test_board_full_9[1][4] = '0'; //Set cell (1,4) to 0
    test_board_full_9[1][7] = '0'; //Set cell (1,7) to 0
    set_possibilities(N, sqrt_N, test_board_full_9, possibilities);
    the_easy_one(N, sqrt_N, test_board_full_9, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_board, test_board_full_9, sizeof(test_board_full_9)));

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    char temp_board16[16][16];
    
    memcpy(temp_board16, test_board_empty_16, sizeof(test_board_empty_16));
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    the_easy_one(N, sqrt_N, test_board_empty_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_board16, test_board_empty_16, sizeof(test_board_empty_16)));

    memcpy(temp_board16, test_board_full_16, sizeof(test_board_full_16));
    test_board_full_16[2][2] = '0'; //Set cell (2,2) to 0
    test_board_full_16[2][5] = '0'; //Set cell (2,5) to 0
    test_board_full_16[2][8] = '0'; //Set cell (2,8) to 0
    set_possibilities(N, sqrt_N, test_board_full_16, possibilities16);
    the_easy_one(N, sqrt_N, test_board_full_16, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_board16, test_board_full_16, sizeof(test_board_full_16)));

    N = 25;
    sqrt_N = 5;
    char possibilities25[N][N][N];
    char temp_board25[25][25];

    memcpy(temp_board25, test_board_empty_25, sizeof(test_board_empty_25));
    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    the_easy_one(N, sqrt_N, test_board_empty_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(temp_board25, test_board_empty_25, sizeof(test_board_empty_25)));

    memcpy(temp_board25, test_board_full_25, sizeof(test_board_full_25));
    test_board_full_25[3][3] = '0'; //Set cell (3,3) to 0
    test_board_full_25[3][8] = '0'; //Set cell (3,8) to 0
    test_board_full_25[3][13] = '0'; //Set cell (3,13) to 0
    set_possibilities(N, sqrt_N, test_board_full_25, possibilities25);
    the_easy_one(N, sqrt_N, test_board_full_25, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(temp_board25, test_board_full_25, sizeof(test_board_full_25)));
}

void test_pairs(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];
    char temp_possibilities[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    memcpy(temp_possibilities, possibilities, sizeof(possibilities));
    pairs(N, sqrt_N, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_possibilities, possibilities, sizeof(possibilities)));

    test_board_empty_9[1][0] = '1';
    test_board_empty_9[1][1] = '2';
    test_board_empty_9[2][0] = '1';
    test_board_empty_9[2][1] = '2';
    test_board_empty_9[3][3] = '1';
    test_board_empty_9[4][3] = '2';
    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities[0][4], "120000000", 9));
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities[0][5], "120000000", 9));
    pairs(N, sqrt_N, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(possibilities[0][4], "120000000", 9));
    CU_ASSERT_EQUAL(0, memcmp(possibilities[0][5], "120000000", 9));
    test_board_empty_9[1][0] = '0';
    test_board_empty_9[1][1] = '0';
    test_board_empty_9[2][0] = '0';
    test_board_empty_9[2][1] = '0';
    test_board_empty_9[3][3] = '0';
    test_board_empty_9[4][3] = '0';

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    char temp_possibilities16[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    memcpy(temp_possibilities16, possibilities16, sizeof(possibilities16));
    pairs(N, sqrt_N, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_possibilities16, possibilities16, sizeof(possibilities16)));

    test_board_empty_16[1][0] = '1';
    test_board_empty_16[1][1] = '2';
    test_board_empty_16[2][0] = '1';
    test_board_empty_16[2][1] = '2';
    test_board_empty_16[3][0] = '1';
    test_board_empty_16[3][1] = '2';
    test_board_empty_16[4][4] = '1';
    test_board_empty_16[5][4] = '2';
    test_board_empty_16[4][5] = '1';
    test_board_empty_16[5][5] = '2';
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities16[0][6], "1200000000000000", 16));
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities16[0][7], "1200000000000000", 16));
    pairs(N, sqrt_N, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(possibilities16[0][6], "1200000000000000", 16));
    CU_ASSERT_EQUAL(0, memcmp(possibilities16[0][7], "1200000000000000", 16));
    test_board_empty_16[1][0] = '0';
    test_board_empty_16[1][1] = '0';
    test_board_empty_16[2][0] = '0';
    test_board_empty_16[2][1] = '0';
    test_board_empty_16[3][0] = '0';
    test_board_empty_16[3][1] = '0';
    test_board_empty_16[4][4] = '0';
    test_board_empty_16[5][4] = '0';
    test_board_empty_16[4][5] = '0';
    test_board_empty_16[5][5] = '0';
}

void test_lines(){
    int N = 9;
    int sqrt_N = 3;
    char possibilities[N][N][N];
    char temp_possibilities[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    memcpy(temp_possibilities, possibilities, sizeof(possibilities));
    lines(N, sqrt_N, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(temp_possibilities, possibilities, sizeof(possibilities)));

    test_board_empty_9[0][0] = '1';
    test_board_empty_9[0][1] = '2';
    test_board_empty_9[1][0] = '3';
    test_board_empty_9[1][1] = '4';
    test_board_empty_9[2][0] = '5';
    test_board_empty_9[2][1] = '6';
    set_possibilities(N, sqrt_N, test_board_empty_9, possibilities);
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities[3][2], "123456000", 9));
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities[4][2], "123456000", 9));
    CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities[5][2], "123456000", 9));
    lines(N, sqrt_N, possibilities);
    CU_ASSERT_EQUAL(0, memcmp(possibilities[3][2], "123456000", 9));
    CU_ASSERT_EQUAL(0, memcmp(possibilities[4][2], "123456000", 9));
    CU_ASSERT_EQUAL(0, memcmp(possibilities[5][2], "123456000", 9));
    test_board_empty_9[0][0] = '0';
    test_board_empty_9[1][0] = '0';
    test_board_empty_9[0][1] = '0';
    test_board_empty_9[1][1] = '0';
    test_board_empty_9[2][0] = '0';
    test_board_empty_9[2][1] = '0';

    N = 16;
    sqrt_N = 4;
    char possibilities16[N][N][N];
    char temp_possibilities16[N][N][N];

    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    memcpy(temp_possibilities16, possibilities16, sizeof(possibilities16));
    lines(N, sqrt_N, possibilities16);
    CU_ASSERT_EQUAL(0, memcmp(temp_possibilities16, possibilities16, sizeof(possibilities16)));

    char test_values[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {':', ';', '<'}
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            test_board_empty_16[i][j] = test_values[i][j];
        }
    }
    set_possibilities(N, sqrt_N, test_board_empty_16, possibilities16);
    for (int i = 4; i < 8; i++) {
        CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities16[i][3], "123456789:;<0000", 16));
    }
    lines(N, sqrt_N, possibilities16);
    for (int i = 4; i < 8; i++) {
        CU_ASSERT_EQUAL(0, memcmp(possibilities16[i][3], "123456789:;<0000", 16));
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            test_board_empty_16[i][j] = '0';
        }
    }

    N = 25;
    sqrt_N = 5;
    char possibilities25[N][N][N];
    char temp_possibilities25[N][N][N];
    char temp_board25[N][N];
    memcpy(temp_board25, test_board_empty_25, sizeof(test_board_empty_25));


    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    memcpy(temp_possibilities25, possibilities25, sizeof(possibilities25));
    lines(N, sqrt_N, possibilities25);
    CU_ASSERT_EQUAL(0, memcmp(temp_possibilities25, possibilities25, sizeof(possibilities25)));
    char test_values25[5][4] = {
        {'1', '2', '3', '4'},
        {'5', '6', '7', '8'},
        {'9', ':', ';', '<'},
        {'=', '>', '?', '@'},
        {'A', 'B', 'C', 'D'}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            test_board_empty_25[i][j] = test_values25[i][j];
        }
    }
    set_possibilities(N, sqrt_N, test_board_empty_25, possibilities25);
    for (int i = 5; i < 10; i++) {
        CU_ASSERT_NOT_EQUAL(0, memcmp(possibilities25[i][4], "123456789:;<=>?@ABCD00000", 25));
    }
    lines(N, sqrt_N, possibilities25);
    for (int i = 5; i < 10; i++) {
        CU_ASSERT_EQUAL(0, memcmp(possibilities25[i][4], "123456789:;<=>?@ABCD00000", 25));
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            test_board_empty_25[i][j] = '0';
        }
    }
}

void test_copy_board(){
    int N = 9;
    char temp_board[9][9];
    copy_board(N, test_board_partial_9, temp_board);
    CU_ASSERT_EQUAL(0, memcmp(temp_board, test_board_partial_9, sizeof(test_board_partial_9)));

    N = 16;
    char temp_board16[16][16];
    copy_board(N, test_board_partial_16, temp_board16);
    CU_ASSERT_EQUAL(0, memcmp(temp_board16, test_board_partial_16, sizeof(test_board_partial_16)));

    N = 25;
    char temp_board25[25][25];
    copy_board(N, test_board_partial_25, temp_board25);
    CU_ASSERT_EQUAL(0, memcmp(temp_board25, test_board_partial_25, sizeof(test_board_partial_25)));
}
/**************************************************************/
/********************** Set board *****************************/
/**************************************************************/
void test_set_board_txt(){
    int N = 9;
    char board[9][9];
    set_numbers(N, board, "/home/oskar/Programming/Maintenance/tests/test_input/9x9_empty.txt");
    CU_ASSERT_EQUAL(0, memcmp(board, test_board_empty_9, sizeof(test_board_empty_9)));
    set_numbers(N, board, "/home/oskar/Programming/Maintenance/tests/test_input/9x9_partial.txt");
    CU_ASSERT_EQUAL(0, memcmp(board, test_board_partial_9, sizeof(test_board_partial_9)));
    set_numbers(N, board, "/home/oskar/Programming/Maintenance/tests/test_input/9x9_full.txt");
    CU_ASSERT_EQUAL(0, memcmp(board, test_board_full_9, sizeof(test_board_full_9)));

    N = 16;
    char board16[16][16];
    set_numbers(N, board16, "/home/oskar/Programming/Maintenance/tests/test_input/16x16_empty.txt");
    CU_ASSERT_EQUAL(0, memcmp(board16, test_board_empty_16, sizeof(test_board_empty_16)));
    set_numbers(N, board16, "/home/oskar/Programming/Maintenance/tests/test_input/16x16_partial.txt");
    CU_ASSERT_EQUAL(0, memcmp(board16, test_board_partial_16, sizeof(test_board_partial_16)));
    set_numbers(N, board16, "/home/oskar/Programming/Maintenance/tests/test_input/16x16_full.txt");
    CU_ASSERT_EQUAL(0, memcmp(board16, test_board_full_16, sizeof(test_board_full_16)));

    N = 25;
    char board25[25][25];
    set_numbers(N, board25, "/home/oskar/Programming/Maintenance/tests/test_input/25x25_empty.txt");
    CU_ASSERT_EQUAL(0, memcmp(board25, test_board_empty_25, sizeof(test_board_empty_25)));
    set_numbers(N, board25, "/home/oskar/Programming/Maintenance/tests/test_input/25x25_partial.txt");
    CU_ASSERT_EQUAL(0, memcmp(board25, test_board_partial_25, sizeof(test_board_partial_25)));
    set_numbers(N, board25, "/home/oskar/Programming/Maintenance/tests/test_input/25x25_full.txt");
    CU_ASSERT_EQUAL(0, memcmp(board25, test_board_full_25, sizeof(test_board_full_25)));
}

/***************************************************************/
/****************************** Utils **************************/
/***************************************************************/
void test_duplicate_in_row(){
    int N = 9;
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_partial_9, 0, 3));
    test_board_partial_9[0][3] = '5'; //Introduce a duplicate in row 0
    CU_ASSERT_TRUE(duplicate_numbers_in_row(N, test_board_partial_9, 0, 3));
    test_board_partial_9[0][3] = '0'; //Reset cell (0,3) to 0

    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '1'; //Introduce a number in row 0
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '0';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_full_9, 0, 0));
    
    N = 16;
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_partial_16, 0, 2));
    test_board_partial_16[0][2] = '8'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_row(N, test_board_partial_16, 0, 2));
    test_board_partial_16[0][2] = '0'; 

    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_full_16, 0, 0));
    
    N = 25;
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_partial_25, 0, 1));
    test_board_partial_25[0][1] = '4'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_row(N, test_board_partial_25, 0, 1));
    test_board_partial_25[0][1] = '0';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_row(N, test_board_full_25, 0, 0));
}

void test_duplicate_in_column(){
    int N = 9;
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_partial_9, 0, 0));
    test_board_partial_9[8][0] = '5'; //Introduce a duplicate in row 0
    CU_ASSERT_TRUE(duplicate_numbers_in_col(N, test_board_partial_9, 0, 0));
    test_board_partial_9[8][0] = '0'; //Reset cell (0,3) to 0

    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '1'; //Introduce a number in row 0
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '0';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_full_9, 0, 0));
    
    N = 16;
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_partial_16, 0, 0));
    test_board_partial_16[15][0] = '2'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_col(N, test_board_partial_16, 0, 0));
    test_board_partial_16[15][0] = '9'; 

    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_full_16, 0, 0));
    
    N = 25;
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_partial_25, 0, 0));
    test_board_partial_25[24][0] = '1'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_col(N, test_board_partial_25, 0, 0));
    test_board_partial_25[24][0] = 'H';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_col(N, test_board_full_25, 0, 0));
}

void test_duplicate_in_box(){
    int N = 9;
    int sqrt_N = 3;
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_9, 0, 0));
    test_board_partial_9[1][2] = '5'; //Introduce a duplicate in row 0
    CU_ASSERT_TRUE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_9, 0, 0));
    test_board_partial_9[1][2] = '0'; //Reset cell (0,3) to 0

    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '1'; //Introduce a number in row 0
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_9, 0, 0));
    test_board_empty_9[0][0] = '0';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_full_9, 0, 0));
    
    N = 16;
    sqrt_N = 4;
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_16, 0, 0));
    test_board_partial_16[1][3] = '2'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_16, 0, 0));
    test_board_partial_16[1][3] = '0'; 

    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_16, 0, 0));
    test_board_empty_16[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_full_16, 0, 0));
    
    N = 25;
    sqrt_N = 5;
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_25, 0, 0));
    test_board_partial_25[1][4] = '1'; //Introduce a duplicate
    CU_ASSERT_TRUE(duplicate_numbers_in_box(N, sqrt_N, test_board_partial_25, 0, 0));
    test_board_partial_25[1][4] = '0';
    
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '1'; //Introduce a number
    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_empty_25, 0, 0));
    test_board_empty_25[0][0] = '0';

    CU_ASSERT_FALSE(duplicate_numbers_in_box(N, sqrt_N, test_board_full_25, 0, 0));
}

void test_check_entire_board(){
    int N = 9;
    CU_ASSERT_FALSE(check_entire_board(N, test_board_empty_9));
    CU_ASSERT_FALSE(check_entire_board(N, test_board_partial_9));
    CU_ASSERT_TRUE(check_entire_board(N, test_board_full_9));

    N = 16;
    CU_ASSERT_FALSE(check_entire_board(N, test_board_empty_16));
    CU_ASSERT_FALSE(check_entire_board(N, test_board_partial_16));
    CU_ASSERT_TRUE(check_entire_board(N, test_board_full_16));

    N = 25;
    CU_ASSERT_FALSE(check_entire_board(N, test_board_empty_25));
    CU_ASSERT_FALSE(check_entire_board(N, test_board_partial_25));
    CU_ASSERT_TRUE(check_entire_board(N, test_board_full_25));

}

///////////////////////////////////////////////////////////////////
int main(){
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite logical_test_suite = CU_add_suite("Logical solver tests", init_suite, clean_suite);
    if ((logical_test_suite == NULL)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(logical_test_suite, "Count unassigned cells", test_unassigned) == NULL) ||
        (CU_add_test(logical_test_suite, "Set and destroy unassigned cells", test_set_destroy_unassigned) == NULL) ||
        (CU_add_test(logical_test_suite, "Set possibilities for each cell", test_set_possibilities) == NULL) ||
        (CU_add_test(logical_test_suite, "Update possibilities after setting a cell", test_update_possibilities) == NULL) ||
        (CU_add_test(logical_test_suite, "The lucky one technique", test_the_lucky_one) == NULL) ||
        (CU_add_test(logical_test_suite, "The easy one technique", test_the_easy_one) == NULL) ||
        (CU_add_test(logical_test_suite, "Pairs technique", test_pairs) == NULL) ||
        (CU_add_test(logical_test_suite, "Lines technique", test_lines) == NULL) ||
        (CU_add_test(logical_test_suite, "Copy board", test_copy_board) == NULL) ||
        0)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite set_board_test_suite = CU_add_suite("Set board tests", init_suite, clean_suite);
    if ((set_board_test_suite == NULL)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(set_board_test_suite, "Set board from .txt file", test_set_board_txt) == NULL) ||
        0)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite utils_test_suite = CU_add_suite("Utils tests", init_suite, clean_suite);
    if ((utils_test_suite == NULL)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(utils_test_suite, "Duplicate numbers in a row", test_duplicate_in_row) == NULL) ||
        (CU_add_test(utils_test_suite, "Duplicate numbers in a column", test_duplicate_in_column) == NULL) ||
        (CU_add_test(utils_test_suite, "Duplicate numbers in a box", test_duplicate_in_box) == NULL) ||
        (CU_add_test(utils_test_suite, "Check entire board for duplicates", test_check_entire_board) == NULL) ||
        0)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}