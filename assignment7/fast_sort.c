/// created By Noor Kasem, Used AI tools used: Claude (Anthropic) - Claude Opus 5.5 and Claude Sonnet 5.5, via Claude Code.
// On my macOS M2. Also used Visual Studio Code for editing. Also used Gemini AI overview for general questions



#include "fast_sort.h"
#include <stdlib.h>

const char first_name[] = "Noor"; 
const char last_name[] = "Kasem";   

#define TOP 11u         
#define LOW (32u - TOP) 
#define NB (1u << TOP) 
#define W0 10u          
#define W1 (LOW - W0)   
#define N0 (1u << W0)
#define N1 (1u << W1)
#define M0 (N0 - 1u)
#define M1 (N1 - 1u)


#ifndef KMIN
#define KMIN (1u << 23)
#endif

#ifndef FORCE_EXACT0
#define FORCE_EXACT0 0
#endif
#ifndef FORCE_EXACT1
#define FORCE_EXACT1 0
#endif
#ifndef FORCE_COMPACT
#define FORCE_COMPACT 0
#endif


#define OPT_MAX ((size_t)1 << 22)


#define ZERO(arr, count)                         \
  do {                                           \
    for (size_t zi_ = 0; zi_ < (count); zi_++) { \
      (arr)[zi_] = 0;                            \
      __asm__ volatile("" ::: "memory");         \
    }                                            \
  } while (0)
#define COPY(dst, src, count)                    \
  do {                                           \
    for (size_t ci_ = 0; ci_ < (count); ci_++) { \
      (dst)[ci_] = (src)[ci_];                   \
      __asm__ volatile("" ::: "memory");         \
    }                                            \
  } while (0)

typedef struct {
  uint32_t *p, *e; 
} bucket;

static void insertion_sort(uint32_t *a, size_t n) {
  for (size_t i = 1; i < n; i++) {
    uint32_t v = a[i];
    size_t j = i;
    while (j && a[j - 1] > v) {
      a[j] = a[j - 1];
      j--;
    }
    a[j] = v;
  }
}


static size_t fs_next[4][256], fs_end[4][256];

static void flag_sort(uint32_t *a, size_t n, unsigned shift) {
  if (n <= 32) {
    insertion_sort(a, n);
    return;
  }
  size_t *next = fs_next[shift / 8], *end = fs_end[shift / 8];
  ZERO(end, 256);
  for (size_t i = 0; i < n; i++) end[(a[i] >> shift) & 255]++;
  size_t sum = 0;
  for (unsigned b = 0; b < 256; b++) {
    next[b] = sum;
    sum += end[b];
    end[b] = sum;
  }
  for (unsigned b = 0; b < 256; b++) {
    while (next[b] < end[b]) {
      uint32_t v = a[next[b]];
      unsigned d = (v >> shift) & 255;
      if (d == b) {
        next[b]++;
      } else {
        a[next[b]] = a[next[d]];
        a[next[d]++] = v;
      }
    }
  }
  if (shift == 0) return;
  size_t lo = 0;
  for (unsigned b = 0; b < 256; b++) {
    flag_sort(a + lo, end[b] - lo, shift - 8);
    lo = end[b];
  }
}


static uint32_t small_buf[4096];
static uint32_t small_cnt[256];

static void small_sort(uint32_t *a, size_t n) {
  uint32_t *src = a, *dst = small_buf;
  for (unsigned sh = 0; sh < 32; sh += 8) {
    uint32_t *c = small_cnt;
    ZERO(c, 256);
    for (size_t i = 0; i < n; i++) c[(src[i] >> sh) & 255]++;
    uint32_t sum = 0;
    for (unsigned i = 0; i < 256; i++) {
      uint32_t t = c[i];
      c[i] = sum;
      sum += t;
    }
    for (size_t i = 0; i < n; i++) {
      uint32_t v = src[i];
      dst[c[(v >> sh) & 255]++] = v;
    }
    uint32_t *t = src;
    src = dst;
    dst = t;
  }
}


#define CAP0(m) ((m) / N0 + (m) / (2 * N0) + 64)
#define ZSIZE(m) (N0 * CAP0(m))
static size_t zneed(size_t m) { return m <= OPT_MAX ? ZSIZE(m) : m; }

static uint32_t exact_h0[N0], exact_h1[N1];
static uint16_t opt_c0[N0];
static uint32_t opt_h1[N1];
static uint32_t tiny[32];

