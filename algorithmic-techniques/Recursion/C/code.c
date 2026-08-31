#include <stdio.h>
#include <string.h>

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int sum(int n)
{
    if (n == 0)
    {
        return 0;
    }

    return n + sum(n - 1);
}

int array_sum(const int *array, int size)
{
    if (size == 0)
    {
        return 0;
    }

    return array[size - 1] + array_sum(array, size - 1);
}

int power(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }

    return base * power(base, exponent - 1);
}

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return gcd(b, a % b);
}

void reverse_string_recursive(
    char *string,
    int left,
    int right
)
{
    if (left >= right)
    {
        return;
    }

    char temp = string[left];
    string[left] = string[right];
    string[right] = temp;

    reverse_string_recursive(string, left + 1, right - 1);
}

void reverse_string(char *string)
{
    int length = strlen(string);

    reverse_string_recursive(
        string,
        0,
        length - 1
    );
}

int main(void)
{
    int array[] = {2, 4, 6, 8};
    int size = sizeof(array) / sizeof(array[0]);

    char string[] = "hello";

    printf("Factorial: %d\n", factorial(5));

    printf("Fibonacci: %d\n", fibonacci(5));

    printf("Sum: %d\n", sum(5));

    printf(
        "Array Sum: %d\n",
        array_sum(array, size)
    );

    printf("Power: %d\n", power(2, 5));

    printf("GCD: %d\n", gcd(48, 18));

    reverse_string(string);

    printf("Reversed String: %s\n", string);

    return 0;
}