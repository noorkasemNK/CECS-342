// all the tools I used haskell.org, google gemini ai overview, w3schools, geeks4geeks, mac os, ghc compiler, vs code/claude extension for debugging
//librariaes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

typedef struct {
    const char *name;
    int age;
} human;
 //values were copied and pasted from canvas
static double numbers[] = {
    645.41, 37.59, 76.41, 5.31, -34.23, 1.11,
    1.10, 23.46, 635.47, -876.32, 467.83, 62.25
    //array
};
#define NUM_COUNT (sizeof(numbers) / sizeof(numbers[0]))
 
//values copied and pasted from canvas
static human people[] = {
    {"Hal", 20},      {"Susann", 31},  {"Dwight", 19},  {"Kassandra", 21},
    {"Lawrence", 25}, {"Cindy", 22},   {"Cory", 27},    {"Mac", 19},
    {"Romana", 27},   {"Doretha", 32}, {"Danna", 20},   {"Zara", 23},
    {"Rosalyn", 26},  {"Risa", 24},    {"Benny", 28},   {"Juan", 33},
    {"Natalie", 25}
    //array
};
#define PEOPLE_COUNT (sizeof(people) / sizeof(people[0]))
 
int CDA_noor(const void *a, const void *b) {
    double x = *(const double *)a;
    double y = *(const double *)b;
    return (x > y) - (x < y);   
}
int CPBN_kasem(const void *a, const void *b) {
    const human *p = (const human *)a;
    const human *q = (const human *)b;
    return strcmp(p->name, q->name);
}
int CPBADTN_passion(const void *a, const void *b) {
    const human *p = (const human *)a;
    const human *q = (const human *)b;
    if (p->age != q->age)
        return q->age - p->age;   
    return strcmp(p->name, q->name);
}
void print__the__numbers(const double *arr, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%.2f%s", arr[i], (i + 1 < n) ? ", " : "\n");
}
void print__the__people(const human *arr, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("  %-10s %d\n", arr[i].name, arr[i].age);
}
int main(void) {
    //arrays
    double sorted_numbers[NUM_COUNT];
    memcpy(sorted_numbers, numbers, sizeof(numbers));
    qsort(sorted_numbers, NUM_COUNT, sizeof(double), CDA_noor);
    printf("Numbers sorted ascending:\n  ");
    print__the__numbers(sorted_numbers, NUM_COUNT);
 
    human by_name[PEOPLE_COUNT];
    memcpy(by_name, people, sizeof(people));
    qsort(by_name, PEOPLE_COUNT, sizeof(human), CPBN_kasem);
    printf("\nPeople sorted by name:\n");
    print__the__people(by_name, PEOPLE_COUNT);
 
    human by_age[PEOPLE_COUNT];
    memcpy(by_age, people, sizeof(people));
    qsort(by_age, PEOPLE_COUNT, sizeof(human), CPBADTN_passion);
    printf("\nPeople sorted by age (descending), then name:\n");
    print__the__people(by_age, PEOPLE_COUNT);
 
    return 0;
}