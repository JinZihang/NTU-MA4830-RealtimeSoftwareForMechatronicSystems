#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

#define ONES 1
#define TENS 10
#define HUNDREDS 100
#define THOUSANDS 1000

double GetParameterInput(void (*paramInstructions)(char *parameter), char *parameter)
{
    char *endptr, buffer[100];
    double number;

    (*paramInstructions)(parameter);

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

void AssignRectangleParameter(struct History *history, int base)
{
    history->rectangles[history->count[0]].width = GetParameterInput(ParamaterSelectionInstructions, "width") / base;
    history->rectangles[history->count[0]].length = GetParameterInput(ParamaterSelectionInstructions, "length") / base;
}

void GetRectangleParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignRectangleParameter(&(*history), ONES);
        break;

    case dm:
        AssignRectangleParameter(&(*history), TENS);
        break;

    case cm:
        AssignRectangleParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignRectangleParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignSquareParameter(struct History *history, int base)
{
    history->squares[history->count[1]].length = GetParameterInput(ParamaterSelectionInstructions, "length") / base;
}

void GetSquareParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignSquareParameter(&(*history), ONES);
        break;

    case dm:
        AssignSquareParameter(&(*history), TENS);
        break;

    case cm:
        AssignSquareParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignSquareParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignCircleParameter(struct History *history, int base)
{
    history->circles[history->count[2]].radius = GetParameterInput(ParamaterSelectionInstructions, "radius") / base;
}

void GetCircleParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignCircleParameter(&(*history), ONES);
        break;

    case dm:
        AssignCircleParameter(&(*history), TENS);
        break;

    case cm:
        AssignCircleParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignCircleParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignCuboidParameter(struct History *history, int base)
{
    history->cuboids[history->count[3]].width = GetParameterInput(ParamaterSelectionInstructions, "width") / base;
    history->cuboids[history->count[3]].length = GetParameterInput(ParamaterSelectionInstructions, "length") / base;
    history->cuboids[history->count[3]].height = GetParameterInput(ParamaterSelectionInstructions, "height") / base;
}

void GetCuboidParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignCuboidParameter(&(*history), ONES);
        break;

    case dm:
        AssignCuboidParameter(&(*history), TENS);
        break;

    case cm:
        AssignCuboidParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignCuboidParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignCubeParameter(struct History *history, int base)
{
    history->cubes[history->count[4]].length = GetParameterInput(ParamaterSelectionInstructions, "length") / base;
}

void GetCubeParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignCubeParameter(&(*history), ONES);
        break;

    case dm:
        AssignCubeParameter(&(*history), TENS);
        break;

    case cm:
        AssignCubeParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignCubeParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignConeParameter(struct History *history, int base)
{
    history->cones[history->count[5]].radius = GetParameterInput(ParamaterSelectionInstructions, "radius") / base;
    history->cones[history->count[5]].height = GetParameterInput(ParamaterSelectionInstructions, "height") / base;
}

void GetConeParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignConeParameter(&(*history), ONES);
        break;

    case dm:
        AssignConeParameter(&(*history), TENS);
        break;

    case cm:
        AssignConeParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignConeParameter(&(*history), THOUSANDS);
        break;
    }
}

void AssignSphereParameter(struct History *history, int base)
{
    history->spheres[history->count[6]].radius = GetParameterInput(ParamaterSelectionInstructions, "radius") / base;
}

void GetSphereParameter(struct History *history, enum unit *unit)
{
    switch (*unit)
    {
    case m:
        AssignSphereParameter(&(*history), ONES);
        break;

    case dm:
        AssignSphereParameter(&(*history), TENS);
        break;

    case cm:
        AssignSphereParameter(&(*history), HUNDREDS);
        break;

    case mm:
        AssignSphereParameter(&(*history), THOUSANDS);
        break;
    }
}

