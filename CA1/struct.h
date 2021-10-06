#ifndef STRUCT
#define STRUCT

struct Rectangle
{
    double width;
    double length;

    double perimeter;
    double area;
};

struct Square
{
    double length;

    double perimeter;
    double area;
};

struct Circle
{
    double radius;
    double circumference;

    double area;
};

struct Cuboid
{
    double width;
    double length;
    double height;

    double area;
    double volume;
};

struct Cube
{
    double length;

    double area;
    double volume;
};

struct Sphere
{
    double radius;

    double area;
    double volume;
};

struct Cone
{
    double radius;
    double height;

    double area;
    double volume;
};

struct History
{
    int count[7];
    struct Rectangle rectangles[10];
    struct Square squares[10];
    struct Circle circles[10];
    struct Cuboid cuboids[10];
    struct Cube cubes[10];
    struct Sphere spheres[10];
    struct Cone cones[10];
};

#endif