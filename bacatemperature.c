#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("temperature.txt", "w");
    if (fp == NULL)
    {
        perror("temperature.txt");
        return 1;
    }

    for (int i = 0; i <= 6; i++)
    {
        double time, temperature;
        fscanf(fp, "%lf %lf", &time, &temperature);
        printf("t = %.lf s, T = %.2f C\n", time, temperature);
    }
       
    fclose(fp);
    printf("Data written to temperature.txt\n");

    return 0;
}