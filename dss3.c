#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];   /* coef[i] = coefficient of x^(degree-i) */
} polynomial;

/* reads a polynomial from the user */
polynomial read_poly() {
    polynomial p;
    int i;

    printf("Enter degree: ");
    scanf("%d", &p.degree);

    printf("Enter %d coefficients (highest power first, put 0 for missing terms):\n", p.degree + 1);
    for (i = 0; i <= p.degree; i++) {
        scanf("%f", &p.coef[i]);
    }
    return p;
}

/* adds two polynomials term by term (matching exponents) */
polynomial add(polynomial a, polynomial b) {
    polynomial c;
    int e, i;
    float sum;

    /* degree of result is the bigger degree */
    if (a.degree > b.degree)
        c.degree = a.degree;
    else
        c.degree = b.degree;

    /* go through every exponent from highest to 0 */
    for (e = c.degree; e >= 0; e--) {
        sum = 0;

        if (e <= a.degree)
            sum = sum + a.coef[a.degree - e];

        if (e <= b.degree)
            sum = sum + b.coef[b.degree - e];

        c.coef[c.degree - e] = sum;
    }
    return c;
}

/* prints polynomial like 3x^4 + 2x^2 + 1 */
void display(polynomial p) {
    int i, e, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        e = p.degree - i;

        if (c == 0)
            continue;          /* skip zero terms */

        /* sign */
        if (first) {
            if (c < 0) {
                printf("-");
                c = -c;
            }
        } else {
            if (c < 0) {
                printf(" - ");
                c = -c;
            } else {
                printf(" + ");
            }
        }

        /* coefficient and power */
        if (e == 0) {
            printf("%g", c);
        } else if (e == 1) {
            printf("%gx", c);
        } else {
            printf("%gx^%d", c, e);
        }

        first = 0;
    }

    /* if every term was 0 */
    if (first)
        printf("0");

    printf("\n");
}

int main() {
    polynomial A, B, C;

    printf("First polynomial A(x)\n");
    A = read_poly();

    printf("\nSecond polynomial B(x)\n");
    B = read_poly();

    C = add(A, B);

    printf("\nA(x) = ");
    display(A);
    printf("B(x) = ");
    display(B);
    printf("A(x) + B(x) = ");
    display(C);

    return 0;
}
