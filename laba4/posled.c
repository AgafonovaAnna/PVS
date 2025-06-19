#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void generateMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            matrix[i][j] = rand() % 100 + 1;
}

double getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Использование: %s <запуски> <строки> <столбцы>\n", argv[0]);
        return 1;
    }

    int runs = atoi(argv[1]);
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    int size = rows * cols;

    srand(time(NULL));

    // Выделение памяти для матриц
    int** A = (int**)malloc(rows * sizeof(int*));
    int** B = (int**)malloc(rows * sizeof(int*));
    int** add = (int**)malloc(rows * sizeof(int*));
    int** sub = (int**)malloc(rows * sizeof(int*));
    int** mul = (int**)malloc(rows * sizeof(int*));
    float** div = (float**)malloc(rows * sizeof(float*));

    for (int i = 0; i < rows; ++i) {
        A[i] = (int*)malloc(cols * sizeof(int));
        B[i] = (int*)malloc(cols * sizeof(int));
        add[i] = (int*)malloc(cols * sizeof(int));
        sub[i] = (int*)malloc(cols * sizeof(int));
        mul[i] = (int*)malloc(cols * sizeof(int));
        div[i] = (float*)malloc(cols * sizeof(float));
    }

    double t_add = 0.0, t_sub = 0.0, t_mul = 0.0, t_div = 0.0;

    for (int r = 0; r < runs; ++r) {
        generateMatrix(A, rows, cols);
        generateMatrix(B, rows, cols);

        double start, end;

        // Сложение
        start = getCurrentTime();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                add[i][j] = A[i][j] + B[i][j];
        end = getCurrentTime();
        t_add += end - start;

        // Вычитание
        start = getCurrentTime();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                sub[i][j] = A[i][j] - B[i][j];
        end = getCurrentTime();
        t_sub += end - start;

        // Умножение
        start = getCurrentTime();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                mul[i][j] = A[i][j] * B[i][j];
        end = getCurrentTime();
        t_mul += end - start;

        // Деление
        start = getCurrentTime();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                div[i][j] = (float)A[i][j] / B[i][j];
        end = getCurrentTime();
        t_div += end - start;
    }

    printf("\nСреднее время выполнения операций за %d запусков:\n", runs);
    printf("Сложение:   %.6f секунд\n", t_add / runs);
    printf("Вычитание:  %.6f секунд\n", t_sub / runs);
    printf("Умножение:  %.6f секунд\n", t_mul / runs);
    printf("Деление:    %.6f секунд\n", t_div / runs);

    // Освобождение памяти
    for (int i = 0; i < rows; ++i) {
        free(A[i]);
        free(B[i]);
        free(add[i]);
        free(sub[i]);
        free(mul[i]);
        free(div[i]);
    }
    free(A);
    free(B);
    free(add);
    free(sub);
    free(mul);
    free(div);

    return 0;
}
