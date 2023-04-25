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

double scaleReal(int r, int imageWidth, double minR, double maxR)
{
    return r * ((maxR - minR) / imageWidth) + minR;
}

double scaleImaginary(int i, int imageHeight, double minI, double maxI)
{
    return i * ((maxI - minI) / imageHeight) + minI;
}

int main(int argc, char *argv[])
{
    int imageWidth, imageHeight, maxIterations, colorSelection, r, g, b, randomSeed, escapeRadius, repeat = 1, selection;
    double minR = -1.5, maxR = 0.7, minI = -1.0, maxI = 1.0, rOffset, iOffset;
    char *imageHeightTemp = new char[64];
    char *imageWidthTemp = new char[64];
    char *minRTemp = new char[64];
    char *maxRTemp = new char[64];
    char *minITemp = new char[64];
    char *maxITemp = new char[64];
    char *outputTemp = new char[64];
    char *maxIterationsTemp = new char[64];
    char *colorSelectionTemp = new char[64];
    char *randomSeedTemp = new char[64];
    char *escapeRadiusTemp = new char[64];
    char *rOffsetTemp = new char[64];
    char *iOffsetTemp = new char[64];
    int C1r, C1g, C1b, C2r, C2g, C2b, C3r, C3g, C3b, C4r, C4g, C4b, C5r, C5g, C5b;

    initscr();

    WINDOW *win = newwin(25, 50, 1, 1);
    refresh();

    while (repeat == 1)
    {
        wclear(win);
        box(win, 0, 0);

        mvwprintw(win, 1, 20, "Welcome!");
        mvwprintw(win, 2, 2, "Please select which type of fractal to create!");
        mvwprintw(win, 4, 2, "[1] Mandelbrot Set");
        mvwprintw(win, 5, 2, "[2] Julia Set");

        do
        {
            mvwprintw(win, 7, 2, "Selection:  ");
            refresh();
            wrefresh(win);

            selection = mvwgetch(win, 7, 13);
        } while (!(selection == '1' || selection == '2'));

        if (selection == '1') // mandlebrot
        {
            mvwprintw(win, 9, 2, "Mandelbrot Set! Excellent choice.");
            mvwprintw(win, 10, 2, "Image Height: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 10, 16, imageHeightTemp);
            imageHeight = atoi(imageHeightTemp) == 0 ? 512 : atoi(imageHeightTemp);

            mvwprintw(win, 11, 2, "Image Width: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 11, 15, imageWidthTemp);
            imageWidth = atoi(imageWidthTemp) == 0 ? 512 : atoi(imageWidthTemp);

            mvwprintw(win, 12, 2, "Minimum Real Value (Default = -1.5): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 12, 39, minRTemp);
            minR = atof(minRTemp) == 0 ? -1.5 : atof(minRTemp);

            mvwprintw(win, 13, 2, "Maximum Real Value (Default = 0.7): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 13, 39, maxRTemp);
            maxR = atof(maxRTemp) == 0 ? 0.7 : atof(maxRTemp);

            mvwprintw(win, 14, 2, "Minimum Imaginary Value (Default = -1.0): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 14, 44, minITemp);
            minI = atof(minITemp) == 0 ? -1.0 : atof(minITemp);

            mvwprintw(win, 15, 2, "Maximum Imaginary Value (Default = 1.0): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 15, 43, maxITemp);
            maxI = atof(maxITemp) == 0 ? 1.0 : atof(maxITemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 16, 2, "Maximum Iterations (Default = 255): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 16, 38, maxIterationsTemp);
            maxIterations = atoi(maxIterationsTemp) == 0 ? 255 : atoi(maxIterationsTemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 17, 2, "[1] Grayscale");
            mvwprintw(win, 18, 2, "[2] Random");
            mvwprintw(win, 19, 2, "Color Function: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 19, 18, colorSelectionTemp);
            colorSelection = atoi(colorSelectionTemp) == 0 ? 1 : atoi(colorSelectionTemp);
            refresh();
            wrefresh(win);

            if (colorSelection == 2)
            {
                mvwprintw(win, 19, 2, "Seed for random number:             ");
                refresh();
                wrefresh(win);

                mvwgetstr(win, 19, 8, randomSeedTemp);
                randomSeed = atoi(randomSeedTemp) == 0 ? time(NULL) : atoi(randomSeedTemp);
                srand(randomSeed);
                refresh();
                wrefresh(win);
                C1r = rand() % 256;
                C1g = rand() % 256;
                C1b = rand() % 256;

                C2r = rand() % 256;
                C2g = rand() % 256;
                C2b = rand() % 256;

                C3r = rand() % 256;
                C3g = rand() % 256;
                C3b = rand() % 256;

                C4r = rand() % 256;
                C4g = rand() % 256;
                C4b = rand() % 256;

                C5r = rand() % 256;
                C5g = rand() % 256;
                C5b = rand() % 256;
            }

            mvwprintw(win, 20, 2, "Output File Name: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 20, 20, outputTemp);

            mvwprintw(win, 21, 2, "Generating... Please be patient.");
            refresh();
            wrefresh(win);

            std::string output = outputTemp;
            output += ".ppm";

            std::ofstream fout(output);
            fout << "P3" << std::endl;
            fout << imageWidth << " " << imageHeight << std::endl;
            fout << "256" << std::endl;

            for (int y = 0; y < imageHeight; y++)
            {
                for (int x = 0; x < imageWidth; x++)
                {
                    double sr = scaleReal(x, imageWidth, minR, maxR);
                    double si = scaleImaginary(y, imageHeight, minI, maxI);

                    int n = mandelbrot(sr, si, maxIterations);

                    if (colorSelection == 1)
                    {
                        r = (n % 256);
                        g = (n % 256);
                        b = (n % 256);
                    }
                    else
                    {
                        int pos = (n % 4);
                        if (pos == 0)
                        {
                            r = C1r;
                            g = C1g;
                            b = C1b;
                        }
                        else if (pos == 1)
                        {
                            r = C2r;
                            g = C2g;
                            b = C2b;
                        }
                        else if (pos == 2)
                        {
                            r = C3r;
                            g = C3g;
                            b = C3b;
                        }
                        else if (pos == 3)
                        {
                            r = C4r;
                            g = C4g;
                            b = C4b;
                        }
                        else
                        {
                            r = C5r;
                            g = C5g;
                            b = C5b;
                        }
                    }

                    fout << r << " " << g << " " << b << " ";
                }
                fout << std::endl;
            }
            fout.close();
            mvwprintw(win, 21, 2, "                                ");
            mvwprintw(win, 21, 2, "Done!");
            mvwprintw(win, 22, 2, "Create Another (Y/N): ");
            refresh();
            wrefresh(win);
            int repeatT = mvwgetch(win, 22, 24);
            if (repeatT == 'Y' || repeatT == 'y')
            {
                repeat = 1;
            }
            else
            {
                repeat = 0;
            }
        }
        else if (selection == '2')
        {
            mvwprintw(win, 9, 2, "Julia Set! Great choice.");
            mvwprintw(win, 10, 2, "Image Height: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 10, 16, imageHeightTemp);
            imageHeight = atoi(imageHeightTemp) == 0 ? 512 : atoi(imageHeightTemp);

            mvwprintw(win, 11, 2, "Image Width: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 11, 15, imageWidthTemp);
            imageWidth = atoi(imageWidthTemp) == 0 ? 512 : atoi(imageWidthTemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 12, 2, "Escape Radius (Default = 2): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 12, 31, escapeRadiusTemp);
            escapeRadius = atoi(escapeRadiusTemp) == 0 ? 2 : atoi(escapeRadiusTemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 13, 2, "Maximum Iterations (Default = 255): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 13, 38, maxIterationsTemp);
            maxIterations = atoi(maxIterationsTemp) == 0 ? 255 : atoi(maxIterationsTemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 14, 2, "Offset 1 (-1<r<1 | Default=Random): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 14, 38, rOffsetTemp);
            srand(time(NULL));
            rOffset = atof(rOffsetTemp) == 0 ? (-1.0 + (double)(rand()) / ((double)(RAND_MAX / (2.0)))) : atof(rOffsetTemp);
            refresh();
            wrefresh(win);

            mvwprintw(win, 15, 2, "Offset 2 (-1<r<1 | Default=Random): ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 15, 38, iOffsetTemp);
            srand(time(NULL));
            iOffset = atof(iOffsetTemp) == 0 ? (-1.0 + (double)(rand()) / ((double)(RAND_MAX / (2.0)))) : atof(iOffsetTemp);

            refresh();
            wrefresh(win);

            mvwprintw(win, 16, 2, "[1] Grayscale");
            mvwprintw(win, 17, 2, "[2] Random (Recommended)");
            mvwprintw(win, 18, 2, "Color Function: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 18, 18, colorSelectionTemp);
            colorSelection = atoi(colorSelectionTemp) == 0 ? 1 : atoi(colorSelectionTemp);
            refresh();
            wrefresh(win);

            if (colorSelection == 2)
            {
                mvwprintw(win, 18, 2, "Seed:             ");
                refresh();
                wrefresh(win);

                mvwgetstr(win, 18, 8, randomSeedTemp);
                randomSeed = atoi(randomSeedTemp) == 0 ? time(NULL) : atoi(randomSeedTemp);
                srand(randomSeed);
                refresh();
                wrefresh(win);
                C1r = rand() % 256;
                C1g = rand() % 256;
                C1b = rand() % 256;

                C2r = rand() % 256;
                C2g = rand() % 256;
                C2b = rand() % 256;

                C3r = rand() % 256;
                C3g = rand() % 256;
                C3b = rand() % 256;

                C4r = rand() % 256;
                C4g = rand() % 256;
                C4b = rand() % 256;

                C5r = rand() % 256;
                C5g = rand() % 256;
                C5b = rand() % 256;
            }

            mvwprintw(win, 19, 2, "Output File Name: ");
            refresh();
            wrefresh(win);

            mvwgetstr(win, 19, 20, outputTemp);

            mvwprintw(win, 20, 2, "Generating... Please be patient.");
            refresh();
            wrefresh(win);

            std::string output = outputTemp;
            output += ".ppm";

            std::ofstream fout(output);
            fout << "P3" << std::endl;
            fout << imageWidth << " " << imageHeight << std::endl;
            fout << "256" << std::endl;

            for (int y = 0; y < imageHeight; y++)
            {
                for (int x = 0; x < imageWidth; x++)
                {
                    double invertedEscapeRadius = escapeRadius * -1.0;
                    double sr = scaleReal(x, imageWidth, invertedEscapeRadius, escapeRadius);
                    double si = scaleImaginary(y, imageHeight, invertedEscapeRadius, escapeRadius);

                    int n = julia(rOffset, iOffset, sr, si, maxIterations, escapeRadius);

                    if (colorSelection == 1)
                    {
                        r = (n % 256);
                        g = (n % 256);
                        b = (n % 256);
                    }
                    else
                    {
                        int pos = (n % 4);
                        if (pos == 0)
                        {
                            r = C1r;
                            g = C1g;
                            b = C1b;
                        }
                        else if (pos == 1)
                        {
                            r = C2r;
                            g = C2g;
                            b = C2b;
                        }
                        else if (pos == 2)
                        {
                            r = C3r;
                            g = C3g;
                            b = C3b;
                        }
                        else if (pos == 3)
                        {
                            r = C4r;
                            g = C4g;
                            b = C4b;
                        }
                        else
                        {
                            r = C5r;
                            g = C5g;
                            b = C5b;
                        }
                    }

                    fout << r << " " << g << " " << b << " ";
                }
                fout << std::endl;
            }
            fout.close();
            mvwprintw(win, 20, 2, "                                ");
            mvwprintw(win, 20, 2, "Done!");
            mvwprintw(win, 21, 2, "Create Another (Y/N): ");
            refresh();
            wrefresh(win);
            int repeatT = mvwgetch(win, 21, 24);
            if (repeatT == 'Y' || repeatT == 'y')
            {
                repeat = 1;
            }
            else
            {
                repeat = 0;
            }
        }
        getch();
        endwin();
    }

    return 0;
}