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

bool ShapeSelection(enum shape *shape)
{
    char *input, *inputLowercase;
    unsigned char *char_ptr;

    ShapeSelectionInstructions();

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
        if (strcmp(inputLowercase, "rectangle\n") == 0 || strcmp(inputLowercase, "1\n") == 0)
        {
            *shape = Rectangle;
            printf("You have selected a rectangle.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "square\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            *shape = Square;
            printf("You have selected a square.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "circle\n") == 0 || strcmp(inputLowercase, "3\n") == 0)
        {
            *shape = Circle;
            printf("You have selected a circle.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "back\n") == 0)
        {
            return false;
        }
        else if (strcmp(inputLowercase, "exit\n") == 0)
        {
            exit(0);
        }
        else
        {
            WrongShapeInput();
        }
    }
}

bool ObjectSelection(enum shape *shape)
{
    char *input, *inputLowercase;
    unsigned char *char_ptr;

    ObjectSelectionInstructions();

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
        if (strcmp(inputLowercase, "cuboid\n") == 0 || strcmp(inputLowercase, "1\n") == 0)
        {
            *shape = Cuboid;
            printf("You have selected a cuboid.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "cube\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            *shape = Cube;
            printf("You have selected a cube.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "cone\n") == 0 || strcmp(inputLowercase, "3\n") == 0)
        {
            *shape = Cone;
            printf("You have selected a cone.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "sphere\n") == 0 || strcmp(inputLowercase, "4\n") == 0)
        {
            *shape = Sphere;
            printf("You have selected a sphere.\n");
            return true;
        }
        else if (strcmp(inputLowercase, "back\n") == 0)
        {
            return false;
        }
        else if (strcmp(inputLowercase, "exit\n") == 0)
        {
            exit(0);
        }
        else
        {
            WrongObjectInput();
        }
    }
}

bool GeometrySelection(enum shape *shape, int dimension)
{
    switch (dimension)
    {
    case 2:
        return ShapeSelection(&(*shape));
        break;
    case 3:
        return ObjectSelection(&(*shape));
        break;
    default:
        printf("Invalid dimension\n");
        break;
    }
    return false;
}

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

void UnitSelection(enum unit *unit)
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
        if (strcmp(input, "m\n") == 0)
        {
            *unit = m;
            free(input);
            return;
        }
        else if (strcmp(input, "dm\n") == 0)
        {
            *unit = dm;
            free(input);
            return;
        }
        else if (strcmp(input, "cm\n") == 0)
        {
            *unit = cm;
            free(input);
            return;
        }
        else if (strcmp(input, "mm\n") == 0)
        {
            *unit = mm;
            free(input);
            return;
        }
        else
        {
            WrongUnitInput();
        }
    }
}

bool ProcessSelection()
{
    char *input, *inputLowercase;
    unsigned char *char_ptr;

    ProcessSelectionInstructions();

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
        if (strcmp(inputLowercase, "history\n") == 0 || strcmp(inputLowercase, "1\n") == 0)
        {
            return true;
        }
        else if (strcmp(inputLowercase, "calculate\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            return false;
        }
        else if (strcmp(inputLowercase, "exit\n") == 0 || strcmp(inputLowercase, "3\n") == 0)
        {
            exit(0);
        }
        else
        {
            WrongProcessInput();
        }
    }
}

// void ShapeAndObjectSelection()
// {
//     char *input, *inputLowercase;
//     unsigned char *char_ptr;

//     DimensionSelectionInstructions();

//     while (true)
//     {
//         // Get input and convert the input to lowercase.
//         if ((input = (char *)malloc(100 * sizeof(char))) == NULL)
//         {
//             NoMemoryAlert();
//             exit(1);
//         }
//         fgets(input, 100 * sizeof(char), stdin);
//         inputLowercase = strdup(input);
//         free(input);
//         char_ptr = (unsigned char *)inputLowercase;
//         while (*char_ptr)
//         {
//             *char_ptr = tolower(*char_ptr);
//             char_ptr++;
//         }

//         // Actions based on the input.
//         if (strcmp(inputLowercase, "2d\n") == 0 || strcmp(inputLowercase, "1\n") == 0)
//         {
//             *dimension = 2;
//             return;
//         }
//         else if (strcmp(inputLowercase, "3d\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
//         {
//             *dimension = 3;
//             return;
//         }
//         else if (strcmp(inputLowercase, "exit\n") == 0)
//         {
//             exit(0);
//         }
//         else
//         {
//             WrongDimensionInput();
//         }
//     }
// }
#endif
