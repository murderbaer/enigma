#include "helper.h"
#include <stdio.h>

int get_number_from_string(char *str, int *number)
{
    *number     = 0;
    int i       = 0;
    int negtive = 1;

    if (str[0] == '-')
    {
        i++;
        negtive = -1;
    }

    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            *number = *number * 10 + (str[i] - '0');
        }
        else
        {
            printf("Error: %s is not a number\n", str);
            return 1;
        }

        i++;
    }

    if (negtive == -1 && i == 1)
    {
        printf("Error: %s is not a number\n", str);
        return 1;
    }

    *number *= negtive;

    return 0;
}
