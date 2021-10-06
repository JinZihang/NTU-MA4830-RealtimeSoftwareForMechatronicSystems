#ifndef CALCULATION
#define CALCULATION

#include "selection.h"
#include "print.h"

#include "struct.h"
#include "enum.h"

void CalculateProperties(enum shape shape) {
    enum unit unit;
    UnitSelection(&unit);
    // input param;

    // calculation steps -> result 1 result 2

    CalculationResults(unit, shape, result_1, result_2);
}

#endif