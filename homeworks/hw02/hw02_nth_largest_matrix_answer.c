#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "test_matrix.dat"
#define uint32_t u_int32_t

int  arg_test(int argc, char **argv);
void load_data(int ***int_array, uint32_t *row, uint32_t *col);
void find_nth(int **int_array, uint32_t row, uint32_t col, int n, int *ret_arr);
void print_matrix(uint32_t row, uint32_t col, int **arr);

int main(int argc, char **argv)
{
    int valid = arg_test(argc, argv);
    
    int nth = -3;
 
    if(valid) {
        int **int_array = NULL;
        uint32_t row = 0;
        uint32_t col = 0;
        load_data(&int_array, &row, &col);
        int *ret_array = (int*) malloc(sizeof(int) * col);
        // This function prints the content of the matrix - debugging tool
        print_matrix(row, col, int_array);

        // Insert your code here (1)
        int n = -1;

        // ------------------------

        find_nth(int_array, row, col, n, ret_array);
        printf("---- Answer ----\n");
        for(int i = 0; i < col; i++) {
            printf("%d ", ret_array[i]);
        }
        printf("\n");
        printf("--------\n");

    } else {
        // Do nothing
    }
    
    return 0;
}



int arg_test(int argc, char **argv)
{
    int return_val = 0;
    if(argc < 2) {
        fprintf(stderr, "Error: no input entered\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else if(argc > 2) {
        fprintf(stderr, "Error: too many inputs\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else {
        return_val = 1;
    }
    return return_val;
}

void load_data(int ***int_array, uint32_t *row, uint32_t *col)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int r = 0;
    int c = 0;
    fscanf(fp, "%d", &r);
    fscanf(fp, "%d", &c);

    int cnt = 0;
    int tmp = 0;
    while(fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
    }
    fclose(fp);

    if(r * c == cnt) {
        printf("This is a %d x %d matrix\n", r, c);
    } else {
        printf("Dimension and number of integers do not match: %d x %d = %d!\n",
               r, c, cnt);
        exit(0);
    }

    int **tmp_array = (int**) malloc(sizeof(int*) * r);
    for(int i = 0; i < r; i++) {
        tmp_array[i] = (int*) malloc(sizeof(int) * c);
    }

    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &tmp);
    fscanf(fp, "%d", &tmp);
 
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        tmp_array[cnt / c][cnt % c] = tmp;
        cnt++;
    }
    fclose(fp);
    
    *int_array = tmp_array;
    *row = r;
    *col = c;
}

// Given n as input, find the nth largest value
// in each column of the matrix.
// If n is larger than the number of rows,
// return -1.
// Return -2 for any other errors.
// NOTE 1:
// The file used for grading will be different from
// the file given with the homework - it will have
// different sized matrix with different values.
void find_nth(int **int_array, uint32_t row, uint32_t col, int n, int *ret_arr)
{
   // Insert your code here (2)



   // -------------------------
}

void print_matrix(uint32_t row, uint32_t col, int **arr)
{
    printf("---- Print Array ----\n");
    printf("This matrix is %d x %d\n", row, col);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col;j ++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("--------\n\n");
}

