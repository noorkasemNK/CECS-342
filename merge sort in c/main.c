//used assignmetn 1 and 2 for help


//explanied this in the other file
#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

//only inside main, pointer to first element, print number of elements
static void print_array(const int *a, size_t n) {
    printf("{");
    for (size_t i = 0; i < n; i++) {
        if (i > 0) printf(", ");
        printf("%d", a[i]);
    }
    printf("}");
}
//prints array, sorts, then prints
static void test_sort(int *a, size_t n) {
    printf("Input:  ");
    print_array(a, n);
    printf("\nSorted: ");
    merge_sort(a, n);
    print_array(a, n);
    printf("\n\n");
    //print label, starts new line, then tests, then prints array
}


//assignmetn 1
int main(void) {
    int empty[] = {0};             
    int single[] = {3};
    int three[] = {3, 2, 1};
    int large[] = {42, -33, 102, -74, 30, 1, 1000, -756, 33, -7, 10};
    int duplicates[] = {5, 3, 5, 1, 3, 5, 1, 1};

    //build array, automatic, local, 
    int random_arr[100];
    srand(12345u);
    for (size_t i = 0; i < 100; i++) {
        random_arr[i] = (rand() % 2001) - 1000; 
    }

    //took from assignment 1 and 2
    printf("CECS 342 Assignment 3\n");
    printf("Name: Noor Kasem\n");
    printf("Algorithm: merge sort, Language: C\n\n");

    //running each case
    test_sort(empty, 0);
    test_sort(single, 1);
    test_sort(three, 3);
    test_sort(large, sizeof(large) / sizeof(large[0]));
    test_sort(duplicates, sizeof(duplicates) / sizeof(duplicates[0]));
    test_sort(random_arr, sizeof(random_arr) / sizeof(random_arr[0]));

    return 0;
}