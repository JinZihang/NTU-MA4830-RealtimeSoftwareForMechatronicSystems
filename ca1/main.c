#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "datatypes/enum.h"
#include "datatypes/struct.h"

#include "functions/print.h"
#include "functions/selection.h"
#include "functions/calculation.h"

int main()
{
    int dimension, i;
    enum shape shape;
    struct History history;
    for (i = 0; i < 7; i++) // Initialize history count.
    {
        history.count[i] = 0;
    }

    DisplayTitle("assets/title.txt");

    while (true)
    {
        DimensionSelection(&dimension);

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