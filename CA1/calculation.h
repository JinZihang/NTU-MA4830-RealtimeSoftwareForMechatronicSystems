#ifndef CALCULATION
#define CALCULATION

#include "struct.h"

#include "struct.h"
#include "enum.h"

void CalculateProperties(enum shape shape, struct History *history)
{
    int rectangleCount = 0;

    switch (shape)
    {
    case Rectangle:
        history->rectangles[rectangleCount].length = 2;
        history->rectangles[rectangleCount].width = 3;
        history->rectangles[rectangleCount].area = 6;
        history->rectangles[rectangleCount].perimeter = 10;
        break;
    default:
        break;
    }
}

#endif