#include "philo.h"

static void write_status_of_debug(t_philo *philo, char *status, long elapsed)
{
    if ((ft_strcmp("TAKE_FIRST_FORK", status) == 0) && !simulation_finished(philo->table))
        printf("%-6ld %d has taken the 1st fork %d\n", elapsed, philo->id, philo->first_fork_id);
    else if ((ft_strcmp("TAKE_SECOND_FORK", status) == 0) && !simulation_finished(philo->table))
        printf("%-6ld %d has taken the 2nd fork %d\n", elapsed, philo->id, philo->second_fork->fork_id);
    else if ((ft_strcmp("EATING", status) == 0) && !simulation_finished(philo->table))
        printf("%-6ld %d is eating\n", elapsed, philo->id);
    else if ((ft_strcmp("SLEEPING", status) == 0) && !simulation_finished(philo->table))
        printf("%-6ld %d is sleeping\n", elapsed, philo->id);
    else if ((ft_strcmp("THINKING", status) == 0) && !simulation_finished(philo->table))
        printf("%-6ld %d is thinking\n", elapsed, philo->id);
    else if (ft_strcmp("DIED", status) == 0)
        printf("%-6ld %d died\n", elapsed, philo->id);
}

void write_status(t_philo *philo, char *status, bool debug)
{
    long elapsed;
    elapsed = get_current_time(MILISECOND) - philo->table->start_simulation;
    if (philo->full)
        return;
    mutex_handle(&philo->table->write_mutex, "LOCK");

    if (debug)
    {
        write_status_of_debug(status, philo, elapsed);
    }
    else
    {
        if ((ft_strcmp("TAKE_FIRST_FORK", status) == 0 ||
             ft_strcmp("TAKE_SECOND_FORK", status) == 0) &&
            !simulation_finished(philo->table))
        {
            printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
        }
        else if (ft_strcmp("EATING", status) == 0 &&
                 !simulation_finished(philo->table))
        {
            printf("%-6ld %d is eating\n", elapsed, philo->id);
        }
        else if (ft_strcmp("SLEEPING", status) == 0 &&
                 !simulation_finished(philo->table))
        {
            printf("%-6ld %d is sleeping\n", elapsed, philo->id);
        }
        else if (ft_strcmp("THINKING", status) == 0 &&
                 !simulation_finished(philo->table))
        {
            printf("%-6ld %d is thinking\n", elapsed, philo->id);
        }
        else if (ft_strcmp("DIED", status) == 0)
        {
            printf("%-6ld %d died\n", elapsed, philo->id);
        }
    }
    mutex_handle(&philo->table->write_mutex, "UNLOCK");
}
