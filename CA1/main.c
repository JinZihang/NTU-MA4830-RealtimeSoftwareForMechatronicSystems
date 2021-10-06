#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "print.h"
#include "selection.h"
#include "enum.h"

int main()
{
    int dimension;
    enum shape shape;
    char *filename = "title.txt";
    FILE *fptr = NULL;

    // Print the title.
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "error opening %s\n", filename);
        return 1;
    }
    PrintImage(fptr);

    while (true)
    { // outer loop
        DimensionSelection(&dimension);
        printf("Dimension selected is %d\n", dimension);

        GeometrySelection(&shape, dimension);

        //     // calculation function (shape_or_object_selected) -> calculation_result
        //     // unit selection
        //     // param selection
        //     switch (shapeResult)
        //     {
        //     case Rectangle:
        //         printf("Rectangle\n");
        //         break;
        //     case Square:
        //         printf("Square\n");
        //         break;
        //     case Triangle:
        //         printf("Trinagle\n");
        //         break;
        //     case Circle:
        //         printf("Circle\n");
        //         break;
        //     case Cuboid:
        //         printf("Cubeoid\n");
        //         break;
        //     case Cube:
        //         printf("Cube\n");
        //         break;
        //     case Cone:
        //         printf("Cone\n");
        //         break;
        //     case Sphere:
        //         printf("Sphere\n");
        //         break;
        //     default:
        //         break;
        //     }
        //     break;
        //     // display(calculatioon_result)
        //     // histroy/calculate/exit
    }

    return 0;
}