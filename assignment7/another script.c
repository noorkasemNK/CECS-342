
    /* Guard the allocation-size multiplication against overflow. */
    if (n > SIZE_MAX / sizeof(*a)) {
        heapsort(a, n);
        return;
    }

    uint32_t *tmp = (uint32_t *)malloc(n * sizeof(*tmp));
    if (tmp == NULL) {
        /* Correct, allocation-free fallback. */
        heapsort(a, n);
        return;
    }

    uint32_t *src = a;
    uint32_t *dst = tmp;

    for (unsigned shift = 0u; shift < 32u; shift += RADIX_BITS) {
        size_t count[RADIX_SIZE] = {0};
        size_t pos[RADIX_SIZE];

        for (size_t i = 0; i < n; ++i)
            ++count[(src[i] >> shift) & RADIX_MASK];

        size_t sum = 0u;
        for (size_t b = 0; b < RADIX_SIZE; ++b) {
            pos[b] = sum;
            sum += count[b];
        }

        for (size_t i = 0; i < n; ++i) {
            uint32_t value = src[i];
            dst[pos[(value >> shift) & RADIX_MASK]++] = value;
        }

        uint32_t *swap = src;
        src = dst;
        dst = swap;
    }

    /* Four passes normally put the result back in `a`; retain correctness
       if the number of passes is changed later. */
    if (src != a) {
        for (size_t i = 0; i < n; ++i)
            a[i] = src[i];
    }

    free(tmp);
}
