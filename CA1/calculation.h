#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

double GetParameterInput(void (*paramInstructions)())
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

    UnitSelection(&unit);

    switch (shape)
    {
    case Rectangle:
        switch (unit)
        {
        case m:
            history->rectangles[history->count[0]].width = GetParameterInput(WidthSelectionInstructions);
            history->rectangles[history->count[0]].length = GetParameterInput(LengthSelectionInstructions);
            break;

        case dm:
            history->rectangles[history->count[0]].width = GetParameterInput(WidthSelectionInstructions) / 1E1;
            history->rectangles[history->count[0]].length = GetParameterInput(LengthSelectionInstructions) / 1E1;
            break;

        case cm:
            history->rectangles[history->count[0]].width = GetParameterInput(WidthSelectionInstructions) / 1E2;
            history->rectangles[history->count[0]].length = GetParameterInput(LengthSelectionInstructions) / 1E2;
            break;

        case mm:
            history->rectangles[history->count[0]].width = GetParameterInput(WidthSelectionInstructions) / 1E3;
            history->rectangles[history->count[0]].length = GetParameterInput(LengthSelectionInstructions) / 1E3;
            break;
        }

        history->rectangles[history->count[0]].perimeter = 2 * (history->rectangles[history->count[0]].width + history->rectangles[history->count[0]].length);
        history->rectangles[history->count[0]].area = history->rectangles[history->count[0]].width * history->rectangles[history->count[0]].length;

        printf("Area is %lf\n", history->rectangles[history->count[0]].area);
        printf("Perimeter is %lf\n", history->rectangles[history->count[0]].perimeter);

        // DisplayResults(shape, history->rectangles[history->count[0]].perimeter, history->rectangles[history->count[0]].area);
        history->count[0]++;
        break;
    case Square:
        switch (unit)
        {
        case m:
            history->squares[history->count[1]].length = GetParameterInput(LengthSelectionInstructions);
            break;

        case dm:
            history->squares[history->count[1]].length = GetParameterInput(LengthSelectionInstructions) / 1E1;
            break;

        case cm:
            history->squares[history->count[1]].length = GetParameterInput(LengthSelectionInstructions) / 1E2;
            break;

        case mm:
            history->squares[history->count[1]].length = GetParameterInput(LengthSelectionInstructions) / 1E3;
            break;
        }

        history->squares[history->count[1]].perimeter = 4 * history->squares[history->count[1]].length;
        history->squares[history->count[1]].area = history->squares[history->count[1]].length * history->squares[history->count[1]].length;

        printf("Area is %lf\n", history->squares[history->count[1]].area);
        printf("Perimeter is %lf\n", history->squares[history->count[1]].perimeter);

        // DisplayResults(shape, history->squares[history->count[1]].perimeter, history->squares[history->count[1]].area);
        history->count[1]++;
        break;
    case Circle:
        switch (unit)
        {
        case m:
            history->circles[history->count[2]].radius = GetParameterInput(RadiusSelectionInstructions);
            break;

        case dm:
            history->circles[history->count[2]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E1;
            break;

        case cm:
            history->circles[history->count[2]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E2;
            break;

        case mm:
            history->circles[history->count[2]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E3;
            break;
        }

        history->circles[history->count[2]].circumference = 2 * M_PI * history->circles[history->count[2]].radius;
        history->circles[history->count[2]].area = M_PI * history->circles[history->count[2]].radius * history->circles[history->count[2]].radius;

        printf("Circumference is %lf\n", history->circles[history->count[2]].circumference);
        printf("Area is %lf\n", history->circles[history->count[2]].area);

        // DisplayResults(shape, history->circles[history->count[2]].circumference, history->circles[history->count[2]].area);
        history->count[2]++;
        break;
    case Cuboid:
        switch (unit)
        {
        case m:
            history->cuboids[history->count[3]].width = GetParameterInput(WidthSelectionInstructions);
            history->cuboids[history->count[3]].length = GetParameterInput(LengthSelectionInstructions);
            history->cuboids[history->count[3]].height = GetParameterInput(HeightSelectionInstructions);
            break;

        case dm:
            history->cuboids[history->count[3]].width = GetParameterInput(WidthSelectionInstructions) / 1E1;
            history->cuboids[history->count[3]].length = GetParameterInput(LengthSelectionInstructions) / 1E1;
            history->cuboids[history->count[3]].height = GetParameterInput(HeightSelectionInstructions) / 1E1;
            break;

        case cm:
            history->cuboids[history->count[3]].width = GetParameterInput(WidthSelectionInstructions) / 1E2;
            history->cuboids[history->count[3]].length = GetParameterInput(LengthSelectionInstructions) / 1E2;
            history->cuboids[history->count[3]].height = GetParameterInput(HeightSelectionInstructions) / 1E2;
            break;

        case mm:
            history->cuboids[history->count[3]].width = GetParameterInput(WidthSelectionInstructions) / 1E3;
            history->cuboids[history->count[3]].length = GetParameterInput(LengthSelectionInstructions) / 1E3;
            history->cuboids[history->count[3]].height = GetParameterInput(HeightSelectionInstructions) / 1E3;
            break;
        }

        history->cuboids[history->count[3]].volume = history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].length * history->cuboids[history->count[3]].height;
        history->cuboids[history->count[3]].area = 2 * (history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].length + history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].height + history->cuboids[history->count[3]].length * history->cuboids[history->count[3]].height);

        printf("Volume is %lf\n", history->cuboids[history->count[3]].volume);
        printf("Area is %lf\n", history->cuboids[history->count[3]].area);

        // DisplayResults(shape, history->cuboids[history->count[3]].area, history->cuboids[history->count[3]].volume);
        history->count[3]++;
        break;
    case Cube:
        switch (unit)
        {
        case m:
            history->cubes[history->count[4]].length = GetParameterInput(LengthSelectionInstructions);
            break;

        case dm:
            history->cubes[history->count[4]].length = GetParameterInput(LengthSelectionInstructions) / 1E1;
            break;

        case cm:
            history->cubes[history->count[4]].length = GetParameterInput(LengthSelectionInstructions) / 1E2;
            break;

        case mm:
            history->cubes[history->count[4]].length = GetParameterInput(LengthSelectionInstructions) / 1E3;
            break;
        }

        history->cubes[history->count[4]].volume = history->cubes[history->count[4]].length * history->cubes[history->count[4]].length * history->cubes[history->count[4]].length;
        history->cubes[history->count[4]].area = 6 * history->cubes[history->count[4]].length * history->cubes[history->count[4]].length;

        printf("Volume is %lf\n", history->cubes[history->count[4]].volume);
        printf("Area is %lf\n", history->cubes[history->count[4]].area);

        // DisplayResults(shape, history->cubes[history->count[4]].area, history->cubes[history->count[4]].volume);
        history->count[4]++;
        break;

    case Cone:
        switch (unit)
        {
        case m:
            history->cones[history->count[5]].radius = GetParameterInput(RadiusSelectionInstructions);
            history->cones[history->count[5]].height = GetParameterInput(HeightSelectionInstructions);
            break;

        case dm:
            history->cones[history->count[5]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E1;
            history->cones[history->count[5]].height = GetParameterInput(HeightSelectionInstructions) / 1E1;
            break;

        case cm:
            history->cones[history->count[5]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E2;
            history->cones[history->count[5]].height = GetParameterInput(HeightSelectionInstructions) / 1E2;
            break;

        case mm:
            history->cones[history->count[5]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E3;
            history->cones[history->count[5]].height = GetParameterInput(HeightSelectionInstructions) / 1E3;
            break;
        }

        history->cones[history->count[5]].volume = M_PI * history->cones[history->count[5]].radius * history->cones[history->count[5]].radius * history->cones[history->count[5]].height / 3;
        history->cones[history->count[5]].area = M_PI * history->cones[history->count[5]].radius * (history->cones[history->count[5]].radius + sqrt(history->cones[history->count[5]].radius * history->cones[history->count[5]].radius + history->cones[history->count[5]].height * history->cones[history->count[5]].height));

        printf("Volume is %lf\n", history->cones[history->count[5]].volume);
        printf("Area is %lf\n", history->cones[history->count[5]].area);

        // DisplayResults(shape, history->cones[history->count[5]].area, history->cones[history->count[5]].volume);
        history->count[5]++;
        break;
    case Sphere:
        switch (unit)
        {
        case m:
            history->spheres[history->count[6]].radius = GetParameterInput(RadiusSelectionInstructions);
            break;

        case dm:
            history->spheres[history->count[6]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E1;
            break;

        case cm:
            history->spheres[history->count[6]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E2;
            break;

        case mm:
            history->spheres[history->count[6]].radius = GetParameterInput(RadiusSelectionInstructions) / 1E3;
            break;
        }

        history->spheres[history->count[6]].volume = 4 / 3 * M_PI * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius;
        history->spheres[history->count[6]].area = 4 * M_PI * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius;

        printf("Volume is %lf\n", history->spheres[history->count[6]].volume);
        printf("Area is %lf\n", history->spheres[history->count[6]].area);

        // DisplayResults(shape, history->spheres[history->count[6]].area, history->spheres[history->count[6]].volume);
        history->count[6]++;
        break;
    }
}

// void CalculateHistory(struct History *history)
// {
//     enum shape shape;

//     GeometrySelection(&shape, dimension);
// }
#endif