static inline void prefix(uint32_t *c, unsigned n) {
  uint32_t sum = 0;
  for (unsigned i = 0; i < n; i++) {
    uint32_t t = c[i];
    c[i] = sum;
    sum += t;
  }
}

static inline void hist2(const uint32_t *X, size_t cnt, uint32_t *restrict h0,
                         uint32_t *restrict h1) {
  for (size_t i = 0; i < cnt; i++) {
    uint32_t v = X[i];
    h0[v & M0]++;
    h1[(v >> W0) & M1]++;
  }
}


static inline void scatter_digit(const uint32_t *X, size_t cnt,
                                 uint32_t *restrict dst, uint32_t *restrict c,
                                 unsigned shift, uint32_t mask) {
  for (size_t i = 0; i < cnt; i++) {
    uint32_t v = X[i];
    dst[c[(v >> shift) & mask]++] = v;
  }
}


static void lsd_exact(const uint32_t *X0, size_t n0, const uint32_t *X1,
                      size_t n1, uint32_t *Y, uint32_t *restrict Z) {
  size_t m = n0 + n1;
  uint32_t *h0 = exact_h0, *h1 = exact_h1;
  ZERO(h0, N0);
  ZERO(h1, N1);
  hist2(X0, n0, h0, h1);
  hist2(X1, n1, h0, h1);
  uint32_t first = n0 ? X0[0] : X1[0];
  int skip0 = h0[first & M0] == m;         
  int skip1 = h1[(first >> W0) & M1] == m; 
  if (skip0 && skip1) {
    COPY(Z, X0, n0);
    COPY(Z + n0, X1, n1);
    COPY(Y, Z, m);
  } else if (skip0 || skip1) {
    uint32_t *c = skip0 ? h1 : h0;
    unsigned shift = skip0 ? W0 : 0;
    uint32_t mask = skip0 ? M1 : M0;
    prefix(c, skip0 ? N1 : N0);
    scatter_digit(X0, n0, Z, c, shift, mask);
    scatter_digit(X1, n1, Z, c, shift, mask);
    COPY(Y, Z, m);
  } else {
    prefix(h0, N0);
    scatter_digit(X0, n0, Z, h0, 0, M0);
    scatter_digit(X1, n1, Z, h0, 0, M0);
    prefix(h1, N1);
    scatter_digit(Z, m, Y, h1, W0, M1);
  }
}


static inline int opt_scatter(const uint32_t *X, size_t cnt,
                              uint32_t *restrict Z, uint16_t *restrict c0,
                              uint32_t *restrict h1, uint32_t capv) {
  for (size_t i = 0; i < cnt; i++) {
    uint32_t v = X[i];
    uint32_t j = v & M0;
    uint32_t c = c0[j];
    if (__builtin_expect(c == capv, 0)) return 0;
    Z[j * capv + c] = v;
    c0[j] = (uint16_t)(c + 1);
    h1[(v >> W0) & M1]++;
  }
  return 1;
}


static inline void opt_final(const uint32_t *restrict Z,
                             const uint16_t *restrict c0, uint32_t capv,
                             uint32_t *restrict Y, uint32_t *restrict h1) {
  for (unsigned j = 0; j < N0; j++) {
    const uint32_t *s = Z + (size_t)j * capv;
    size_t cnt = c0[j];
    for (size_t k = 0; k < cnt; k++) {
      uint32_t v = s[k];
      Y[h1[(v >> W0) & M1]++] = v;
    }
  }
}

static void lsd_bucket(const uint32_t *X0, size_t n0, const uint32_t *X1,
                       size_t n1, uint32_t *Y, uint32_t *restrict Z) {
  size_t m = n0 + n1;
  if (m <= 32) {
    COPY(tiny, X0, n0);
    COPY(tiny + n0, X1, n1);
    insertion_sort(tiny, m);
    COPY(Y, tiny, m);
    return;
  }
  if (m >= 4 * N0 && m <= OPT_MAX) {
    uint16_t *c0 = opt_c0;
    uint32_t *h1 = opt_h1;
    uint32_t capv = (uint32_t)CAP0(m);
    ZERO(c0, N0);
    ZERO(h1, N1);
    if (opt_scatter(X0, n0, Z, c0, h1, capv) &&
        opt_scatter(X1, n1, Z, c0, h1, capv)) {
      prefix(h1, N1);
      opt_final(Z, c0, capv, Y, h1);
      return;
    }
  }
  lsd_exact(X0, n0, X1, n1, Y, Z);
}


