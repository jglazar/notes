/*
    Selection sort of array of integers
 */

#include <stdio.h>
#define ARRSIZE 10
#define SWAP_PTR(T, i, j) { T TMP = *i; *i = *j; *j = TMP; }


void print(int *a)
{
    for (int i = 0; i < ARRSIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


void swap_ptr(int *i, int *j)
{
    if (i == j) { return; }
    int tmp = *i;
    *i = *j;
    *j = tmp;
}


void swap(int *a, int i, int j)
{
    if (i == j) { return; }
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}


// sort using integers to track place
void i_selectionsort(int *a)
{
    int min;
    for (int i = 0; i < ARRSIZE; ++i)
    {
        min = i;
        for (int j = i; j < ARRSIZE; ++j)
        {
            if (a[j] < a[min]) { min = j; }
        }
        //SWAP_PTR(int, &a[i], &a[min]);
        swap(a, i, min);
    }
}


// sort using pointers to track place
// pointers have issues with falling off the beginning
void p_selectionsort(int * const a)
{
    int *min;
    for (int *i = a; i < a+ARRSIZE; ++i)
    {
        min = i;
        for (int* j = i; j < a+ARRSIZE; ++j)
        {
            if (*j < *min) { min = j; }
        }
        //SWAP_PTR(int, i, min);
        swap_ptr(i, min);
    }
}


int main()
{
    int a[ARRSIZE] = {3, 2, 5, 4, 7, 6, 9, 10, 1, 8};
    print(a);
    p_selectionsort(a);
    print(a);
    return 0;
}
