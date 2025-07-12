#include "philo.h"

void data_init(t_table *table)
{
    table->stop_simulation = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
}