void CalculateProperties(enum shape shape, struct History *history)
{
    enum unit unit;

    UnitSelection(&unit);

    switch (shape)
    {
    case Rectangle:
        GetRectangleParameter(&(*history), &unit);

        history->rectangles[history->count[0]].perimeter = 2 * (history->rectangles[history->count[0]].width + history->rectangles[history->count[0]].length);
        history->rectangles[history->count[0]].area = history->rectangles[history->count[0]].width * history->rectangles[history->count[0]].length;

        printf("Area is %lf\n", history->rectangles[history->count[0]].area);
        printf("Perimeter is %lf\n", history->rectangles[history->count[0]].perimeter);

        DisplayResults(shape, history->rectangles[history->count[0]].perimeter, history->rectangles[history->count[0]].area);
        history->count[0]++;
        break;
    case Square:
        GetSquareParameter(&(*history), &unit);

        history->squares[history->count[1]].perimeter = 4 * history->squares[history->count[1]].length;
        history->squares[history->count[1]].area = history->squares[history->count[1]].length * history->squares[history->count[1]].length;

        printf("Area is %lf\n", history->squares[history->count[1]].area);
        printf("Perimeter is %lf\n", history->squares[history->count[1]].perimeter);

        // DisplayResults(shape, history->squares[history->count[1]].perimeter, history->squares[history->count[1]].area);
        history->count[1]++;
        break;
    case Circle:
        GetCircleParameter(&(*history), &unit);

        history->circles[history->count[2]].circumference = 2 * M_PI * history->circles[history->count[2]].radius;
        history->circles[history->count[2]].area = M_PI * history->circles[history->count[2]].radius * history->circles[history->count[2]].radius;

        printf("Circumference is %lf\n", history->circles[history->count[2]].circumference);
        printf("Area is %lf\n", history->circles[history->count[2]].area);

        DisplayResults(shape, history->circles[history->count[2]].circumference, history->circles[history->count[2]].area);
        history->count[2]++;
        break;
    case Cuboid:
        GetCuboidParameter(&(*history), &unit);

        history->cuboids[history->count[3]].volume = history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].length * history->cuboids[history->count[3]].height;
        history->cuboids[history->count[3]].area = 2 * (history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].length + history->cuboids[history->count[3]].width * history->cuboids[history->count[3]].height + history->cuboids[history->count[3]].length * history->cuboids[history->count[3]].height);

        printf("Volume is %lf\n", history->cuboids[history->count[3]].volume);
        printf("Area is %lf\n", history->cuboids[history->count[3]].area);

        // DisplayResults(shape, history->cuboids[history->count[3]].area, history->cuboids[history->count[3]].volume);
        history->count[3]++;
        break;
    case Cube:
        GetCubeParameter(&(*history), &unit);

        history->cubes[history->count[4]].volume = history->cubes[history->count[4]].length * history->cubes[history->count[4]].length * history->cubes[history->count[4]].length;
        history->cubes[history->count[4]].area = 6 * history->cubes[history->count[4]].length * history->cubes[history->count[4]].length;

        printf("Volume is %lf\n", history->cubes[history->count[4]].volume);
        printf("Area is %lf\n", history->cubes[history->count[4]].area);

        // DisplayResults(shape, history->cubes[history->count[4]].area, history->cubes[history->count[4]].volume);
        history->count[4]++;
        break;

    case Cone:
        GetConeParameter(&(*history), &unit);

        history->cones[history->count[5]].volume = M_PI * history->cones[history->count[5]].radius * history->cones[history->count[5]].radius * history->cones[history->count[5]].height / 3;
        history->cones[history->count[5]].area = M_PI * history->cones[history->count[5]].radius * (history->cones[history->count[5]].radius + sqrt(history->cones[history->count[5]].radius * history->cones[history->count[5]].radius + history->cones[history->count[5]].height * history->cones[history->count[5]].height));

        printf("Volume is %lf\n", history->cones[history->count[5]].volume);
        printf("Area is %lf\n", history->cones[history->count[5]].area);

        // DisplayResults(shape, history->cones[history->count[5]].area, history->cones[history->count[5]].volume);
        history->count[5]++;
        break;
    case Sphere:
        GetSphereParameter(&(*history), &unit);

        history->spheres[history->count[6]].volume = 4 / 3 * M_PI * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius;
        history->spheres[history->count[6]].area = 4 * M_PI * history->spheres[history->count[6]].radius * history->spheres[history->count[6]].radius;

        printf("Volume is %lf\n", history->spheres[history->count[6]].volume);
        printf("Area is %lf\n", history->spheres[history->count[6]].area);

        // DisplayResults(shape, history->spheres[history->count[6]].area, history->spheres[history->count[6]].volume);
        history->count[6]++;
        break;
    }
}

void CalculateHistoricalProperties(struct History *history)
{
    enum shape shape;
    int i;
    float mean_result_1 = 0, mean_result_2 = 0, std_result_1, std_result_2;

    ShapeAndObjectSelection(&shape);

    switch (shape)
    {
    case Rectangle:
        for (i = 0; i < history->count[0]; i++)
        {
            mean_result_1 += history->rectangles[i].perimeter;
            mean_result_2 += history->rectangles[i].area;

            DisplayResults(shape, history->rectangles[i].perimeter, history->rectangles[i].area);
        }

        mean_result_1 /= history->count[0];
        mean_result_2 /= history->count[0];

        for (i = 0; i < history->count[0]; i++)
        {
            std_result_1 += pow(history->rectangles[i].perimeter - mean_result_1, 2);
            std_result_2 += pow(history->rectangles[i].area - mean_result_2, 2);
        }

        std_result_1 = sqrt(std_result_1 / history->count[0]);
        std_result_2 = sqrt(std_result_2 / history->count[0]);

        printf("mean1: %lf\n", mean_result_1);
        printf("mean2: %lf\n", mean_result_2);

        printf("std1: %lf\n", std_result_1);
        printf("std2: %lf\n", std_result_2);
        break;
    }
}

#endif