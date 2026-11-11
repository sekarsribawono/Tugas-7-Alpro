#include <stdio.h>

#define MAX_DATA 1000

typedef struct
{
    double time;
    double voltage;
    double current;
} ElectricalMeasurement;

int main(void)
{
    FILE *fp = fopen("sensor_raw.csv", "r");
    if (fp == NULL)
    {
        perror("sensor_raw.csv");
        return 1;
    }

    ElectricalMeasurement data[MAX_DATA];
    int n = 0;
    int rejected = 0;
    char line[256];

    if (fgets(line, sizeof(line), fp) == NULL)     /* lewati header */
    {
        printf("File is empty.\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        ElectricalMeasurement m;
        int matched = sscanf(line, "%lf,%lf,%lf", &m.time, &m.voltage, &m.current);

        if (matched != 3)
        {
            printf("Skipping invalid line: %s", line);
            rejected++;
            continue;
        }
        if (n >= MAX_DATA)
        {
            printf("Data capacity exceeded.\n");
            break;
        }
        data[n] = m;
        n++;
    }
    fclose(fp);

    printf("Valid records = %d, rejected = %d\n", n, rejected);
    for (int i = 0; i < n; i++)
    {
        printf("%4.1f s  %5.2f V  %5.2f A\n", data[i].time, data[i].voltage, data[i].current);
    }

    return 0;
}