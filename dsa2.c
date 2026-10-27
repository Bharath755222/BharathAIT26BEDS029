/*
  Sparse matrix: array of triples + fast transpose

  Input format:
    1. rows and cols
    2. then all rows*cols elements of the matrix (row by row)
*/

#include <stdio.h>

#define MAX_TERMS 101
#define MAX_COL 50

typedef struct {
    int row, col, value;
} term;

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX_COL], starting_pos[MAX_COL];
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;

    /* header of b */
    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        /* count terms in each column of a */
        for (i = 0; i < num_cols; i++)
            row_terms[i] = 0;
        for (i = 1; i <= num_terms; i++)
            row_terms[a[i].col]++;

        /* starting position of each row of b */
        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++)
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

        /* print the two arrays */
        printf("\nrow_terms[]    : ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", row_terms[i]);
        printf("\nstarting_pos[] : ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", starting_pos[i]);
        printf("\n");

        /* place each term directly at its correct position */
        for (i = 1; i <= num_terms; i++) {
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void print_triples(term t[]) {
    int i;
    printf("Row\tCol\tValue\n");
    for (i = 0; i <= t[0].value; i++)
        printf("%d\t%d\t%d\n", t[i].row, t[i].col, t[i].value);
}

int main() {
    term a[MAX_TERMS], b[MAX_TERMS];
    int r, c, i, j, x, k, ordered;

    printf("Enter rows and cols: ");
    scanf("%d %d", &r, &c);

    /* read matrix and store non-zero elements as triples */
    k = 1;
    printf("Enter the matrix elements:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &x);
            if (x != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = x;
                k++;
            }
        }
    }
    a[0].row = r;
    a[0].col = c;
    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    print_triples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    print_triples(b);

    /* check that b is in row-major order */
    ordered = 1;
    for (i = 2; i <= b[0].value; i++) {
        if (b[i].row < b[i - 1].row ||
            (b[i].row == b[i - 1].row && b[i].col <= b[i - 1].col))
            ordered = 0;
    }
    if (ordered)
        printf("\nTransposed triples are already in row-major order.\n");
    else
        printf("\nTransposed triples are NOT in row-major order.\n");

    return 0;
}
