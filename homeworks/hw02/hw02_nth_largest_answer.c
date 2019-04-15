#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "test.dat"

#define uint32_t u_int32_t

int  arg_test(int argc, char **argv);
void conversion_test();
void load_data(int **int_array, uint32_t *array_size);
int  find_nth(int *int_array, uint32_t array_size, int n);
void print_array(uint32_t size, int *arr);

int main(int argc, char **argv)
{
    int valid = arg_test(argc, argv);
    // Test function for atoi
    // conversion_test(argc, argv);
    
    int nth = -3;
 
    if(valid) {
        int *int_array = NULL;
        uint32_t array_size = 0;
        load_data(&int_array, &array_size);

        // This function prints the content of the array - debugging tool
        // print_array(array_size, int_array);

        // Insert your code here (1)
        // Get value of n
        int n = atoi(argv[1]);
        
        // If n is less than 1, set = 0 for find_nth purposes
        if(n < 1) {
            n = 0;
        } else if(n > array_size) { // If n is greater than array size, set = -1 for find_nth purposes
            n = -1;
        }
        // ------------------------

        nth = find_nth(int_array, array_size, n);
        if(nth >= 0) {
            printf("---- Answer ----\n");
            printf("The nth value is %d\n", int_array[nth]);
            printf("--------\n");
        } else if(nth == -1) {
            printf("n is too large!\n");
        } else if(nth == -2) {
            printf("Some error!\n");
        } else {
            // Do nothing
        }
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

void conversion_test()
{
    printf("---- ATOI Sample Usage ----\n");
    char *num_str = "101";
    int num = atoi(num_str);
    printf("The number is %d\n", num);
    printf("--------\n\n");
}

void load_data(int **int_array, uint32_t *array_size)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
    }
    fclose(fp);

    int *tmp_array = (int*) malloc(sizeof(int) * cnt);
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        tmp_array[cnt] = tmp;
        cnt++;
    }
    fclose(fp);
    
    *int_array = tmp_array;
    *array_size = cnt;
}

// Given n as input, find the nth largest value
// in the list of integers loaded from the file.
// If n is larger than the number of integers,
// return -1.
// Return -2 for any other errors.
// NOTE 1:
// The file used for grading will be different from
// the file given with the homework - it will have
// different number of integers and different integer
// values

int find_nth(int *int_array, uint32_t array_size, int n)
{
    // Insert your code here (2)
    
    // Initialize vars and malloc for temp array
    int num; int max; int temp;
    int *array;
    array = (int *) malloc(sizeof(int) * array_size);
    
    // Return required outputs based on cases described in assignment
    if(n == 0) {
        // return -2 if n == 0
        return -2;
    } else if(n == -1) {
        // return -1 if greater than array_size
        return -1;
    }
    // Loop only for the n times
    for(int i = 0; i < n; ++i) {
        max = 0;
        for(int j = 0; j < array_size; ++j) {
            // Set temp var
            temp = int_array[j];
            
            // If var is in temp array, ignore
            if(array[j] == temp) {
                // Do nothing 
            } else if(temp > max) {
                // If temp var is > max then store temp in max and j in num
                max = temp;
                num = j;
            } 
        }
        // enter max from iteration through array into temp array
        array[num] = max;
    }
    // Free the temp array and return the index of nth largest 
    free(array); 
    return num;
    // ------------------------

}

void print_array(uint32_t size, int *arr)
{
   printf("---- Print Array ----\n");
    printf("This file has %d elements\n", size);
    printf("#\tValue\n");
    for(int i = 0; i < size; i++) {
        printf("%d\t%d\n", i, arr[i]);
    }
   printf("--------\n\n");
}

