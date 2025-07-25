/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:52:50 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:52:50 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_value_init(t_philo *philo, t_fork *forks, int i)
{
	philo->right_fork = &forks[(i + 1) % philo->table->philo_nbr];
	philo->left_fork = &forks[i];
	if (philo->philo_id % 2 == 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork = &forks[(i + 1) % philo->table->philo_nbr];
	}
}

static void	philo_value_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->full = false;
		philo->meals_eaten = 0;
		philo->table = table;
		mutex_handle(&philo->philo_mutex, "INIT");
		forks_value_init(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	table->stop_simulation = false;
	table->threads_ready = false;
	table->threads_running_nbr = 0;
	mutex_handle(&table->print_mutex, "INIT");
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	mutex_handle(&table->table_mutex, "INIT");
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	mutex_handle(&table->write_mutex, "INIT");
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->forks[i].id = i;
		mutex_handle(&table->forks[i].mutex, "INIT");
	}
	philo_value_init(table);
}
