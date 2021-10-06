#define MAX_LEN 128

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];

    while (fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);
}

void PrintDimensionSelection() {
    printf("\n============================================================================\n");
    printf("Calculate 2D or 3D object's properties? Type \"exit\" if you want to leave the program:\n");
    printf("1. 2D\n2. 3D\n");
    printf("Type in your choice here: ");
}