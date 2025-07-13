#include "philo.h"

static void forks_init(t_philo *philo, t_fork *forks, int i)
{
    philo->right_fork = &forks[i];
    philo->left_fork = &forks[i+1 % philo->table->philo_nbr];

}

static void philo_init(t_table table)
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
        forks_init(philo, table->forks, i);
    }
}
void data_init(t_table *table)
{
    table->stop_simulation = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
}  