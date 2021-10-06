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

void ShapeSelection(enum shape *shapeResult, int dimensionResult)
{
    switch (dimensionResult)
    {
    case 2:
        Selection2D(shapeResult);
        printf("2D");
        break;
    case 3:
        // Selection3D(shapeResult);
        printf("3D");
        break;
    default:
        printf("Invalid dimension\n");
    }
}

void Selection2D(enum shape *shapeResult)
{
    int shapeNumber = 1;

    printf("1. Rectangle\n2. Square\n3. Triangle\n4. Circle\n");
    printf("Enter your choice: ");
    switch (shapeNumber)
    {
    case 1:
        *shapeResult = Rectangle;
        break;
    case 2:
        *shapeResult = Square;
        break;
    case 3:
        *shapeResult = Triangle;
        break;
    case 4:
        *shapeResult = Circle;
        break;
    default:
        printf("2D shape selection fail");
        break;
    }
}

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

#endif