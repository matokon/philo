#include "philo.h"

static void thinking(t_philo *philo)
{
    write_status(philo, "THINKING", DEBUG_MODE);
}
static void eat(t_philo *philo)
{
    mutex_handle(&philo->left_fork->mutex, "LOCK");
    mutex_handle(&philo->right_fork->mutex, "LOCK");

    write_status(philo, "TAKE_FIRST_FORK", DEBUG_MODE);
    write_status(philo, "TAKE_SECOND_FORK", DEBUG_MODE);

    long_setter(&philo->philo_mutex, &philo->last_meal_time, get_current_time("MILLISECOND"));
    philo->meals_eaten++;
    write_status(philo, "EATING", DEBUG_MODE);
    ft_usleep(philo->table->time_to_eat, philo->table);

    if(philo->table->meals_limit_count > 0 && philo->meals_eaten == philo->table->meals_limit_count)
        bool_setter(&philo->philo_mutex, &philo->full, true);

    mutex_handle(&philo->left_fork->mutex, "UNLOCK");
    mutex_handle(&philo->right_fork->mutex, "UNLOCK");
}

void *dinner_simulation(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;

    wait_all_threads(philo->table);

    while(!simulation_finished(philo->table))
    {
        if(philo->full)//TODO safe
            break ;

        eat(philo);

        write_status(philo, "SLEEPING", DEBUG_MODE);

        ft_usleep(philo->table->time_to_sleep, philo->table);

        thinking(philo);//TODO
    }
    return NULL;
}


void dinner_start(t_table *table)
{
    if(table->philo_nbr == 0)
        return ;
    else if(table->philo_nbr == 1)
        ;//TODO
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