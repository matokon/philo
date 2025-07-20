#include "philo.h"

void wait_all_threads(t_table *table)
{
    while(!bool_getter(&table->table_mutex, &table->threads_ready))
        ;
}