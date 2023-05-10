/*
    Heap sort array of integers
    print before and after results
    indexing starts from 1 for typical array, so we'll ignore the leading 0
*/

#include <stdio.h>

#define HSIZE 10
#define SWAP(T, i, j) { T TMP = *i; *i = *j; *j = TMP; }
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define PARENT(i) (i/2)

static int a[HSIZE] = {0, 3, 2, 5, 4, 7, 6, 9, 8, 1};

void print_arr()
{
    for (int i = 0; i < HSIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// sift-down a[l] to maintain heap
// l and r determine the “left” and “right” range of the sift-down.
void sift_down(const int l, const int r, )
{
    if (j > r) { return; }
    int j = RIGHT(l), jold = l;
    while (j <= r)
    {
        if (j < r && a[j] < a[j+1]) { ++j; } // set j to better child
        if (a[j] <= a[l]) { break; } // found proper level
        a[jold] = a[j];
        jold = j;
        j=2*j+1; 
    } 
    a[jold]=a[l];
}

// indexing starts at zero for this one
void heapsort()
{
    // i = left range of the sift-down (element to be sifted)
    // decremented in hiring (heap creation) phase.
    int i;
    for (i = HSIZE/2 - 1; i >= 0; --i)
    {
        sift_down(i, HSIZE - 1);
    }
    // right range of the sift-down 
    // decremented in retirement-and-promotion (heap selection) phase.
    for (i = HSIZE - 1; i > 0; i--)
    {
        // Clear space at end array, then retire top of the heap into it.
        SWAP(int, &a[0], &a[i]); 
        sift_down(0,i-1); 
    }
}

/*
typedef struct Phase
{
    int lower_idx;
    int upper_idx;
} Phase;

void print_phase(Phase p)
{
    printf("lower %d, upper %d\n", p.lower_idx, p.upper_idx);
}

void print_arr()
{
    for (int i = 1; i < HSIZE+1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


Phase decrement_phase(Phase p)
{
    // hiring phase
    if (p.lower_idx > 1)
    {
        --p.lower_idx; 
        return p;
    }
    // retire/promotion phase
    --p.upper_idx;
    return p;
}


int get_current_val(Phase p)
{
    // hiring phase
    if (p.lower_idx > 1)
    {
        return a[p.lower_idx];
    }
    // retire/promotion phase
    int curr_val = a[p.upper_idx+1];
    a[p.upper_idx+1] = a[1]; // retire top man into end
    return curr_val;
}

int sift_down(int curr_val, Phase p)
{
    // sift curr_val to proper place 
    int i = p.lower_idx;
    int j = p.lower_idx * 2;
    while (j <= p.upper_idx)
    {
       // set j to better child
       if (j < p.upper_idx && a[j] < a[j+1]) { ++j; } 
       // check for demotion
       if (curr_val < a[j])
       {
           a[i] = a[j];
           j += (i = j);
       } 
       // otherwise, we're on curr_val's level 
       else { break; }
    }
    return i;
}

void heapsort()
{
    int curr_val, place;
    Phase phase = {(HSIZE/2)+1, HSIZE};
    while (1)
    {
        phase = decrement_phase(phase);
        curr_val = get_current_val(phase);
        if (phase.lower_idx == 1 && phase.upper_idx == 1)
        {
            a[1] = curr_val;
            return;
        }
        place = sift_down(curr_val, phase);
        a[place] = curr_val;
    }
}
*/

int main()
{
    print_arr();
    heapsort();
    print_arr();
    return 0;
}
