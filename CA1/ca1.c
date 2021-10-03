#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define _USE_MATH_DEFINES
#include <math.h>

// Process control functions.
double GetNumericInput() {
    char input_value[10];
    double numeric_input;

    while (true) {
        scanf("%s", input_value);

        numeric_input = strtod(input_value, NULL);
        if (numeric_input != 0) {
            break;
        } else {
            printf("Invalid input! Please enter a numeric value!\n");
            printf("Enter again here: ");
        }
    }

    return numeric_input;
}
int SelectInputUnit() {
    int i;
    char input_value[3];

    printf("\nSelect the input unit:\n");
    printf("m\tdm\tcm\tmm\n");
    printf("Your choice: ");

    while (true) {
        scanf("%s", input_value);
        for (i = 0; input_value[i]; i++) {
            input_value[i] = tolower(input_value[i]);
        }

        if(strcmp(input_value, "m") == 0) {
            return 1;

        } else if (strcmp(input_value, "dm") == 0) {
            return 2;

        } else if (strcmp(input_value, "cm") == 0) {
            return 3;

        } else if (strcmp(input_value, "mm") == 0) {
            return 4;

        } else {
            printf("Invalid input! Please enter \"m\", \"dm\", \"cm\" or \"mm\"!\n");
            printf("Enter again here: ");
        }
    }
}
void Print2DObjectProperties(bool isRectangle, int inputUnit, double perimeterOrCircumference, double area) {
    printf("\nCalculation results:\n");

    if (isRectangle) {
        printf("Perimeter:\n\t");
    } else {
        printf("Circumference:\n\t");
    }
    
    switch (inputUnit) {
        case 1:
            printf("Circumference:\n\t%.3gm = %.3gdm = %.3gcm = %.3gmm\n", perimeterOrCircumference, perimeterOrCircumference*10, perimeterOrCircumference*1E2, perimeterOrCircumference*1E3);
            printf("Area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n\n", area, area*1E2, area*1E4, area*1E6);
            break;
    
        case 2:
            printf("Circumference:\n\t%.3gm = %.3gdm = %.3gcm = %.3gmm\n", perimeterOrCircumference/10, perimeterOrCircumference, perimeterOrCircumference*10, perimeterOrCircumference*1E2);
            printf("Area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n\n", area/1E2, area, area*1E2, area*1E4);
            break;

        case 3:
            printf("Circumference:\n\t%.3gm = %.3gdm = %.3gcm = %.3gmm\n", perimeterOrCircumference/1E2, perimeterOrCircumference/10, perimeterOrCircumference, perimeterOrCircumference*10);
            printf("Area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n\n", area/1E4, area/1E2, area, area*1E2);
            break;

        default:
            printf("Circumference:\n\t%.3gm = %.3gdm = %.3gcm = %.3gmm\n", perimeterOrCircumference/1E3, perimeterOrCircumference/1E2, perimeterOrCircumference/10, perimeterOrCircumference);
            printf("Area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n\n", area/1E6, area/1E4, area/1E2, area);
            break;
    }
}
void Print3DObjectProperties(int inputUnit, double surface_area, double volume) {
    printf("\nCalculation results:\n");
    switch (inputUnit) {
        case 1:
            printf("Surface area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n", surface_area, surface_area*1E2, surface_area*1E4, surface_area*1E6);
            printf("Volume:\n\t%.3gm^3 = %.3gdm^3 = %.3gcm^3 = %.3gmm^3\n\n", volume, volume*1E3, volume*1E6, volume*1E9);
            break;
    
        case 2:
            printf("Surface area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n", surface_area/1E2, surface_area, surface_area*1E2, surface_area*1E4);
            printf("Volume:\n\t%.3gm^3 = %.3gdm^3 = %.3gcm^3 = %.3gmm^3\n\n", volume/1E3, volume, volume*1E3, volume*1E6);
            break;

        case 3:
            printf("Surface area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n", surface_area/1E4, surface_area/1E2, surface_area, surface_area*1E2);
            printf("Volume:\n\t%.3gm^3 = %.3gdm^3 = %.3gcm^3 = %.3gmm^3\n\n", volume/1E6, volume/1E3, volume, volume*1E3);
            break;

        default:
            printf("Surface area:\n\t%.3gm^2 = %.3gdm^2 = %.3gcm^2 = %.3gmm^2\n", surface_area/1E6, surface_area/1E4, surface_area/1E2, surface_area);
            printf("Volume:\n\t%.3gm^3 = %.3gdm^3 = %.3gcm^3 = %.3gmm^3\n\n", volume/1E9, volume/1E6, volume/1E3, volume);
            break;
    }
}
bool ExitProgramOrNot() {
    int i;
    char exit_program_input[4]; 

    printf("Type in \"yes\" if you want to calculate again. Key in anything else to exit the program.\n");
    printf("Your choice: ");

    scanf("%s", exit_program_input);
    for(i = 0; exit_program_input[i]; i++) {
        exit_program_input[i] = tolower(exit_program_input[i]);
    }

    if (strcmp(exit_program_input, "yes") != 0) {
        return true;
    } else {
        return false;
    }
}
bool ContinueInThisDimensionOrNot() { // Let user decide whether to calculate properties again or exit this program.
    int i;
    char process_control_input[4]; 

    printf("Type in \"yes\" if you want to calculate for another object in this dimension. Key in anything else to reselect object's dimension.\n");
    printf("Your choice: ");

    scanf("%s", process_control_input);
    for(i = 0; process_control_input[i]; i++) {
        process_control_input[i] = tolower(process_control_input[i]);
    }

    if (strcmp(process_control_input, "yes") != 0) {
        return true;
    } else {
        printf("\n============================================================================");
        return false;
    }
}

