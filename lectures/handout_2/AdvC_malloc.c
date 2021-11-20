#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *a, *b = "string";
    int *arr, n, i, j;

    typedef struct {
        char name[30];
        char address[30];
        char postalcode[10];
        char id[10];
    } person;
    person *p;

    struct orang {
        char name[30];
        char address[30];
        char postalcode[10];
        char id[10];
    };
    struct orang *o;

    char **c, *d[3] = {"Aa", "Bb", "Cc"};

    if ((a = (char *) malloc(strlen(b) + 1)) == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    strcpy(a, b);
    printf("*a=%s\n", a);
    free((void *) a);

    scanf("%d", &n);
    if ((arr = (int *) malloc(n * sizeof(int))) == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    for (i = 0; i < n; i++) arr[i] = 0;
    free((void *) arr);

    scanf("%d", &n);
    if ((p = (person *) malloc(n * sizeof(person))) == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        strcpy(p[i].name, "");
        strcpy(p[i].postalcode, "");
    }
    free((void *) p);

    scanf("%d", &n);
    if ((o = (struct orang *) malloc(n * sizeof(struct orang))) == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        strcpy(o[i].name, "");
        strcpy(o[i].postalcode, "");
    }
    free((void *) o);

    if ((c = (char **) malloc(3 * sizeof(char *))) == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    for (i = 0; i < 3; i++) {
        if ((c[i] = (char *) malloc(strlen(d[i] + 1))) == NULL) {
            printf("Not enough memory\n");
            exit(1);
        }
        strcpy(c[i], d[i]);
    }
    printf("**c={");
    for (i = 0; i < 3; i++) {
        printf("{");
        for (j = 0; j < 2; j++) {
            printf("%c", c[i][j]);
            if (j == 1)printf("}"); else printf(",");
        }
        if (i == 2)printf("}"); else printf(",");
    }
    printf("}\n");
    for (i = 0; i < 3; i++)
        free((void *) c[i]);
    free((void *) c);

    exit(0);
}