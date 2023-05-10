/*
    Insertion sort of array of integers
    Works well for arrays with < 50 elements
    Performs O(N) work for sorted arrays
 */

#include <stdio.h>
#define ARRSIZE 10

void print(int *a)
{
    for (int i = 0; i < ARRSIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void insertionsort(int *a)
{
    int curr_val, j;

    // start from 1
    for (int i = 1; i < ARRSIZE; ++i)
    {
        curr_val = a[i];
        // do a shift on every iteration
        for (j = i-1; j >= 0 && curr_val < a[j]; --j)
        {
            a[j+1] = a[j];
        }
        a[j+1] = curr_val;
    }
}

int main()
{
    int a[ARRSIZE] = {3, 2, 5, 4, 7, 6, 9, 10, 1, 8};
    print(a);
    insertionsort(a);
    print(a);
    return 0;
}
