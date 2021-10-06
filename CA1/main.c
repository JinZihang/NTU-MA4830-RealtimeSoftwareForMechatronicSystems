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
#include "calculation.h"

int main()
{
    int dimension;
    enum shape shape;
    struct History history;
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

        CalculateProperties(shape, &history);

        //     // calculation function (shape_or_object_selected) -> calculation_result
        //      // unit = unit selection
        //      // param = param selection
        // cal
        //      // display(unit, result) ->

        /// reurn
        //     // histroy/calculate/exit
    }

    return 0;
}