#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

// Process control functions.
double GetNumericInput() {
    char input_value[10], *end_pointer;
    double numeric_input;

    while (true) {
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
bool ContinueCalculationOrNot() { // Let user decide whether to calculate properties again or exit this program.
    char exit_program_input[5]; 

    printf("Type in \"yes\" if you want to calculate again. Key in any other thing to exit the program.\n");
    printf("Your choice: ");

    scanf("%s", exit_program_input);
    for(int i = 0; exit_program_input[i]; i++) {
        exit_program_input[i] = tolower(exit_program_input[i]);
    }

    if (strcmp(exit_program_input, "yes") != 0) {
        return true;
    } else {
        printf("\n============================================================================");
        return false;
    }
}

// Functions to calculate properties for differnt objects.
// 2D objects:
void Calculate2DRectangleProperties(bool isCube) {
    double width, height;
    double perimeter, area;

    printf("\nPlease provide these necessary parameters:\n");
    if (isCube) {
        printf("Side length: ");
    } else {
        printf("Width: ");
    }
    width = GetNumericInput();
    if (isCube) {
        height = width;
    } else {
        printf("Height: ");
        height = GetNumericInput();
    }

    perimeter = 2 * (width + height);
    area = width * height;

    printf("\nCalculation results:\nPerimeter: %.2lf\tArea: %.2lf\n\n", perimeter, area);
}
void Calculate2DCircleProperties() {
    double radius;
    double circumference, area;

    printf("\nPlease provide this necessary parameter:\n");
    printf("Radius: ");
    radius = GetNumericInput();

    circumference = 2 * M_PI * radius;
    area = M_PI * pow(radius, 2);

    printf("\nCalculation results:\nCircumference: %.2lf\tArea: %.2lf\n\n", circumference, area);
}
// 3D Objects:
void Calculate3DCuboidProperties(bool isCube) {
    double length, width, height;
    double surface_area, volume;

    printf("\nPlease provide these necessary parameters:\n");
    if (isCube) {
        printf("Side length: ");
    } else {
        printf("Length: ");
    }
    length = GetNumericInput();
    if (isCube) {
        width = length;
        height = length;
    } else {
        printf("Width: ");
        width = GetNumericInput();
        printf("Height: ");
        height = GetNumericInput();
    }

    surface_area = 2 * (length * width + length * height + width * height);
    volume = length * width * height;

    printf("\nCalculation results:\nSurface area: %.2lf\tVolume: %.2lf\n\n", surface_area, volume);
}
void Calculate3DCircleProperties() {
    double radius;
    double surface_area, volume;

    printf("\nPlease provide these necessary parameters:\n");
    printf("Radius: ");
    radius = GetNumericInput();

    surface_area = 4.0 * M_PI * pow(radius, 2);
    volume = M_PI * pow(radius, 3) * 4.0  / 3.0;

    printf("\nCalculation results:\nSurface area: %.2lf\tVolume: %.2lf\n\n", surface_area, volume);
}
void Calculate3DConeProperties() {
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

void main() {
    printf("****************************************************************************\n");
    printf("********************* Nanyang Technological University *********************\n");
    printf("********** Realtime System for Mechatronics Software (MA4830)-CA1 **********\n");
    printf("****************************************************************************\n");
    printf("********************************* Program **********************************\n");
    printf("********************* Calculate Properties of an Object ********************\n");
    printf("****************************************************************************\n\n");

    char object_dimension[5], object_name[10];
    
    while (true) {
        while (true) { // Let user select whether to calculate 2D object's properties or 3D object's properties.
            printf("\n============================================================================\n");
            printf("Calculate 2D or 3D object's properties? Type \"exit\" to leave the program:\n2D\t3D\n");
            printf("Type in your choice here: ");

            scanf("%s", object_dimension);
            for (int i = 0; object_dimension[i]; i++) { // Conver the input characters to lower-case for string comparison.
                object_dimension[i] = tolower(object_dimension[i]);
            }

            // Analyse the input.
            if (strcmp(object_dimension, "2d") == 0 || strcmp(object_dimension, "3d") == 0 || strcmp(object_dimension, "exit") == 0) {
                break;
            } else { // Let user type again if the input is different from all desired ones.
                printf("\n============================================================================\n");
                printf("************** Invalid input! Please follow the instructions! **************\n");
                printf("************************** (Key in \"2D\" or \"3D\".) **************************\n");
                printf("============================================================================\n\n");
            }
        }
        
        if (strcmp(object_dimension, "exit") == 0) {
            break;
        } else {
            while (true) {
                if (strcmp(object_dimension, "2d") == 0) { // Calculate 2D object's properties.
                    printf("\nSelect a object from the following list and key in its name:\n");
                    printf("Type \"back\" to reselect the object dimension, type \"exit\" to leave the program):\n");
                    printf("Rectangle\tSquare\nCircle\n");
                    printf("Type in your choice here: ");
        
                    scanf("%s", object_name);
                    for (int i = 0; object_name[i]; i++) {
                        object_name[i] = tolower(object_name[i]);
                    }

                    if (strcmp(object_name, "rectangle") == 0) { 
                        Calculate2DRectangleProperties(false);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "square") == 0) {
                        Calculate2DRectangleProperties(true);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "circle") == 0) {
                        Calculate2DCircleProperties(false);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "back") == 0) {
                        break;

                    } else if (strcmp(object_name, "exit") == 0) {
                        break;

                    } else { // Input does not match any of the desired one.
                        printf("\n============================================================================\n");
                        printf("============== Invalid input! Please follow the instructions! ==============\n");
                        printf("======= (Key in \"Rectangle\", \"Square\", \"Circle\", \"Back\" or \"Exit\".) ========\n");
                        printf("============================================================================\n\n");
                    }

                } else { // Calculate 3D object's properties.
                    printf("\nSelect a object from the following list and key in its name:\n");
                    printf("Type \"back\" to reselect the object dimension, type \"exit\" to leave the program):\n");
                    printf("Cuboid\t\tCube\nCircle\t\tCone\n");
                    printf("Type in your choice here: ");
        
                    scanf("%s", object_name);
                    for (int i = 0; object_name[i]; i++) {
                        object_name[i] = tolower(object_name[i]);
                    }

                    if (strcmp(object_name, "cuboid") == 0) { 
                        Calculate3DCuboidProperties(false);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "cube") == 0) {
                        Calculate3DCuboidProperties(true);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "circle") == 0) {
                        Calculate3DCircleProperties(false);
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "cone") == 0) {
                        Calculate3DConeProperties(false); 
                        if (ContinueCalculationOrNot()) break;

                    } else if (strcmp(object_name, "back") == 0) {
                        break;

                    } else if (strcmp(object_name, "exit") == 0) {
                        break;

                    } else { // Let user type again if the input string is different from all desired ones.
                        printf("\n============================================================================\n");
                        printf("============== Invalid input! Please follow the instructions! ==============\n");
                        printf("====== (Key in \"Cuboid\", \"Cube\", \"Circle\", \"Cone\", \"Back\" or \"Exit\".) ======\n");
                        printf("============================================================================\n\n");
                    }
                }
            }

            if (strcmp(object_name, "back") == 0) {
                continue;
            } else if (strcmp(object_name, "exit") == 0) {
                break;
            }
        }
        
    }
}
