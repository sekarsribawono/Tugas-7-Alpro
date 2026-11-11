#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("temperature.txt", "w");
    if (fp == NULL)
    {
        perror("temperature.txt");
        return 1;
    }

    for (int i = 0; i <= 5; i++)
    {
        double time = i * 1.0;
        double temperature = 25.0 + 0.8 * time;
        fprintf(fp, "%.2f %.2f\n", time, temperature);
    }

    fclose(fp);
    printf("Data written to temperature.txt\n");

    return 0;
}