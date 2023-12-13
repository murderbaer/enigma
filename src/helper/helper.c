int get_number_from_string(char *str) {
    int number = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            number = number * 10 + (str[i] - '0');
        }
        
        i++;
    }

    return number;
}
