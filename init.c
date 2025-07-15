#include "philo.h"

static void forks_value_init(t_philo *philo, t_fork *forks, int i)
{
    philo->right_fork = &forks[(i+1) % philo->table->philo_nbr];
    philo->left_fork = &forks[i];
    if(philo->philo_id % 2 == 0)
    {
        philo->right_fork = &forks[i];
        philo->left_fork = &forks[(i+1) % philo->table->philo_nbr];
    }
}

static void philo_value_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1
    while(++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->philo_id = i+1;
        philo->full = false;
        philo->meals_eaten = 0;
        philo->table = table;
        forks_value_init(philo, table->forks, i);
    }
}
void data_init(t_table *table)
{
    table->stop_simulation = false;
    table->start_simulation  = get_time();//idk

    if(pthread_mutex_init(&table->print_mutex, NULL) != 0)
        error_exit("Mutex init error![1]");

    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);

    i = 0;
    while (i < table->philo_nbr)
    {
        table->forks[i].id = i + 1;
        if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
            error_exit("Mutex init error![2]");
        i++;
    }
    philo_value_init(table);

}  
