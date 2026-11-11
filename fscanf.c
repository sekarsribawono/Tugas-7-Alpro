#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("temperature.txt", "r");
    if (fp == NULL)
    {
        perror("temperature.txt");
        return 1;
    }

    double time, temperature;
    double sum = 0.0;
    int n = 0;

    while (fscanf(fp, "%lf %lf", &time, &temperature) == 2)
    {
        sum += temperature;
        n++;
    }
    fclose(fp);

    if (n > 0)
    {
        printf("Records read     = %d\n", n);
        printf("Mean temperature = %.3f C\n", sum / n);
    }

    return 0;
}