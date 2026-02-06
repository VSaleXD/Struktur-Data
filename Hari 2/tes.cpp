#include <stdio.h>
#include <stdlib.h>

int main() {

    int n, i;
    int *a, *b;
    scanf("%d", &n);

    a = (int*) malloc (n * sizeof(int));
    b = (int*) malloc (n * sizeof(int));

    int* helpA = a;
    int* helpB = b + n - 1;

    for (i = 0; i<n; i++) {
        *helpA = rand()%10; 
        *helpB = *helpA;
        helpA++;
        helpB--;
    }

    helpA = a;
    helpB = b;

    for (i = 0; i<n; i++) printf("%d ", helpA[i]); 
    printf("\n");
    for (i = 0; i<n; i++) printf("%d ", helpB[i]);

    free(a);
    free(b);

    return 0;
}