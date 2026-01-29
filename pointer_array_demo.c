#include <stdio.h>
#include <stddef.h>

// Modifikasi isi array dengan pointer (menambah 1 ke setiap elemen)
void increment_all(int *arr, size_t n) {
    int *p = arr;
    int *end = arr + n;
    for (; p < end; ++p) {
        (*p)++;
    }
}

// Skala semua elemen: arr[i] *= factor
void scale_all(int *arr, size_t n, int factor) {
    for (int *p = arr, *end = arr + n; p < end; ++p) {
        *p *= factor;
    }
}

// Isi rentang [begin, end) dengan value
void fill_range(int *begin, int *end, int value) {
    while (begin != end) {
        *begin++ = value;
    }
}

// Balik susunan array menggunakan dua pointer (left/right)
void reverse(int *arr, size_t n) {
    if (n == 0) return;
    int *left = arr;
    int *right = arr + n - 1;
    while (left < right) {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}

// Contoh fungsi yang tidak mengubah isi (menggunakan const pointer)
int sum_const(const int *arr, size_t n) {
    const int *p = arr;
    const int *end = arr + n;
    int s = 0;
    for (; p < end; ++p) {
        s += *p;
    }
    return s;
}

static void print_array(const int *arr, size_t n, const char *label) {
    printf("%s: ", label);
    for (size_t i = 0; i < n; ++i) {
        printf("%d%s", arr[i], (i + 1 == n ? "\n" : " "));
    }
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(a)/sizeof(a[0]);

    print_array(a, n, "Awal");

    // Modifikasi via pointer arithmetic
    increment_all(a, n);
    print_array(a, n, "Setelah increment_all");

    scale_all(a, n, 3);
    print_array(a, n, "Setelah scale_all *3");

    // Isi sebagian rentang dengan nilai tetap menggunakan pointer ke rentang
    fill_range(a + 1, a + 4, 9); // isi indeks 1..3 dengan 9
    print_array(a, n, "Setelah fill_range(1..3)=9");

    reverse(a, n);
    print_array(a, n, "Setelah reverse");

    int s = sum_const(a, n);
    printf("Sum (const) = %d\n", s);

    return 0;
}
