#ifndef PRINT
#define PRINT

#include <stdbool.h>

#include "enum.h"

#define MAX_LEN 128

void PrintImage(FILE *fptr)
{
    char read_string[MAX_LEN];

    while (fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);
}

void DimensionSelectionInstructions() {
    printf("\n============================================================================\n");
    printf("Calculate 2D or 3D object's properties? Type \"Exit\" if you want to leave the program:\n");
    printf("1. 2D\n2. 3D\n");
    printf("Type in your choice here: ");
}

void WrongDimensionInput() {
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("============ Key in \"2D\", \"3D\" or the choice index (\"1\" or \"2\"). ===========\n");
    printf("===================== Type \"Exit\" to leave the program. ====================\n");
    printf("============================================================================\n\n");
    printf("Type in your choice here: ");
}

void NoMemoryAlert() {
    printf("Not enough memory!");
}

void UnitSelectionInstructions() {
    printf("\nSelect the input unit:\n");
    printf("m\tdm\tcm\tmm\n");
    printf("Your choice: ");
}

void WrongUnitInput() {
    printf("\n============================================================================\n");
    printf("============== Invalid input! Please follow the instructions! ==============\n");
    printf("================== Enter \"m\", \"dm\", \"cm\" or \"mm\". ==================\n");
    printf("============================================================================\n\n");
    printf("Enter again here: ");
}

void CalculationResults(enum unit unit, enum shape shape, double result_1, double result_2) {
    bool is2D = false;

    printf("\nCalculation results:\n");

    if (shape == Rectangle || shape == Square || shape == Triangle || shape == Circle) {
        is2D = true;
    }

    if (is2D) {
        if (shape != Circle) {
            printf("   |    Perimeter  | ");
        } else {
            printf("   | Circumference | ");
        }

        switch (unit) {
            case m:
                printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1, result_1*10, result_1*1E2, result_1*1E3);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2, result_2*1E2, result_2*1E4, result_2*1E6);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                break;
        
            case dm:
                printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1/10, result_1, result_1*10, result_1*1E2);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2/1E2, result_2, result_2*1E2, result_2*1E4);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                break;

            case cm:
                printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1/1E2, result_1/10, result_1, result_1*10);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2/1E4, result_2/1E2, result_2, result_2*1E2);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                break;

            case mm:
                printf("%12.2g m   | %12.2g dm   | %12.2g cm   | %12.2g mm   |\n", result_1/1E3, result_1/1E2, result_1/10, result_1);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                printf("   |      Area     | %12.2g m^2 | %12.2g dm^2 | %12.2g cm^2 | %12.2g mm^2 |\n", result_2/1E6, result_2/1E4, result_2/1E2, result_2);
                printf("   |_______________|__________________|___________________|___________________|___________________|\n");
                break;
        }

    } else {
        switch (unit) {
            case m:
                printf("    _________________________________________________________________________________________________________\n");
                printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1, result_1*1E2, result_1*1E4, result_1*1E6);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2, result_2*1E3, result_2*1E6, result_2*1E9);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                break;
        
            case dm:
                printf("    _________________________________________________________________________________________________________\n");
                printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1/1E2, result_1, result_1*1E2, result_1*1E4);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2/1E3, result_2, result_2*1E3, result_2*1E6);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                break;

            case cm:
                printf("    _________________________________________________________________________________________________________\n");
                printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1/1E4, result_1/1E2, result_1, result_1*1E2);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2/1E6, result_2/1E3, result_2, result_2*1E3);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                break;

            case mm:
                printf("    _________________________________________________________________________________________________________\n");
                printf("   |    Surface area  | %12.2g m^2   | %12.2g dm^2   | %12.2g cm^2   | %12.2g mm^2   |\n", result_1/1E6, result_1/1E4, result_1/1E2, result_1);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                printf("   |      Volume      | %12.2g m^3   | %12.2g dm^3   | %12.2g cm^3   | %12.2g mm^3   |\n", result_2/1E9, result_2/1E6, result_2/1E3, result_2);
                printf("   |__________________|____________________|_____________________|_____________________|_____________________|\n");
                break;
        }
    }
}

void ProcessSelectionInstructions() {
    printf("Type in\n");
    printf("1. History\t- To view the calculation history.\n");
    printf("2. Calculate\t- To calculate again.\n");
    printf("2. Exit\t- To leave the program.\n");
    printf("Your choice: ");
}

#endif