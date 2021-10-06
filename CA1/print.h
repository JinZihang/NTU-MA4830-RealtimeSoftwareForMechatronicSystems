#ifndef PRINT
#define PRINT

#include <stdbool.h>

#include "enum.h"

#define MAX_LEN 128

void PrintImage(FILE *fptr)
{
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
}

void PrintTitle(char *filename)
{
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "error opening %s\n", filename);
        exit(1);
    }
    PrintImage(fptr);
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

void ShapeSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Calculate which 2D Shape? Type \"Exit\" if you want to leave the program:\n");
    printf("1. Rectangle\n2. Square\n3. Circle\n");
    printf("Type in your choice here: ");
}

void WrongShapeInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"Rectangle\", \"Square\", \"Circle\" ===========\n");
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

void DisplayResults(enum shape shape, double result_1, double result_2)
{
    bool is2D = false;

    printf("\nCalculation results:\n");

    if (shape == Rectangle || shape == Square || shape == Circle)
    {
        is2D = true;
    }

    if (is2D)
    {
        if (shape != Circle)
        {
            printf("   |    Perimeter  | ");
        }
        else
        {
            printf("   | Circumference | ");
        }

        printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1, result_1 * 10, result_1 * 1E2, result_1 * 1E3);
        printf("   |_______________|__________________|___________________|___________________|___________________|\n");
        printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2, result_2 * 1E2, result_2 * 1E4, result_2 * 1E6);
        printf("   |_______________|__________________|___________________|___________________|___________________|\n");
    }
    else
    {
        printf("    _________________________________________________________________________________________________________\n");
        printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1, result_1 * 1E2, result_1 * 1E4, result_1 * 1E6);
        printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
        printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2, result_2 * 1E3, result_2 * 1E6, result_2 * 1E9);
        printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
    }
}

void ProcessSelectionInstructions()
{
    printf("Type in\n");
    printf("1. History\t- To view the calculation history.\n");
    printf("2. Calculate\t- To calculate again.\n");
    printf("2. Exit\t- To leave the program.\n");
    printf("Your choice: ");
}

void LengthSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Enter the length parameter\n");
    printf("Type in your choice here: ");
}

void WidthSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Enter the width parameter\n");
    printf("Type in your choice here: ");
}

void RadiusSelectionInstructions()
{
    printf("\n============================================================================\n");
    printf("Enter the radius parameter\n");
    printf("Type in your choice here: ");
}

#endif