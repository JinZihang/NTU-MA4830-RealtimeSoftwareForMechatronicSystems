#ifndef PRINT
#define PRINT

#define MAX_LEN 128

void PrintImage(FILE *fptr)
{
    char read_string[MAX_LEN];

    while (fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);
}

void DimensionSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Calculate 2D or 3D object's properties? Type \"Exit\" if you want to leave the program:\n");
    printf("1. 2D\n2. 3D\n");
    printf("Type in your choice here: ");
}

void WrongDimensionInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"2D\", \"3D\" or the choice index (\"1\" or \"2\"). ===========\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice here: ");
}

void NoMemoryAlert()
{
    printf("Not enough memory!");
}

void UnitSelectionInstructions()
{
    printf("\nSelect the input unit:\n");
    printf("m\tdm\tcm\tmm\n");
    printf("Your choice: ");
}

void WrongUnitInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("================== Enter \"m\", \"dm\", \"cm\" or \"mm\". ==================\n");
    printf("============================================================================\n\n");
    printf("Enter again here: ");
}

void ShapeSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Calculate which 2D Shape? Type \"Exit\" if you want to leave the program:\n");
    printf("1. Rectangle\n2. Square\n3. Triangle\n4. Circle\n");
    printf("Type in your choice here: ");
}

void WrongShapeInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"Rectangle\", \"Square\", \"Triangle\", \"Circle\" ===========\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice here: ");
}

void ObjectSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Calculate which 3D Object? Type \"Exit\" if you want to leave the program:\n");
    printf("1. Cuboid\n2. Cube\n3. Cone\n4. Sphere\n");
    printf("Type in your choice here: ");
}

void WrongObjectInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"Cuboid\", \"Cube\", \"Cone\", \"Sphere\" ===========\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice here: ");
}

#endif