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

bool ShapeSelection(int *shapeNumber)
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
            *shapeNumber = 1;
            return true;
        }
        else if (strcmp(inputLowercase, "square\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            *shapeNumber = 2;
            return true;
        }
        else if (strcmp(inputLowercase, "circle\n") == 0 || strcmp(inputLowercase, "3\n") == 0)
        {
            *shapeNumber = 3;
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

bool ObjectSelection(int *shapeNumber)
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
            *shapeNumber = 1;
            return true;
        }
        else if (strcmp(inputLowercase, "cube\n") == 0 || strcmp(inputLowercase, "2\n") == 0)
        {
            *shapeNumber = 2;
            return true;
        }
        else if (strcmp(inputLowercase, "cone\n") == 0 || strcmp(inputLowercase, "3\n") == 0)
        {
            *shapeNumber = 3;
            return true;
        }
        else if (strcmp(inputLowercase, "sphere\n") == 0 || strcmp(inputLowercase, "4\n") == 0)
        {
            *shapeNumber = 4;
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
    int shapeNumber;

    switch (dimension)
    {
    case 2:
        if (ShapeSelection(&shapeNumber))
        {
            switch (shapeNumber)
            {
            case 1:
                *shape = Rectangle;
                printf("Rectangle selected\n");
                break;
            case 2:
                *shape = Square;
                printf("Square selected\n");
                break;
            case 3:
                *shape = Circle;
                printf("Circle selected\n");
                break;
            }
        }
        else
        {
            return false;
        }
        break;
    case 3:
        if (ObjectSelection(&shapeNumber))
        {
            switch (shapeNumber)
            {
            case 1:
                *shape = Cuboid;
                printf("Cuboid selected\n");
                break;
            case 2:
                *shape = Cube;
                printf("Cube selected\n");
                break;
            case 3:
                *shape = Cone;
                printf("Cone selected\n");
                break;
            case 4:
                *shape = Sphere;
                printf("Sphere selected\n");
                break;
            }
        }
        else
        {
            return false;
        }
        break;
    default:
        printf("Invalid dimension\n");
        break;
    }
    return true;
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

void ProcessSelection()
{
    ProcessSelectionInstructions();
}

#endif
