#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    struct Student *ptr, *top;
    int n, i;
    float sum;
    char ch;

    printf("Enter number of students: ");
    scanf("%d", &n);

    /* allocate memory for n students */
    ptr = (struct Student *) malloc(n * sizeof(struct Student));
    if (ptr == NULL) {
        printf("Memory not allocated\n");
        return 1;
    }

    /* read records */
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
    }

    /* find average and topper */
    sum = 0;
    top = ptr;
    for (i = 0; i < n; i++) {
        sum = sum + (ptr + i)->marks;
        if ((ptr + i)->marks > top->marks) {
            top = ptr + i;
        }
    }

    printf("Average marks: %.2f\n", sum / n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n", top->name, top->roll_no, top->marks);

    /* ask to add 2 more students */
    printf("Add 2 more students? (y/n): ");
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y') {
        /* grow the array, old data stays as it is */
        ptr = (struct Student *) realloc(ptr, (n + 2) * sizeof(struct Student));
        if (ptr == NULL) {
            printf("Memory not allocated\n");
            return 1;
        }

        for (i = n; i < n + 2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
        }
        n = n + 2;

        /* calculate again for all students */
        sum = 0;
        top = ptr;
        for (i = 0; i < n; i++) {
            sum = sum + (ptr + i)->marks;
            if ((ptr + i)->marks > top->marks) {
                top = ptr + i;
            }
        }

        printf("Updated average marks: %.2f\n", sum / n);
        printf("Topper: %s (Roll %d, Marks %.2f)\n", top->name, top->roll_no, top->marks);
    }

    /* free memory */
    free(ptr);

    return 0;
}
