#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

double GetNumericInput() {
    char input_value[10], *end_pointer;
    double numeric_input;

    while(true) {
        scanf("%s", input_value);

        numeric_input = strtod(input_value, &end_pointer);

        if (numeric_input != 0) {
            break;
        } else {
            printf("Invalid input! Please enter a numeric value!\n");
            printf("Enter again here: ");
        }
    }

    return numeric_input;
}

// Functions to calculate properties for differnt objects.
void CalculateRectangleProperties() {
    double width, height;
    double perimeter, area;

    printf("\nPlease provide these necessary parameters:\n");
    printf("Width: ");
    width = GetNumericInput();
    printf("Height: ");
    height = GetNumericInput();

    perimeter = 2 * (width + height);
    area = width * height;

    printf("\nCalculation results:\nPerimeter: %.2lf\tArea: %.2lf\n\n", perimeter, area);
}

void CalculateCircleProperties() {
    double radius;
    double circumference, area;

    printf("\nPlease provide this necessary parameter:\n");
    printf("Radius: ");
    radius = GetNumericInput();

    circumference = 2 * M_PI * radius;
    area = M_PI * pow(radius, 2);

    printf("\nCalculation results:\nCircumference: %.2lf\tArea: %.2lf\n\n", circumference, area);
}

void CalculateCubeProperties() {
    double length, width, height;
    double surface_area, volume;

    printf("\nPlease provide these necessary parameters:\n");
    printf("Length: ");
    length = GetNumericInput();
    printf("Width: ");
    width = GetNumericInput();
    printf("Height: ");
    height = GetNumericInput();

    surface_area = 2 * (length * width + length * height + width * height);
    volume = length * width * height;

    printf("\nCalculation results:\nSurface area: %.2lf\tVolume: %.2lf\n\n", surface_area, volume);
}

void CalculateConeProperties() {
    double radius, height;
    double surface_area, volume;

    printf("\nPlease provide these necessary parameters:\n");
    printf("Radius: ");
    radius = GetNumericInput();
    printf("Height: ");
    height = GetNumericInput();

    surface_area = M_PI * pow(radius, 2) + M_PI * radius * sqrt(pow(radius, 2) + pow(height, 2));
    volume = M_PI * pow(radius, 2) * height / 3.0;

    printf("\nCalculation results:\nSurface area: %.2lf\tVolume: %.2lf\n\n", surface_area, volume);
}

// Let user decide whether to calculate properties again or exit this program.
bool ContinueCalculationOrNot() {
    char exit_program_input[5]; 

    printf("Type in \"yes\" if you want to calculate again. Press any other key to exit the program.\n");
    printf("Your choice: ");

    scanf("%s", exit_program_input);
    for(int i = 0; exit_program_input[i]; i++) {
        exit_program_input[i] = tolower(exit_program_input[i]);
    }

    if (strcmp(exit_program_input, "yes") != 0) {
        return true;
    } else {
        printf("\n****************************************************************************\n\n");
        return false;
    }
}

void main() {
    printf("****************************************************************************\n");
    printf("********************* Nanyang Technological University *********************\n");
    printf("********** Realtime System for Mechatronics Software (MA4830)-CA1 **********\n");
    printf("****************************************************************************\n\n");

    char object_name[10];
    printf("Program-Calculate Properties of a Object:\n\n");

    while (true) {
        printf("Select a object from the following list and key in its name:\nRectangle\tCircle\nCube\t\tCone\n\n(Type \"exit\" to leave the program.)\n\n");
        printf("Type in your choice here: ");

        // Conver the input characters to lower-case for string comparison.
        scanf("%s", object_name);
        for(int i = 0; object_name[i]; i++) {
            object_name[i] = tolower(object_name[i]);
        }

        if (strcmp(object_name, "rectangle") == 0) { 
            CalculateRectangleProperties();

            if (ContinueCalculationOrNot()) {
                break;
            }
        } else if (strcmp(object_name, "circle") == 0) {
            CalculateCircleProperties();
            
            if (ContinueCalculationOrNot()) {
                break;
            }
        } else if (strcmp(object_name, "cube") == 0) {
            CalculateCubeProperties();

            if (ContinueCalculationOrNot()) {
                break;
            }
        } else if (strcmp(object_name, "cone") == 0) {
            CalculateConeProperties();
            
            if (ContinueCalculationOrNot()) {
                break;
            }
        } else if (strcmp(object_name, "exit") == 0) {
            break;
        } else { // Let user type again if the input string is different from all desired ones.
            printf("\n****************************************************************************\n");
            printf("************** Invalid input! Please follow the instructions! **************\n");
            printf("****************************************************************************\n\n");
        }
    }
}