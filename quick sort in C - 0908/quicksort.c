// Program Quick Sort in C (TH, 1959)
// need to use Void quick_sort(int *a, int n); // Quick sort an array 'a' with 'n' elements in place
// CECS 342 Assignment 1
// Name; Noor Kasem
// Algorithm: quick sort, Language: C
// Tools: visual studio code, macOS terminal, Clang compiler, w3schools, stackoverflow, and notes from previous class.

// standard input and output. .h is the header file
#include <stdio.h>


// swap functions is meant to reorganize where the elements
    // pointers, derefrences, stored values, values dont get lost when over written.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    //saved value moved into b
    *b = temp;
}

// partition is the divide and conquer, breaks down large sorting problem into smaller independent sub problems
//used an array for effiency, reordering of the data/elements
int partition( int array[], int low, int high) {
    //selecting last element
    int pivot = array[high];
    //i is tracking the index, this line intitializes the boundary
    int i = (low -1);
    //j starts low and moves high, and this for loop is going to each element in array except the pivot
    for (int j = low; j <= high -1; j++) {
        //if it's true then increments, if it's false then nothing happens. j moves to next element
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]); 
        } 
    }
    swap(&array[i + 1], &array[high]);
    return(i + 1);
}
// void to sort array in place, mutates memeory
void quick_sort(int *a, int n) {
    // 0 or 1 for already sorted elements, prevents on going recursions
    if (n<= 1) {
        return;
    }
    // always makes a the start for every rangem sorts full length which is n
    int low = 0;
    int high = n-1;
    // rearranging so everything is less than the pivot goes to left, and greater goes to the right
    int pivot_index = partition(a, low, high);
    // returns this to the correct location of pivot
    quick_sort(a, pivot_index);
    quick_sort(a + pivot_index +1, n-pivot_index -1);
    //recursively sorts
}

//testing my program, used the same numbers as the professor
int main(void) {
    int small[] = {0};
    int single[] = {3};
    int three[] = {3, 2, 1,};
    int large[] = {42, -33, 102, -74, 30, 1, 1000, -756, 33, -7, 10,};

    //general info listed in the exmaple on canvas
    printf("CECS 342 Assignment 1\n");
    printf("Name: Noor Kasem\n");
    printf("Algorithm: quick sort, Language: C\n\n");

    // I chose  for-loops because that's what I'm used to, also I think it works etter because it iterates thru every elemnts
    //starts at 0, goes to 10, incremeents, prints current element as a #
    //the if makes the ouput organize the numbers, separates, uses commas
    printf("Input:  {");
    for (int i = 0; i < 0; i++) {
        if (i > 0) printf(", ");
        printf("%d", small[i]);
    }
    //prints new line witht he sorted numbers
    printf("}\nSorted: ");
    //calls quick sort, not much to sort in empty arrays, but for other arrays it sorts them
    quick_sort(small, 0);
    printf("{");
    for (int i = 0; i < 0; i++) {
        if (i > 0) printf(", ");
        printf("%d", small[i]);
    }
    // new lines for formatting
    printf("}\n\n");

    printf("Input:  {");
    for (int i = 0; i < 1; i++) {
        if (i > 0) printf(", ");
        printf("%d", single[i]);
    }
    printf("}\nSorted: ");
    quick_sort(single, 1);
    printf("{");
    for (int i = 0; i < 1; i++) {
        if (i > 0) printf(", ");
        printf("%d", single[i]);
    }
    printf("}\n\n");

    printf("Input:  {");
    for (int i = 0; i < 3; i++) {
        if (i > 0) printf(", ");
        printf("%d", three[i]);
    }
    printf("}\nSorted: ");
    quick_sort(three, 3);
    printf("{");
    for (int i = 0; i < 3; i++) {
        if (i > 0) printf(", ");
        printf("%d", three[i]);
    }
    printf("}\n\n");

    printf("Input:  {");
    for (int i = 0; i < 11; i++) {
        if (i > 0) printf(", ");
        printf("%d", large[i]);
    }
    printf("}\nSorted: ");
    quick_sort(large, 11);
    printf("{");
    for (int i = 0; i < 11; i++) {
        if (i > 0) printf(", ");
        printf("%d", large[i]);
    }
    printf("}\n\n");
    //end of the program, no erros will be successful
    return 0;
}