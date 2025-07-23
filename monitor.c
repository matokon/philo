/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:53:25 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:53:25 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed_time;
	long	t_to_die;

	if (bool_getter(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed_time = get_current_time("MILLISECOND")
		- long_getter(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (t_to_die < elapsed_time)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				bool_setter(&table->table_mutex,
					&table->stop_simulation, true);
				write_status(table->philos + i, "DIED");
			}
		}
	}
	return (NULL);
}
