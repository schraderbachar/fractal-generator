#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <math.h>
#include <time.h>

int julia(double rOffset, double iOffset, double sr, double si, int maxIterations, int escapeRadius)
{
    int i = 0;
    double zr = sr, zi = si;
    while (i < maxIterations && zr * zr + zi * zi < (escapeRadius * escapeRadius))
    {
        double temp = zr * zr - zi * zi + rOffset;
        zi = 2.0 * zr * zi + iOffset;
        zr = temp;
        i++;
    }

    return i;
}

int mandelbrot(double sr, double si, int maxIterations)
{
    int i = 0;
    double zr = 0.0, zi = 0.0;
    while (i < maxIterations && zr * zr + zi * zi < 4.0)
    {
        double temp = zr * zr - zi * zi + sr;
        zi = 2.0 * zr * zi + si;
        zr = temp;
        i++;
    }

    return i;
}