// Functions to calculate properties for differnt objects.
// 2D objects:
void Calculate2DRectangleProperties(bool isSquare) {
    int inputUnit;
    double width, height;
    double perimeter, area;

    inputUnit = SelectInputUnit();
    printf("\nPlease provide these necessary parameters:\n");
    if (isSquare) {
        printf("Side length: ");
    } else {
        printf("Width: ");
    }
    width = GetNumericInput();
    if (isSquare) {
        height = width;
    } else {
        printf("Height: ");
        height = GetNumericInput();
    }

    perimeter = 2 * (width + height);
    area = width * height;

    Print2DObjectProperties(true, inputUnit, perimeter, area);
}
void Calculate2DCircleProperties() {
    int inputUnit;
    double radius;
    double circumference, area;

    inputUnit = SelectInputUnit();
    printf("\nPlease provide this necessary parameter:\n");
    printf("Radius: ");
    radius = GetNumericInput();

    circumference = 2 * M_PI * radius;
    area = M_PI * pow(radius, 2);

    Print2DObjectProperties(false, inputUnit, circumference, area);
}
// 3D Objects:
void Calculate3DCuboidProperties(bool isCube) {
    int inputUnit;
    double length, width, height;
    double surface_area, volume;

    inputUnit = SelectInputUnit();
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

    Print3DObjectProperties(inputUnit, surface_area, volume);
}
void Calculate3DSphereProperties() {
    int inputUnit;
    double radius;
    double surface_area, volume;

    inputUnit = SelectInputUnit();
    printf("\nPlease provide these necessary parameters:\n");
    printf("Radius: ");
    radius = GetNumericInput();

    surface_area = 4.0 * M_PI * pow(radius, 2);
    volume = M_PI * pow(radius, 3) * 4.0  / 3.0;

    Print3DObjectProperties(inputUnit, surface_area, volume);
}
void Calculate3DConeProperties() {
    int inputUnit;
    double radius, height;
    double surface_area, volume;

    inputUnit = SelectInputUnit();
    printf("\nPlease provide these necessary parameters:\n");
    printf("Radius: ");
    radius = GetNumericInput();
    printf("Height: ");
    height = GetNumericInput();

    surface_area = M_PI * pow(radius, 2) + M_PI * radius * sqrt(pow(radius, 2) + pow(height, 2));
    volume = M_PI * pow(radius, 2) * height / 3.0;

    Print3DObjectProperties(inputUnit, surface_area, volume);
}

