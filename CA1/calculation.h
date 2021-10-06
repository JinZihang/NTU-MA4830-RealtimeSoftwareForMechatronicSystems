#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

double input() {
    fgets()
}

void CalculateProperties(enum shape shape, struct History *history) {
    enum unit unit;

    UnitSelection(&unit);

    int rectangleCount = 0;

    switch (shape)
    {
    case Rectangle:
        switch (unit)
        {
        case /* constant-expression */:
            /* code */
            break;
        
        }
        history->rectangles[rectangleCount].length = input();
        history->rectangles[rectangleCount].width = input();

        history->rectangles[rectangleCount].perimeter = 2*(width + height);
        history->rectangles[rectangleCount].area = width * height;

        CalculateProperties(unit, shape, result_1, result_2);
        break;
    
    default:
        break;
    }


    // input param; -> width and height

    // calculation steps -> result 1 result 2

    CalculationResults(unit, shape, result_1, result_2);
    
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

#endif