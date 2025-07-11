#include "philo.h"

void input_parsing(t_table *table, char **argv)
{
    table->philo_nbr = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]) * 1e3;
    table->time_to_eat = ft_atol(argv[3]) * 1e3;
    table->time_to_sleep = ft_atol(argv[4]) * 1e3;
    if(table->time_to_die < 6e4 ||
    time_to_eat < 6e4 || time_to_sleep < 6e4)
        error_exit("Timestamps are wrong!(60ms is bare minimum)");
    if(argv[5])
    {
        table->meals_limit_count = ft_atol(argv[5]);
    }
    else
    {
        table->meals_limit_count = -1;
    }
}
