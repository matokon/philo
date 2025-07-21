#include "philo.h"

void wait_all_threads(t_table *table)
{
    while(!bool_getter(&table->table_mutex, &table->threads_ready))
        ;
}

bool all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool return_val;
    return_val = false;

    mutex_handle(mutex, "LOCK");
    if(*threads == philo_nbr)
        return_val = true;
    mutex_handle(mutex, "UNLOCK");
    return return_val;
}

void increase_long(pthread_mutex_t *mutex, long *value)
{
    mutex_handle(mutex, "LOCK");
    (*value)++;
    mutex_handle(mutex, "UNLOCK");
}