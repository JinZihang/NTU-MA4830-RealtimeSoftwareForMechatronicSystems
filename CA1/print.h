#ifndef PRINT
#define PRINT

#include <stdbool.h>

#include "struct.h"
#include "enum.h"

#define MAX_LEN 128

void DisplayImage(FILE *fptr)
{
    char readString[MAX_LEN];

    while (fgets(readString, sizeof(readString), fptr) != NULL)
        printf("%s", readString);
}

void DisplayTitle(char *filename)
{
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "error opening %s\n", filename);
        exit(1);
    }
    DisplayImage(fptr);
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
    printf("Type in your choice again here: ");
}

void NoMemoryAlert()
{
    printf("\n============================================================================\n");
    printf("============================ Not enough memory! ============================\n");
    printf("============================================================================\n\n");
}

void ShapeSelectionInstructions()
{
    printf("\nSelect the shape to calculate its properties. Type \"Exit\" if you want to leave the program or \"Back\" if you want to reselect the dimension:\n");
    printf("1. Rectangle\n2. Square\n3. Circle\n");
    printf("Type in your choice here: ");
}

void WrongShapeInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("================= Key in \"Rectangle\", \"Square\" or \"Circle\". ================\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("================== Type \"Back\" to reselect the dimension. ==================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice again here: ");
}

void ObjectSelectionInstructions()
{
    printf("\nSelect the object to calculate its properties. Type \"Exit\" if you want to leave the program or \"Back\" if you want to reselect the dimension:\n");
    printf("1. Cuboid\n2. Cube\n3. Cone\n4. Sphere\n");
    printf("Type in your choice here: ");
}

void WrongObjectInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("=============== Key in \"Cuboid\", \"Cube\", \"Cone\" or \"Sphere\". ===============\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("=================== Type \"Back\" to reselect the dimension. =================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice again here: ");
}

void UnitSelectionInstructions()
{
    printf("\nSelect the input unit:\n");
    printf("1. m\n2. dm\n3. cm\n4. mm\n");
    printf("Select unit: ");
}

void WrongUnitInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("====================== Enter \"m\", \"dm\", \"cm\" or \"mm\". ======================\n");
    printf("============= Or enter the choice index: \"1\", \"2\", \"3\" or \"4\". =============\n");
    printf("============================================================================\n\n");
    printf("Enter again here: ");
}

void DisplayResults(enum shape shape, double result_1, double result_2)
{
    bool is2D = false;

    printf("\nCalculation results:\n");
    printf("    ______________________________________________________________________________________________");

    if (shape == Rectangle || shape == Square || shape == Circle)
    {
        is2D = true;
    }

    if (is2D)
    {
        if (shape != Circle)
        {
            printf("\n   |    Perimeter  | ");
        }
        else
        {
            printf("\n   | Circumference | ");
        }

        printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1, result_1 * 10, result_1 * 1E2, result_1 * 1E3);
        printf("   |_______________|__________________|___________________|___________________|___________________|\n");
        printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2, result_2 * 1E2, result_2 * 1E4, result_2 * 1E6);
        printf("   |_______________|__________________|___________________|___________________|___________________|\n");
    }
    else
    {
        printf("___________\n");
        printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1, result_1 * 1E2, result_1 * 1E4, result_1 * 1E6);
        printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
        printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2, result_2 * 1E3, result_2 * 1E6, result_2 * 1E9);
        printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
    }
}

void ProcessSelectionInstructions()
{
    printf("\nSelect:\n");
    printf("1. History\t- To view the calculation history.\n");
    printf("2. Calculate\t- To calculate again.\n");
    printf("3. Exit\t\t- To leave the program.\n");
    printf("Enter your choice here: ");
}

void WrongProcessInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"History\", \"Calculate\" or \"Exit\" ===========\n");
    printf("============================================================================\n\n");
    printf("Type in your choice again here: ");
}

void ParamaterSelectionInstructions(char *parameter)
{
    printf("\nEnter the %s parameter\n", parameter);
    printf("Type in your choice here: ");
}

void ShapeAndObjectSelectionInstructions()
{
    printf("\nSelect any of the option\n");
    printf("1. Rectangle\n2. Square\n3. Circle\n");
    printf("4. Cuboid\n5. Cube\n6. Cone\n7. Sphere\n");
    printf("Type in your choice here: ");
}

void WrongShapeAndObjectInput()
{
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"Rectangle\", \"Square\", \"Circle\", \"Cuboid\", \"Cube\", \"Cone\", \"Sphere\" ===========\n");
    printf("============================================================================\n\n");
    printf("Type in your choice again here: ");
}

void NumericInputAlert(bool isNumeric)
{
    if (isNumeric)
    {
        printf("\n============================================================================\n");
        printf("========================= Enter a positive number! =========================\n");
        printf("============================================================================\n");
    }
    else
    {
        printf("\n============================================================================\n");
        printf("============================== Enter a number! =============================\n");
        printf("============================================================================\n");
    }
    printf("Enter again here: ");
}

