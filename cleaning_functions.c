/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:51:47 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:51:47 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, "DESTROY");
	}
	mutex_handle(&table->write_mutex, "DESTROY");
	mutex_handle(&table->table_mutex, "DESTROY");
	free(table->forks);
	free(table->philos);
}
