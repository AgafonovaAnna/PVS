#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Размеры массива
#define SIZE_X 5000
#define SIZE_Y 5000

typedef float arr_t;

// Получение текущего времени (в секундах)
double get_time_sec() {
    return (double)clock() / CLOCKS_PER_SEC;
}

// Инициализация массива
void init(arr_t* arr[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        arr[i] = malloc(sizeY * sizeof(arr_t));
}

// Заполнение массива по порядку числами от 1 до size
void fill_sequential(arr_t* arr[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        for (uint32_t j = 0; j < sizeY; ++j)
            arr[i][j] = i * sizeY + j + 1;
}

// Освобождение памяти
void free_array(arr_t* arr[], uint32_t sizeX) {
    for (uint32_t i = 0; i < sizeX; ++i)
        free(arr[i]);
}

// Последовательное сложение
void sAddArray(arr_t* a[], arr_t* b[], arr_t* out[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        for (uint32_t j = 0; j < sizeY; ++j)
            out[i][j] = a[i][j] + b[i][j];
}

// Последовательное вычитание
void sSubArray(arr_t* a[], arr_t* b[], arr_t* out[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        for (uint32_t j = 0; j < sizeY; ++j)
            out[i][j] = a[i][j] - b[i][j];
}

// Последовательное умножение
void sMulArray(arr_t* a[], arr_t* b[], arr_t* out[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        for (uint32_t j = 0; j < sizeY; ++j)
            out[i][j] = a[i][j] * b[i][j];
}

// Последовательное деление
void sDivArray(arr_t* a[], arr_t* b[], arr_t* out[], uint32_t sizeX, uint32_t sizeY) {
    for (uint32_t i = 0; i < sizeX; ++i)
        for (uint32_t j = 0; j < sizeY; ++j)
            out[i][j] = b[i][j] ? a[i][j] / b[i][j] : 0;
}

int main() {
    arr_t *a[SIZE_X], *b[SIZE_X], *out[SIZE_X];

    init(a, SIZE_X, SIZE_Y);
    init(b, SIZE_X, SIZE_Y);
    init(out, SIZE_X, SIZE_Y);

    fill_sequential(a, SIZE_X, SIZE_Y);
    fill_sequential(b, SIZE_X, SIZE_Y);

    printf("Последовательное выполнение:\n");

    double t1 = get_time_sec();
    sAddArray(a, b, out, SIZE_X, SIZE_Y);
    double t2 = get_time_sec();
    printf("Сложение: %.6f сек\n", t2 - t1);

    t1 = get_time_sec();
    sSubArray(a, b, out, SIZE_X, SIZE_Y);
    t2 = get_time_sec();
    printf("Вычитание: %.6f сек\n", t2 - t1);

    t1 = get_time_sec();
    sMulArray(a, b, out, SIZE_X, SIZE_Y);
    t2 = get_time_sec();
    printf("Умножение: %.6f сек\n", t2 - t1);

    t1 = get_time_sec();
    sDivArray(a, b, out, SIZE_X, SIZE_Y);
    t2 = get_time_sec();
    printf("Деление: %.6f сек\n", t2 - t1);

    free_array(a, SIZE_X);
    free_array(b, SIZE_X);
    free_array(out, SIZE_X);

    return 0;
}
