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
    int dimension, i;
    enum shape shape;
    struct History history;
    char *filename = "title.txt"; //can be moved to main argument

    for (i = 0; i < 7; i++)
    {
        history.count[i] = 0;
    }

    PrintTitle(filename);

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