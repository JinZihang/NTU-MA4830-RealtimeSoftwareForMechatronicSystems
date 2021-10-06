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
    {
        DimensionSelection(&dimension);
        printf("Dimension selected is %d\n", dimension);

        if (!GeometrySelection(&shape, dimension))
        {
            continue;
        }

        CalculateProperties(shape, &history);

        while (ProcessSelection())
        {
            CalculateHistoricalProperties(&history);
        }
    }

    return 0;
}