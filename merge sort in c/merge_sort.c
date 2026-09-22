// Noor Kasem, cecs 343-03, 0921
//Tools used: macos, vs code, clang compiler, google/gemini ai overview, previous notes I made, geeks4geeks, w3schools, claude code
//merge sort in c
//i will submit my agents.md for claude code

//from assignment: Recall the sorting algorithm merge sort (John von Neumann, 1945).
      //Implement the merge sort algorithm by defining the following C procedure:
            //void merge_sort(int *a, size_t n);

//this is for the header file
#include "merge_sort.h"
//standard library
#include<stdio.h>
////standard library, gives me  malloc
#include <stdlib.h>

//array being sorted, temp is temporary array, 
//left is index of first element in left half, 
//cent is index of last element on left half, right is last element index on right half
void merge (int *arr, int *temp, size_t left, size_t cent, size_t right) {
    size_t n =left;
    size_t j = cent+1;
    size_t k = left;

    //merge loop, keeps looping until halves are merged
    while (n <= cent && j<=right) {
        if (arr[n] <= arr[j]) {
            temp[k++] = arr[n++];
            } else {
             temp[k++] = arr[j++];
            }
            //when either sides runs out, loop stops
            //comparing current front elemnt of the left half with current front elemnt from right half
            //used <= bc if elements equal it takes from left, that is stable/standard

    //cleanup for merge
    //handles left half when it has leftovers
    }
    while ( n <=cent) {
        temp[k++] = arr[n++];
    }   
    while (j <= right) {
        temp[k++] = arr[j++];
    }
        for (n = left; n <= right; n++) {
            arr[n] = temp[n];
            //recall temp
    }
}


//now is recursive
//splitting range in half, then moves onto merge
static void merge_sort_range(int *arr,  int *temp, size_t left, size_t right) {
    //points to where recursion should stop
    if (left >= right) {
        return;

    }
    //mid point 
    size_t cent = left + (right -left) /2;
    //sort the left half, the right half,
    merge_sort_range(arr, temp, left , cent);
    merge_sort_range(arr, temp, cent + 1, right);
    //merges back
    merge (arr, temp, left, cent, right);
}
//handling cases, then recursion, then cleans up
void merge_sort(int *arr, size_t d) {
    if ( d < 2) {
        return ;
    }

    //memory allocation: temporary array,
    //error handling checks if memory alloc failed
    int *temp = malloc(d * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Error: Failed memory allocating");
        exit(EXIT_FAILURE);

    }
    merge_sort_range(arr, temp, 0, d-1);
    //temp is a local pointer, 
    free(temp);
}
