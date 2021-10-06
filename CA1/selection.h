#ifndef SELECTION
#define SELECTION

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "print.h"
#include "enum.h"

// void ShapeSelection(enum shape *shapeResult, int dimensionResult)
// {
//     switch (dimensionResult)
//     {
//     case 2:
//         Selection2D(shapeResult);
//         printf("2D");
//         break;
//     case 3:
//         // Selection3D(shapeResult);
//         printf("3D");
//         break;
//     default:
//         printf("Invalid dimension\n");
//     }
// }

// void Selection2D(enum shape *shapeResult)
// {
//     int shapeNumber = 1;

//     printf("1. Rectangle\n2. Square\n3. Triangle\n4. Circle\n");
//     printf("Enter your choice: ");
//     switch (shapeNumber)
//     {
//     case 1:
//         *shapeResult = Rectangle;
//         break;
//     case 2:
//         *shapeResult = Square;
//         break;
//     case 3:
//         *shapeResult = Triangle;
//         break;
//     case 4:
//         *shapeResult = Circle;
//         break;
//     default:
//         printf("2D shape selection fail");
//         break;
//     }
// }

// void Selection3D(enum shape *shapeResult)
// {
//     int shapeNumber = 1;

//     printf("1. Cuboid\n2. Cube\n3. Cone\n4. Sphere\n");
//     printf("Enter your choice: ");
//     switch (shapeNumber)
//     {
//     case 1:
//         *shapeResult = Cuboid;
//         break;
//     case 2:
//         *shapeResult = Cube;
//         break;
//     case 3:
//         *shapeResult = Sphere;
//         break;
//     case 4:
//         *shapeResult = Cone;
//         break;
//     default:
//         printf("3D object selection fail");
//         break;
//     }
// }

void DimensionSelection(int *dimension)
{
    char *input, *inputLowercase;
    unsigned char *char_ptr;

    DimensionSelectionInstructions();

    while (true)
    {
        // Get input and convert the input to lowercase.
        if ((input = (char *)malloc(100 * sizeof(char))) == NULL)
        {
            NoMemoryAlert();
            exit(1);
        }
        fgets(input, 100 * sizeof(char), stdin);
        inputLowercase = strdup(input);
        free(input);
        char_ptr = (unsigned char *)inputLowercase;
        while (*char_ptr)
        {
            *char_ptr = tolower(*char_ptr);
            char_ptr++;
        }

        // Actions based on the input.
        if (strcmp(inputLowercase, "2d\n") == 0 || strcmp(inputLowercase, "1\n") == 0)
        {
            *dimension = 2;
            return;
        }
        else if (strcmp(inputLowercase, "3d\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            *dimension = 3;
            return;
        }
        else if (strcmp(inputLowercase, "exit\n") == 0)
        {
            exit(0);
        }
        else
        {
            WrongDimensionInput();
        }
    }
}

enum unit UnitSelection()
{
    char *input;

    UnitSelectionInstructions();

    while (true)
    {
        // Read the input.
        if ((input = (char *)malloc(100 * sizeof(char))) == NULL)
        {
            NoMemoryAlert();
            exit(1);
        }
        fgets(input, 100 * sizeof(char), stdin);

        // Actions based on the input.
        if (strcmp(input, "m") == 0)
        {
            free(input);
            return m;
        }
        else if (strcmp(input, "dm") == 0)
        {
            free(input);
            return dm;
        }
        else if (strcmp(input, "cm") == 0)
        {
            free(input);
            return cm;
        }
        else if (strcmp(input, "mm") == 0)
        {
            free(input);
            return mm;
        }
        else
        {
            WrongUnitInput();
        }
    }
}

#endif
