#include "philo.h"

void *safe_malloc(size_t bytes)
{
    void *value;
    value = malloc(bytes);
    if(value == NULL)
        error_exit("Memory allocation problem!");
    return value;
}
long	get_current_time(char *code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_exit("gettimeofday() error\n");
    if(ft_strcmp(code, "SECOND") == 0)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if(ft_strcmp(code, "MILLISECOND") == 0)
        return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
    else if(ft_strcmp(code, "MICROSECOND") == 0)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input code!\n");
	
}
int ft_strcmp(const char *s1, const char *s2)
{
    unsigned char c1;
    unsigned char c2;

    while (*s1 != '\0' || *s2 != '\0')
    {
        c1 = (unsigned char)*s1;
        c2 = (unsigned char)*s2;
        if (c1 != c2)
            return (c1 - c2);
        s1++;
        s2++;
    }
    return 0;
}


void ft_usleep(long usec, t_table *table)//st
{
    long start;
    long elapsed;
    long rem;

    start = get_current_time("MICROSECOND");
    while (get_current_time("MICROSECOND") - start < usec)
    {
        if (simulation_finished(table))
            break;
        elapsed = get_current_time("MICROSECOND") - start;
        rem     = usec - elapsed;
        if (rem > 1000)
            usleep(usec / 2);
        else
            while (get_current_time("MICROSECOND") - start < usec)
                ;
    }
}