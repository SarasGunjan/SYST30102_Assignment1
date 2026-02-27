#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

double g_average = 0.0;
int g_minimum = 0;
int g_maximum = 0;
double g_std_dev = 0.0;

typedef struct
{
    const int *numbers;
    int count;
} StatsArgs;

void *thread_average(void *arg)
{
    StatsArgs *args = (StatsArgs *)arg;
    int sum = 0;

    for (int i = 0; i < args->count; i++)
    {
        sum += args->numbers[i];
    }

    g_average = (double)sum / args->count;
    return NULL;
}

void *thread_minimum(void *arg)
{
    StatsArgs *args = (StatsArgs *)arg;
    int min_val = args->numbers[0];

    for (int i = 1; i < args->count; i++)
    {
        if (args->numbers[i] < min_val)
        {
            min_val = args->numbers[i];
        }
    }

    g_minimum = min_val;
    return NULL;
}

void *thread_maximum(void *arg)
{
    StatsArgs *args = (StatsArgs *)arg;
    int max_val = args->numbers[0];

    for (int i = 1; i < args->count; i++)
    {
        if (args->numbers[i] > max_val)
        {
            max_val = args->numbers[i];
        }
    }

    g_maximum = max_val;
    return NULL;
}

void *thread_std_dev(void *arg)
{
    StatsArgs *args = (StatsArgs *)arg;
    double variance_sum = 0.0;

    for (int i = 0; i < args->count; i++)
    {
        double diff = args->numbers[i] - g_average;
        variance_sum += diff * diff;
    }

    double variance = variance_sum / args->count;
    g_std_dev = sqrt(variance);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide at least one number.\n");
        return 1;
    }

    int count = argc - 1;
    int numbers[count];

    for (int i = 0; i < count; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    StatsArgs args;
    args.numbers = numbers;
    args.count = count;

    pthread_t t_avg, t_min, t_max, t_std;

    pthread_create(&t_avg, NULL, thread_average, &args);
    pthread_create(&t_min, NULL, thread_minimum, &args);
    pthread_create(&t_max, NULL, thread_maximum, &args);

    pthread_join(t_avg, NULL);
    pthread_create(&t_std, NULL, thread_std_dev, &args);

    pthread_join(t_min, NULL);
    pthread_join(t_max, NULL);
    pthread_join(t_std, NULL);

    printf("The average value is %.2f\n", g_average);
    printf("The minimum value is %d\n", g_minimum);
    printf("The maximum value is %d\n", g_maximum);
    printf("The Standard Deviation is %.2f\n", g_std_dev);

    return 0;
}