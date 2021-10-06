#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

double GetNumericInput()
{
    char input_value[10];
    double numeric_input;

    while (true)
    {
        scanf("%s", input_value);

        numeric_input = strtod(input_value, NULL);
        if (numeric_input != 0)
        {
            break;
        }
        else
        {
            printf("Invalid input! Please enter a numeric value!\n");
            printf("Enter again here: ");
        }
    }

    return numeric_input;
}

void CalculateProperties(enum shape shape, struct History *history)
{
    enum unit unit;
    int index, test;

    UnitSelection(&unit);

    switch (shape)
    {
    case Rectangle:

        test = GetNumericInput();
        printf("%lf", test);
        // switch (unit)
        // {
        // case m:
        //     history->rectangles[history->count[0]].width = GetNumericInput();
        //     history->rectangles[history->count[0]].length = GetNumericInput();
        //     break;

        // case dm:
        //     history->rectangles[history->count[0]].width = GetNumericInput() / 1E1;
        //     history->rectangles[history->count[0]].length = GetNumericInput() / 1E1;
        //     break;

        // case cm:
        //     history->rectangles[history->count[0]].width = GetNumericInput() / 1E2;
        //     history->rectangles[history->count[0]].length = GetNumericInput() / 1E2;
        //     break;

        // case mm:
        //     history->rectangles[history->count[0]].width = GetNumericInput() / 1E3;
        //     history->rectangles[history->count[0]].length = GetNumericInput() / 1E3;
        //     break;

        //     history->rectangles[history->count[0]].perimeter = 2 * (history->rectangles[history->count[0]].width + history->rectangles[history->count[0]].length);
        //     history->rectangles[history->count[0]].area = history->rectangles[history->count[0]].width * history->rectangles[history->count[0]].length;

        //     DisplayResults(shape, history->rectangles[history->count[0]].width, history->rectangles[history->count[0]].length);
        //     history->count[0]++;
        //     break;
        // }
    }
}

#endif