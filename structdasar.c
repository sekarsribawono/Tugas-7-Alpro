#include <stdio.h>

typedef struct
{
    double time;
    double temperature;
} Measurement;

int main(void)
{
    Measurement data[] =
    {
        {0.0, 25.1},
        {1.0, 25.8},
        {2.0, 26.7},
        {3.0, 27.4}
    };
    int n = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < n; i++)
    {
        printf("t = %.1f s, T = %.2f C\n", data[i].time, data[i].temperature);
    }

    return 0;
}