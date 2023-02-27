#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double shift = 1.0;
#define offset (x / (shift + (x / 44.993)))

double H(double to)
{
    double sum = 0;
    do
    {
        sum += 1 / to;
    } while (--to);
    return sum;
}

double calculate(double x)
{
    return (x + pow(H(x) + offset, 2)) / (2 * (H(x) + offset));
}

double minmap(double *k, double *v, int len)
{
    double min = *v;
    int mindex = 0;

    for (int i = 1; i < len; i++)
    {
        if (*v < min)
        {
            min = *v;
            mindex = i;
        }
        v++;
    }
    return k[mindex];
}

/// @param lowerBound Lowest number to be optimized for
/// @param upperBound Highest number to be optimized for
/// @param change step between each shift
/// @param startShift Number to start the shift at
/// @param endShift Number to end the shift at
double optimize(int lowerBound, int upperBound, double change, double startShift, double endShift)
{
    shift = startShift;

    int size = ceil((endShift - shift) / change);

    double errors[size];
    double shiftOff[size];

    double *ep = errors;
    double *sp = shiftOff;

    FILE *fp = fopen("sqrtSolver/data.txt", "w");
    if(fp == NULL) {
        printf("Data can't be opened, check path\n");
        exit(1);
    }

    for (; shift < endShift; shift += change)
    {
        double err = 0;
        for (int number = lowerBound; number < upperBound; number++)
        {
            err += fabs(sqrt(number) - calculate((double)number));
        }

        *(ep++) = err;
        *(sp++) = shift;

        fprintf(fp, "%lf : %lf\n", shift, err);
    }

    fclose(fp);
    return minmap(shiftOff, errors, size);
}

int main()
{

    
    shift = optimize(1, 1000, 0.1, 1, 40);
    printf("\nmost optimized: %lf\n", shift);
    // best has been found as 43.993000

    printf("calculated sqrt(100) as [%lf]\n", calculate(100));
    return 0;
}