#include "philo.h"

void *dinner_simulation(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;

    wait_all_threads(philo->table);

    while(!simulation_finished(philo->table))
    {
        if(philo->full)
            break ;
        
    }
    return NULL;
}


void dinner_start(t_table *table)
{
    if(table->philo_nbr == 0)
        return ;
    else if(table->philo_nbr == 1)
        ;//
    else
    {
        int i;
        i = -1;
        while(++i < table->philo_nbr)
            thread_handle(&table->philos[i].thread_id, "CREATE", dinner_simulation, &table->philos[i]);
    }
    table->start_simulation  = get_current_time(MILISECOND);

    bool_setter(&table->table_mutex, &table->threads_ready, true);
    i = -1;
    while(++i < table->philo_nbr)
        thread_handle(&table->philos[i].thread_id, "JOIN", NULL, NULL);
}