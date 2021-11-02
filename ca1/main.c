#include <stdbool.h>

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

    // Initialize history count.
    for (i = 0; i < 7; i++)
    {
        history.count[i] = 0;
    }

    // CMake path, use different path to run from different directory. For example, "assets/title.txt".
    DisplayTitle("../ca1/assets/title.txt");

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