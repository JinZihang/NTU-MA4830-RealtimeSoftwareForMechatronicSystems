#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

double GetParamterInput(void (*paramInstructions)())
{
    char *endptr, buffer[100];
    double number;

    (*paramInstructions)();

    while (fgets(buffer, sizeof(buffer), stdin))
    {
        number = strtod(buffer, &endptr);
        if (endptr == buffer || *endptr != '\n')
        {
            printf("Please enter a number: ");
        }
        else if (number < 0)
        {
            printf("Please enter a positive number: ");
        }
        else
        {
            return number;
        }
    }
}

void CalculateProperties(enum shape shape, struct History *history)
{
    enum unit unit;
    int index;

    UnitSelection(&unit);

    switch (shape)
    {
    case Rectangle:
        switch (unit)
        {
        case m:
            history->rectangles[history->count[0]].width = GetParamterInput(WidthSelectionInstructions);
            history->rectangles[history->count[0]].length = GetParamterInput(LengthSelectionInstructions);
            break;

        case dm:
            history->rectangles[history->count[0]].width = GetParamterInput(WidthSelectionInstructions) / 1E1;
            history->rectangles[history->count[0]].length = GetParamterInput(LengthSelectionInstructions) / 1E1;
            break;

        case cm:
            history->rectangles[history->count[0]].width = GetParamterInput(WidthSelectionInstructions) / 1E2;
            history->rectangles[history->count[0]].length = GetParamterInput(LengthSelectionInstructions) / 1E2;
            break;

        case mm:
            history->rectangles[history->count[0]].width = GetParamterInput(WidthSelectionInstructions) / 1E3;
            history->rectangles[history->count[0]].length = GetParamterInput(LengthSelectionInstructions) / 1E3;
            break;
        }

        history->rectangles[history->count[0]].perimeter = 2 * (history->rectangles[history->count[0]].width + history->rectangles[history->count[0]].length);
        history->rectangles[history->count[0]].area = history->rectangles[history->count[0]].width * history->rectangles[history->count[0]].length;

        DisplayResults(shape, history->rectangles[history->count[0]].perimeter, history->rectangles[history->count[0]].area);
        history->count[0]++;
        break;
    case Square:
        switch (unit)
        {
        case m:
            history->squares[history->count[1]].length = GetParamterInput(LengthSelectionInstructions);
            break;

        case dm:
            history->squares[history->count[1]].length = GetParamterInput(LengthSelectionInstructions) / 1E1;
            break;

        case cm:
            history->squares[history->count[1]].length = GetParamterInput(LengthSelectionInstructions) / 1E2;
            break;

        case mm:
            history->squares[history->count[1]].length = GetParamterInput(LengthSelectionInstructions) / 1E3;
            break;
        }

        history->squares[history->count[1]].perimeter = 4 * history->squares[history->count[1]].length;
        history->squares[history->count[1]].area = history->squares[history->count[1]].length * history->squares[history->count[1]].length;

        DisplayResults(shape, history->squares[history->count[1]].perimeter, history->squares[history->count[1]].area);
        history->count[1]++;
        break;
    case Circle:
        switch (unit)
        {
        case m:
            history->circles[history->count[2]].radius = GetParamterInput(RadiusSelectionInstructions);
            break;

        case dm:
            history->circles[history->count[2]].radius = GetParamterInput(RadiusSelectionInstructions) / 1E1;
            break;

        case cm:
            history->circles[history->count[2]].radius = GetParamterInput(RadiusSelectionInstructions) / 1E2;
            break;

        case mm:
            history->circles[history->count[2]].radius = GetParamterInput(RadiusSelectionInstructions) / 1E3;
            break;
        }

        history->circles[history->count[2]].circumference = 2 * M_PI * history->circles[history->count[2]].radius;
        history->circles[history->count[2]].area = M_PI * history->circles[history->count[2]].radius * history->circles[history->count[2]].radius;

        DisplayResults(shape, history->circles[history->count[2]].circumference, history->circles[history->count[2]].area);
        history->count[2]++;
        break;
    }
}

#endif