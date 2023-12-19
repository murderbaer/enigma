#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"

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

int to_upper_case(char *input, char *output)
{
    int i = 0;

    while (input[i] != '\0')
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            output[i] = input[i] - 32;
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')
        {
            output[i] = input[i];
        }
        else
        {
            printf("Error: %s is not a letter\n", input);
            return 1;
        }

        i++;
    }

    output[i] = '\0';

    return 0;
}

int remove_none_alnum(char *input, char *output)
{
    int i = 0;
    int j = 0;

    while (input[i] != '\0')
    {
        if ((input[i] >= 'a' && input[i] <= 'z') ||
            (input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= '0' && input[i] <= '9'))
        {
            output[j] = input[i];
            j++;
        }

        i++;
    }

    output[j] = '\0';

    return 0;
}
