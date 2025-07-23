#include "philo.h"

static inline bool is_space(char c)
{
    return ((c >=9 && c <= 13) || c == 32);
}

static inline bool is_digit(char c) 
{
    return (c >= '0' && c <= '9');
}


const char *input_checker(const char *str)
{
    int len;
    const char *nbr;
    len = 0;
    while(is_space(*str))
        str++;
    if(*str == '+')
        str++;
    else if(*str == '-')
        error_exit("Number cannot be negative!");
    if(!is_digit(*str))
        error_exit("Wrong number!");
    nbr = str;
    while(is_digit(*str++))
        ++len;
    if(len > 10)
        error_exit("Value exceeds INT_MAX!");
    return nbr;
}

long ft_atol(const char *str)
{
    long nbr;
    nbr = 0;
    str = input_checker(str);
    while(is_digit(*str))
        nbr = (nbr * 10) + (*str++ - 48);
    if(nbr > INT_MAX)
        error_exit("Value is too big!");

    return nbr;
}
