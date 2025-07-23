#include "philo.h"

void thinking(t_philo *philo, bool before_dinner)
{
    long t_to_eat;
    long t_to_sleep;
    long t_to_think;
    if(!before_dinner)
        write_status(philo, "THINKING");

    if(philo->table->philo_nbr % 2 == 0)
        return ;

    t_to_eat = philo->table->time_to_eat;
    t_to_sleep = philo->table->time_to_sleep;
    t_to_think = t_to_eat * 2 - t_to_sleep;
    if(t_to_think < 0)
        t_to_think = 0;
    ft_usleep(t_to_think * 0.5, philo->table);
}   

void *single_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_all_threads(philo->table);
    long_setter(&philo->philo_mutex, &philo->last_meal_time, get_current_time("MILLISECOND"));
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
    write_status(philo, "TAKE_FIRST_FORK");
    while(!simulation_finished(philo->table))
        usleep(200);
    return NULL;
}

static void eat(t_philo *philo)
{
    mutex_handle(&philo->left_fork->mutex, "LOCK");
    mutex_handle(&philo->right_fork->mutex, "LOCK");

    write_status(philo, "TAKE_FIRST_FORK");
    write_status(philo, "TAKE_SECOND_FORK");

    long_setter(&philo->philo_mutex, &philo->last_meal_time, get_current_time("MILLISECOND"));
    philo->meals_eaten++;
    write_status(philo, "EATING");
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
    long_setter(&philo->philo_mutex, &philo->last_meal_time, get_current_time("MILLISECOND"));
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);

    desynchronize_philos(philo);

    while(!simulation_finished(philo->table))
    {
        if(philo->full)
            break ;

        eat(philo);

        write_status(philo, "SLEEPING");

        ft_usleep(philo->table->time_to_sleep, philo->table);

        thinking(philo, false);
    }
    return NULL;
}

void dinner_start(t_table *table)
{   
    int i;
    if(table->philo_nbr == 0)
        return ;
    else if(table->philo_nbr == 1)
        thread_handle(&table->philos[0].thread, "CREATE", single_philo, &table->philos[0]);
    else
    {
        i = -1;
        while(++i < table->philo_nbr)
            thread_handle(&table->philos[i].thread, "CREATE", dinner_simulation, &table->philos[i]);
    }
    thread_handle(&table->death_monitor, "CREATE", monitor_dinner, table);
    table->start_simulation = get_current_time("MILLISECOND");
    bool_setter(&table->table_mutex, &table->threads_ready, true);
    i = -1;
    while(++i < table->philo_nbr)
        thread_handle(&table->philos[i].thread, "JOIN", NULL, NULL);

    bool_setter(&table->table_mutex, &table->stop_simulation, true);
    thread_handle(&table->death_monitor, "JOIN", NULL, NULL);
}
