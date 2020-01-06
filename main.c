#include <stdio.h>
#include <stdlib.h>

static float **sum(float **first_matrix, float **second_matrix, unsigned int rows, unsigned int cols);
static float **create_matrix(unsigned int rows, unsigned int cols);
static void load_matrix(float **matrix, unsigned int rows, unsigned int cols);
static void print_matrix(float **matrix, unsigned int rows, unsigned int cols);
static void free_matrix(float **matrix, unsigned int rows);

int main() {
    unsigned int rows, cols;
    printf("Number of rows: ");
    scanf("%u", &rows);
    printf("Number of cols: ");
    scanf("%u", &cols);

    float **first_matrix = create_matrix(rows, cols);

    if(first_matrix == NULL) {
        printf("Unable to allocate first matrix!\n");
        return 1;
    }

    float **second_matrix = create_matrix(rows, cols);

    if(second_matrix == NULL) {
        printf("Unable to allocate first matrix!\n");
        free_matrix(first_matrix, rows);
        return 1;
    }

    printf("-- FIRST MATRIX --\n");
    load_matrix(first_matrix, rows, cols);
    printf("-- SECOND MATRIX --\n");
    load_matrix(second_matrix, rows, cols);

    float **result = sum(first_matrix, second_matrix, rows, cols);

    if(result == NULL) {
        printf("\nUnable to allocate result matrix!\n");
        free_matrix(first_matrix, rows);
        free_matrix(second_matrix, rows);
    }

    printf("\n-- RESULT --\n");
    print_matrix(result, rows, cols);

    free_matrix(first_matrix, rows);
    free_matrix(second_matrix, rows);

    return 0;
}

static float **sum(float **first_matrix, float **second_matrix, unsigned int rows, unsigned int cols) {
    float **res = create_matrix(rows, cols);

    if(res == NULL)
        return NULL;

    unsigned int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            res[i][j] = first_matrix[i][j] + second_matrix[i][j];

    return res;
}

static void load_matrix(float **matrix, unsigned int rows, unsigned int cols) {
    unsigned int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++) {
            printf("Enter number [%u][%u]: ", i, j);
            scanf("%f", &matrix[i][j]);
        }
}

static void print_matrix(float **matrix, unsigned int rows, unsigned int cols) {
    unsigned int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%f ", matrix[i][j]);

        printf("\n");
    }
}

static float **create_matrix(unsigned int rows, unsigned int cols) {
    float **matrix = (float **) malloc(rows * sizeof(float));

    unsigned int i;
    for (i = 0; i < rows; i++) {
        matrix[i] = (float *) malloc(cols * sizeof(float));

        if(matrix[i] == NULL) {
            free_matrix(matrix, i + 1);
            return NULL;
        }
    }

    return matrix;
}

static void free_matrix(float **matrix, unsigned int rows) {
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
}