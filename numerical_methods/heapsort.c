/*
    Heap sort array of integers
    print before and after results
    indexing starts from 1 for typical array, so we'll ignore the leading 0
*/

#include <stdio.h>

#define HSIZE 10

static int a[HSIZE+1] = {0, 3, 2, 5, 4, 7, 6, 9, 10, 1, 8};
static int lower = (HSIZE / 2) + 1;
static int upper = HSIZE;
static int curr_val;

void decrement_phase()
{
    // hiring phase
    if (lower > 1)
    {
        curr_val = a[--lower];
        return;
    }
    // retire/promotion phase
    curr_val = a[upper];
    a[upper] = a[1]; // retire top man into end
    if (--upper == 1)
    {
        a[1] = curr_val;
        // <send heapsort abort signal here>
    }
    return;
}

void heapsort()
{
    // lower is decremented to 1 in hiring phase
    // upper is decremented to 1 in retire/promotion phase
    while (1)
    {
        decrement_phase();
       // sift curr_val to proper place 
       int i = lower;
       int j = lower * 2;
       while (j <= upper)
       {
           // set j to better child
           if (j < upper && a[j] < a[j+1]) { ++j; } 
           // check for demotion
           if (curr_val < a[j])
           {
               a[i] = a[j];
               j += (i = j);
           } 
           // otherwise, we're on curr_val's level and terminate 
           // sift-down by setting j to upper + 1
           else { j = upper + 1; }
       }
       // finally, put curr_val in its place
       a[i] = curr_val;
    }
}


void print(int *a)
{
    for (int i = 1; i < HSIZE+1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main()
{
    print(a);
    heapsort(a);
    print(a);
    return 0;
}
