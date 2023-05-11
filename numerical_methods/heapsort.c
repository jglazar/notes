/*
    Heap sort array of integers
    print before and after results
    indexing starts from 1 for typical array, so we'll ignore the leading 0
*/

#include <stdio.h>

#define SWAP(T, pa, pb) { T TMP = *pa; *pa = *pb; *pb = TMP; }
#define MAXIDX(i, j, a) (a[i] > a[j] ? i : j)
#define LEFTCHILD(i) (2*i + 1)
//#define MAX(pa, pb) { *(pa) > *(pb) ? (pa) : (pb); }
//#define RIGHT(i) (2*i + 2)
//#define PARENT(i) ((i-1)/2)

void print_arr(int *a, int size)
{
    int *end = a + size;
    for (; a < end; ++a) { printf("%d ", *a); }
    printf("\n");
}

// return max child, 
// only child below max_sift_idx,
// or -1 if neither child below cut
int max_child(int curr, int max_sift_idx, int *a)
{
    int l, r;
    if ((l = LEFTCHILD(curr)) > max_sift_idx) { return -1; }
    if ((r = l+1) > max_sift_idx) { return l; } 
    return MAXIDX(l, r, a);
}

// sift value down until greater than both children
// stops if children are out-of-bounds (beyond max_sift_idx)
void sift_down(int curr, int max_sift_idx, int *a)
{
    int child = max_child(curr, max_sift_idx, a);
    if ((child < 0) || (a[child] <= a[curr])) { return; }
    SWAP(int, &a[curr], &a[child])
    sift_down(child, max_sift_idx, a);
}

// start with leaf parents, then sift each down to create heap
// this uses Floyd's algorithm which magically uses O(N) time
void create_max_heap(int *a, int size)
{
    for (int l = size/2 - 1; l >= 0; --l)
    {
        sift_down(l, size-1, a);
    }
}

// move top of heap (max value) to end
// then sift down to next-to-last position
void place_max_at_end(int *a, int size)
{
    for (int r = size - 1; r > 0; r--)
    {
        SWAP(int, &a[0], &a[r]); 
        sift_down(0, r-1, a); 
    }
}

void heapsort(int *a, int size)
{
    create_max_heap(a, size);
    place_max_at_end(a, size);
}

int main()
{
    int a[] = {0, 3, 2, 5, 4, 7, 6, 9, 8, 1};
    int size = sizeof(a) / sizeof(a[0]);
    print_arr(a, size);
    heapsort(a, size);
    print_arr(a, size);
    return 0;
}

// sift-down a[l] to maintain heap
// l and r determine the left-right range of the sift-down.
/*
void sift_down(const int l, const int r)
{
    int child = LEFT(l), curr_idx = l, val = a[l];
    while (child <= r)
    {
        if (child < r && a[child] < a[child+1]) { ++child; } // set j to better child
        if (a[child] <= val) { break; } // found proper level
        a[curr_idx] = a[child];
        curr_idx = child;
        child = LEFT(child);
    } 
    a[curr_idx]=val;
}
*/


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
