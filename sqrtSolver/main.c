#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double shift = 1.0;
#define offset (x / (20 + (x / shift)))

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

    const int lower = 1;
    const int upper = 500;

    const int shiftStart = 1;
    const int shiftEnd = 100;

    shift = optimize(lower, upper, 1, shiftStart, shiftEnd);
    printf("\noptimize 1: %lf\n", shift);

    shift = optimize(lower, upper, 0.1, shift - 10, shift + 10);
    printf("optimize 2: %lf\n", shift);

    shift = optimize(lower, upper, 0.01, shift - 5, shift + 5);
    printf("optimize 3: %lf\n", shift);

    shift = optimize(lower, upper, 0.001, shift - 1, shift + 1);
    printf("optimize 4: %lf\n", shift);

    // from [1-1000] shift [1-100] best has been found as 43.993000

    printf("calculated sqrt(25) as [%lf]\n", calculate(25));
    return 0;
}