static int scatter(const uint32_t *restrict src, size_t n,
                   bucket *restrict B) {
  for (size_t i = 0; i < n; i++) {
    uint32_t v = src[i];
    bucket *b = &B[v >> LOW];
    uint32_t *p = b->p;
    if (__builtin_expect(p == b->e, 0)) return 0;
    *p = v;
    b->p = p + 1;
  }
  return 1;
}


static size_t gap_cap(size_t n) { return (n / NB + (n / NB >> 4) + 64) | 1; }


static bucket B0[NB], B1[NB];
static size_t st0[NB], st1[NB];
static size_t off[NB];

static void init_gapped(bucket *B, size_t *st, uint32_t *base, size_t cap) {
  for (size_t b = 0; b < NB; b++) {
    st[b] = b * cap;
    B[b].p = base + b * cap;
    B[b].e = base + (b + 1) * cap;
  }
}

static size_t exact_cnt[NB];

static void init_exact(bucket *B, size_t *st, uint32_t *base,
                       const uint32_t *src, size_t n) {
  size_t *cnt = exact_cnt;
  ZERO(cnt, NB);
  for (size_t i = 0; i < n; i++) cnt[src[i] >> LOW]++;
  size_t sum = 0;
  for (size_t b = 0; b < NB; b++) {
    st[b] = sum;
    B[b].p = base + sum;
    sum += cnt[b];
    B[b].e = base + sum;
  }
}


static void compact_part1(uint32_t *a) {
  size_t pos = 0;
  for (size_t b = 0; b < NB; b++) {
    uint32_t *src = a + st1[b];
    size_t cnt = (size_t)(B1[b].p - src);
    uint32_t *dst = a + pos;
    if (dst != src) COPY(dst, src, cnt);
    st1[b] = pos;
    pos += cnt;
    B1[b].p = a + pos;
  }
}

void fast_sort(uint32_t *a, size_t n) {
  if (n <= 32) {
    insertion_sort(a, n);
    return;
  }
  if (n <= 4096) {
    small_sort(a, n);
    return;
  }

  
  size_t h = n >= KMIN ? n / 32 * 17 : n;
  size_t n1 = n - h;
  size_t cap0 = gap_cap(h);
  uint32_t *tmp = malloc(NB * cap0 * sizeof *tmp);
  if (!tmp) {
    flag_sort(a, n, 24);
    return;
  }

  init_gapped(B0, st0, tmp, cap0);
  if (FORCE_EXACT0 || !scatter(a, h, B0)) {
    init_exact(B0, st0, tmp, a, h); 
    scatter(a, h, B0);
  }

  
  size_t cap1 = gap_cap(n1);
  if (n1 == 0) {
    for (size_t b = 0; b < NB; b++) {
      st1[b] = 0;
      B1[b].p = a;
      B1[b].e = a;
      __asm__ volatile("" ::: "memory");
    }
  } else {
    int ok = 0;
    if (!FORCE_EXACT1 && NB * cap1 <= h) {
      init_gapped(B1, st1, a, cap1);
      ok = scatter(a + h, n1, B1);
    }
    if (!ok) {
      init_exact(B1, st1, a, a + h, n1); // n1 <= h
      scatter(a + h, n1, B1);
    }
  }

  
  size_t zmax = 0, sum = 0, hi = 0;
  int unsafe = FORCE_COMPACT;
  for (size_t b = 0; b < NB; b++) {
    size_t c0 = (size_t)(B0[b].p - (tmp + st0[b]));
    size_t c1 = (size_t)(B1[b].p - (a + st1[b]));
    off[b] = sum;
    sum += c0 + c1;
    size_t z = zneed(c0 + c1);
    if (z > zmax) zmax = z;
    if (hi > off[b]) unsafe = 1;
    if (st1[b] + c1 > hi) hi = st1[b] + c1;
  }
  if (unsafe) compact_part1(a); 

  uint32_t *z = malloc(zmax * sizeof *z);
  if (!z) {
    
    compact_part1(a);
    size_t pos = n1;
    for (size_t b = 0; b < NB; b++) {
      const uint32_t *src = tmp + st0[b];
      size_t cnt = (size_t)(B0[b].p - src);
      COPY(a + pos, src, cnt);
      pos += cnt;
    }
    free(tmp);
    flag_sort(a, n, 24);
    return;
  }

  for (size_t b = NB; b-- > 0;) {
    const uint32_t *x0 = tmp + st0[b];
    const uint32_t *x1 = a + st1[b];
    lsd_bucket(x0, (size_t)(B0[b].p - x0), x1, (size_t)(B1[b].p - x1), a + off[b],
               z);
  }
  free(z);
  free(tmp);
}