void main() {
    int i;
    char object_dimension[4], object_name[10];
    bool exit_program = false;

    printf("****************************************************************************\n");
    printf("********************* Nanyang Technological University *********************\n");
    printf("********** Realtime Software for Mechatronic Systems (MA4830)-CA1 **********\n");
    printf("****************************************************************************\n");
    printf("********************************* Program **********************************\n");
    printf("********************* Calculate Properties of an Object ********************\n");
    printf("****************************************************************************\n\n");
    
    while (true) {
        while (true) { // Let user select whether to calculate 2D object's properties or 3D object's properties.
            printf("\n============================================================================\n");
            printf("Calculate 2D or 3D object's properties? Type \"exit\" to leave the program:\n2D\t3D\n");
            printf("Type in your choice here: ");

            scanf("%s", object_dimension);
            for (i = 0; object_dimension[i]; i++) { // Conver the input characters to lower-case for string comparison.
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
        
        // Actions based on the previous input.
        if (strcmp(object_dimension, "exit") == 0) {
            break;
        } else {
            while (true) {
                if (strcmp(object_dimension, "2d") == 0) { // Calculate 2D object's properties.
                    printf("\nSelect a object from the following list and key in its name:\n");
                    printf("Type \"back\" to reselect the object dimension, type \"exit\" to leave the program:\n");
                    printf("Rectangle\tSquare\nCircle\n");
                    printf("Type in your choice here: ");
        
                    scanf("%s", object_name);
                    for (i = 0; object_name[i]; i++) {
                        object_name[i] = tolower(object_name[i]);
                    }

                    if (strcmp(object_name, "rectangle") == 0) { 
                        Calculate2DRectangleProperties(false);

                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }
                        
                    } else if (strcmp(object_name, "square") == 0) {
                        Calculate2DRectangleProperties(true);
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

                    } else if (strcmp(object_name, "circle") == 0) {
                        Calculate2DCircleProperties(false);
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

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
                    printf("Type \"back\" to reselect the object dimension, type \"exit\" to leave the program:\n");
                    printf("Cuboid\t\tCube\nSphere\t\tCone\n");
                    printf("Type in your choice here: ");
        
                    scanf("%s", object_name);
                    for (i = 0; object_name[i]; i++) {
                        object_name[i] = tolower(object_name[i]);
                    }

                    if (strcmp(object_name, "cuboid") == 0) { 
                        Calculate3DCuboidProperties(false);
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

                    } else if (strcmp(object_name, "cube") == 0) {
                        Calculate3DCuboidProperties(true);
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

                    } else if (strcmp(object_name, "sphere") == 0) {
                        Calculate3DSphereProperties(false);
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

                    } else if (strcmp(object_name, "cone") == 0) {
                        Calculate3DConeProperties(false); 
                        
                        exit_program = ExitProgramOrNot();
                        if (!exit_program) {
                            if (ContinueInThisDimensionOrNot()) break;
                        } else {
                            break;
                        }

                    } else if (strcmp(object_name, "back") == 0) {
                        break;

                    } else if (strcmp(object_name, "exit") == 0) {
                        break;

                    } else { // Let user type again if the input string is different from all desired ones.
                        printf("\n============================================================================\n");
                        printf("============== Invalid input! Please follow the instructions! ==============\n");
                        printf("====== (Key in \"Cuboid\", \"Cube\", \"Sphere\", \"Cone\", \"Back\" or \"Exit\".) ======\n");
                        printf("============================================================================\n\n");
                    }
                }
            }

            if (exit_program) {
                break;
            }

            if (strcmp(object_name, "back") == 0) {
                continue;
            } else if (strcmp(object_name, "exit") == 0) {
                break;
            }
        }
    }
}