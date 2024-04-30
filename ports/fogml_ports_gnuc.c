#if defined(__GNUC__)

#include "fogml_ports.h"

int fogml_random(int min, int max)
{
    return (rand() % (max - min)) + min;
}

void fogml_printf(char const *str)
{
    printf("%s", str);
};

void fogml_printf_float(float number)
{
    printf("%.2f", number);
};

void fogml_printf_int(int number)
{
    printf("%d", number);
};

#endif