void DisplayHistoryTable(enum shape shape, struct History *history, double *means, double *stds)
{
    int i;

    printf("\nCalculation Histroy of ");

    switch (shape)
    {
    case Rectangle:
        printf("Rectangle\n");
        printf("    ____________________________________________________________________________________________________\n");
        printf("   |         Index        |       Width      |       Lenth      |     Perimeter    |        Area        |\n");
        printf("   |______________________|__________________|__________________|__________________|____________________|\n");

        for (i = 0; i < history->count[0]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", i, history->rectangles[i].width, history->rectangles[i].length, history->rectangles[i].perimeter, history->rectangles[i].area);
            printf("   |______________________|__________________|__________________|__________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", means[0], means[1], means[2], means[3]);
        printf("   |______________________|__________________|__________________|__________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", stds[0], stds[1], stds[2], stds[3]);
        printf("   |______________________|__________________|__________________|__________________|____________________|\n");

        break;

    case Square:
        printf("Square\n");
        printf("    _________________________________________________________________________________\n");
        printf("   |         Index        |    Side Lenth    |     Perimeter    |        Area        |\n");
        printf("   |______________________|__________________|__________________|____________________|\n");

        for (i = 0; i < history->count[1]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", i, history->squares[i].length, history->squares[i].perimeter, history->squares[i].area);
            printf("   |______________________|__________________|__________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", means[0], means[1], means[2]);
        printf("   |______________________|__________________|__________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", stds[0], stds[1], stds[2]);
        printf("   |______________________|__________________|__________________|____________________|\n");
        
        break;

    case Circle:
        printf("Circle\n");
        printf("    _________________________________________________________________________________\n");
        printf("   |         Index        |      Radius      |   Circumference  |        Area        |\n");
        printf("   |______________________|__________________|__________________|____________________|\n");

        for (i = 0; i < history->count[2]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", i, history->circles[i].radius, history->circles[i].circumference, history->squares[i].area);
            printf("   |______________________|__________________|__________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", means[0], means[1], means[2]);
        printf("   |______________________|__________________|__________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m   | %12.2g m^2   |\n", stds[0], stds[1], stds[2]);
        printf("   |______________________|__________________|__________________|____________________|\n");

        break;

    case Cuboid:
        printf("Cuboid\n");
        printf("    _________________________________________________________________________________________________________________________\n");
        printf("   |         Index        |       Width      |       Lenth      |      Height      |    Surface Area    |       Volume       |\n");
        printf("   |______________________|__________________|__________________|__________________|____________________|____________________|\n");

        for (i = 0; i < history->count[3]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", i, history->cuboids[i].width, history->cuboids[i].length, history->cuboids[i].height, history->cuboids[i].area, history->cuboids[i].volume);
            printf("   |______________________|__________________|__________________|__________________|____________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", means[0], means[1], means[2], means[3], means[4]);
        printf("   |______________________|__________________|__________________|__________________|____________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", stds[0], stds[1], stds[2], stds[3], stds[4]);
        printf("   |______________________|__________________|__________________|__________________|____________________|____________________|\n");

        break;

    case Cube:
        printf("Cube\n");
        printf("    ___________________________________________________________________________________\n");
        printf("   |         Index        |    Side Length   |    Surface Area    |       Volume       |\n");
        printf("   |______________________|__________________|____________________|____________________|\n");

        for (i = 0; i < history->count[4]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", i, history->cubes[i].length, history->cubes[i].area, history->cubes[i].volume);
            printf("   |______________________|__________________|____________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", means[0], means[1], means[2]);
        printf("   |______________________|__________________|____________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", stds[0], stds[1], stds[2]);
        printf("   |______________________|__________________|____________________|____________________|\n");

        break;

    case Sphere:
        printf("Sphere\n");
        printf("    ___________________________________________________________________________________\n");
        printf("   |         Index        |      Radius      |    Surface Area    |       Volume       |\n");
        printf("   |______________________|__________________|____________________|____________________|\n");

        for (i = 0; i < history->count[6]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", i, history->spheres[i].radius, history->spheres[i].area, history->spheres[i].volume);
            printf("   |______________________|__________________|____________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", means[0], means[2], means[1]);
        printf("   |______________________|__________________|____________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", stds[0], stds[2], stds[1]);
        printf("   |______________________|__________________|____________________|____________________|\n");

        break;

    case Cone:
        printf("Cone\n");
        printf("    ______________________________________________________________________________________________________\n");
        printf("   |         Index        |      Radius      |      Height      |    Surface Area    |       Volume       |\n");
        printf("   |______________________|__________________|__________________|____________________|____________________|\n");

        for (i = 0; i < history->count[5]; i++)
        {
            printf("   |           %d          | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", i, history->cones[i].radius, history->cones[i].height, history->cones[i].area, history->cones[i].volume);
            printf("   |______________________|__________________|__________________|____________________|____________________|\n");
        }

        printf("   |         Mean         | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", means[0], means[1], means[3], means[2]);
        printf("   |______________________|__________________|__________________|____________________|____________________|\n");
        printf("   |  Standard Deviation  | %12.2g m   | %12.2g m   | %12.2g m^2   | %12.2g m^3   |\n", stds[0], stds[1], stds[3], stds[2]);
        printf("   |______________________|__________________|__________________|____________________|____________________|\n");

        break;
    }
}

#endif