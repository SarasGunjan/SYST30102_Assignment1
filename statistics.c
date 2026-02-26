#include <stdio.h>   // for printf
#include <stdlib.h>  // for atoi
#include <math.h>    // for sqrt because this one was giving an error in the compiler 

// Global variables to store results for it to be later used by threads
double g_average = 0.0;
int g_minimum = 0;
int g_maximum = 0;
double g_std_dev = 0.0;

// Function to calculate average
void compute_average(const int numbers[], int count)
{
    int sum = 0;

    // first adding all numbers
    for (int i = 0; i < count; i++)
    {
        sum += numbers[i];
    }

    // then storing the result in a global variable
    g_average = (double)sum / count;
}

// Function to calculate minimum value
void compute_minimum(const int numbers[], int count)
{
    int min_val = numbers[0];  // initally storing the first number as the minimum

    // Compare with rest of numbers
    for (int i = 1; i < count; i++)
    {
        if (numbers[i] < min_val)
        {
            min_val = numbers[i];
        }
    }

    // Store result globally
    g_minimum = min_val;
}

// Function to calculate maximum value
void compute_maximum(const int numbers[], int count)
{
    int max_val = numbers[0];  // assume first number is maximum

    // Compare with rest of numbers
    for (int i = 1; i < count; i++)
    {
        if (numbers[i] > max_val)
        {
            max_val = numbers[i];
        }
    }

    // Store result globally
    g_maximum = max_val;
}

// Function to calculate standard deviation
void compute_std_dev(const int numbers[], int count)
{
    double variance_sum = 0.0;

    // Use previously calculated average
    for (int i = 0; i < count; i++)
    {
        double diff = numbers[i] - g_average;
        variance_sum += diff * diff;  // square of difference
    }

    double variance = variance_sum / count;

    // Store final result globally
    g_std_dev = sqrt(variance);
}

int main(int argc, char *argv[])
{
    // Check if at least one number was provided
    if (argc < 2)
    {
        printf("Please provide at least one number.\n");
        return 1;
    }

    int count = argc - 1;
    int numbers[count];

    // Convert command line input from string to integer
    for (int i = 0; i < count; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    // Call each computation function
    compute_average(numbers, count);
    compute_minimum(numbers, count);
    compute_maximum(numbers, count);
    compute_std_dev(numbers, count);

    // Print final results
    printf("The average value is %.2f\n", g_average);
    printf("The minimum value is %d\n", g_minimum);
    printf("The maximum value is %d\n", g_maximum);
    printf("The Standard Deviation is %.2f\n", g_std_dev);

    return 0;
}