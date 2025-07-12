#include "philo.c"

void *safe_malloc(size_t bytes)
{
    void *value;
    value = malloc(bytes);
    if(value == NULL)
        error_exit("Memory allocation problem!")
    return value;
}