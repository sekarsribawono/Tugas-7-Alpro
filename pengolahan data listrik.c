#include <stdio.h>

#define MAX_DATA 1000

typedef struct
{
    double time;      /* s */
    double voltage;   /* V */
    double current;   /* A */
} ElectricalMeasurement;

int load_measurements(const char filename[], ElectricalMeasurement data[], int max_data);
double power(const ElectricalMeasurement *m);
double mean_power(const ElectricalMeasurement data[], int n);
int index_max_power(const ElectricalMeasurement data[], int n);
int save_results(const char filename[], const ElectricalMeasurement data[], int n);

int main(void)
{
    ElectricalMeasurement data[MAX_DATA];

    int n = load_measurements("electrical.csv", data, MAX_DATA);
    if (n <= 0)
    {
        printf("No valid data.\n");
        return 1;
    }

    int k = index_max_power(data, n);

    printf("Records       = %d\n", n);
    printf("Mean power    = %.4f W\n", mean_power(data, n));
    printf("Maximum power = %.4f W at t = %.1f s\n", power(&data[k]), data[k].time);

    if (save_results("processed.csv", data, n) != 0)
    {
        return 1;
    }
    printf("Results written to processed.csv\n");

    return 0;
}

int load_measurements(const char filename[], ElectricalMeasurement data[], int max_data)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror(filename);
        return -1;
    }

    char line[256];
    if (fgets(line, sizeof(line), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }

    int n = 0;
    while (n < max_data && fgets(line, sizeof(line), fp) != NULL)
    {
        ElectricalMeasurement m;
        if (sscanf(line, "%lf,%lf,%lf", &m.time, &m.voltage, &m.current) != 3)
        {
            printf("Skipping invalid line: %s", line);
            continue;
        }
        data[n] = m;
        n++;
    }

    fclose(fp);
    return n;
}

double power(const ElectricalMeasurement *m)
{
    return m->voltage * m->current;
}

double mean_power(const ElectricalMeasurement data[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += power(&data[i]);
    }
    return sum / n;
}

int index_max_power(const ElectricalMeasurement data[], int n)
{
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (power(&data[i]) > power(&data[index]))
        {
            index = i;
        }
    }
    return index;
}

int save_results(const char filename[], const ElectricalMeasurement data[], int n)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror(filename);
        return -1;
    }

    fprintf(fp, "time,voltage,current,power\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%.2f,%.3f,%.3f,%.5f\n",
                data[i].time, data[i].voltage, data[i].current, power(&data[i]));
    }

    if (fclose(fp) != 0)
    {
        perror(filename);
        return -1;
    }
    return 0;
}