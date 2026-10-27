// fast_sort.c
// 
// CECS 342 - Extra Credit Grand Prix
// Optimized 16-bit LSD Radix Sort for 32-bit integers

#include "fast_sort.h"
#include <stdlib.h>

// AI Tools used: Gemini (Collaborative design and code optimization)

const char first_name[] = "Alex";
const char last_name[] = "Student";

void fast_sort(uint32_t *a, size_t n) {
    if (n < 2) return;

    // Allocate temporary array for sorting passes (approx. 4 GB for 1 billion elements)
    uint32_t *temp = (uint32_t *)malloc(n * sizeof(uint32_t));
    // Allocate frequency/prefix sum table for 16-bit chunks (65,336 bins)
    uint32_t *count = (uint32_t *)malloc(65536 * sizeof(uint32_t));

    if (!temp || !count) {
        free(temp);
        free(count);
        return;
    }

    // ==========================================
    // Pass 1: Sort by lower 16 bits (bits 0-15)
    // ==========================================
    for (size_t i = 0; i < 65536; i++) {
        count[i] = 0;
    }

    for (size_t i = 0; i < n; i++) {
        count[a[i] & 0xFFFF]++;
    }

    uint32_t total = 0;
    for (size_t i = 0; i < 65536; i++) {
        uint32_t c = count[i];
        count[i] = total;
        total += c;
    }

    for (size_t i = 0; i < n; i++) {
        uint32_t val = a[i];
        uint32_t bucket = val & 0xFFFF;
        temp[count[bucket]++] = val;
    }

    // ==========================================
    // Pass 2: Sort by upper 16 bits (bits 16-31)
    // ==========================================
    for (size_t i = 0; i < 65536; i++) {
        count[i] = 0;
    }

    for (size_t i = 0; i < n; i++) {
        count[temp[i] >> 16]++;
    }

    total = 0;
    for (size_t i = 0; i < 65536; i++) {
        uint32_t c = count[i];
        count[i] = total;
        total += c;
    }

    for (size_t i = 0; i < n; i++) {
        uint32_t val = temp[i];
        uint32_t bucket = val >> 16;
        a[count[bucket]++] = val;
    }

    // Clean up allocated memory
    free(count);
    free(temp);
}