/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:52:33 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:52:33 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bool_setter(pthread_mutex_t *mtx, bool *dest, bool value)
{
	mutex_handle(mtx, "LOCK");
	*dest = value;
	mutex_handle(mtx, "UNLOCK");
}

bool	bool_getter(pthread_mutex_t *mtx, bool *value)
{
	bool	ret;

	mutex_handle(mtx, "LOCK");
	ret = *value;
	mutex_handle(mtx, "UNLOCK");
	return (ret);
}

void	long_setter(pthread_mutex_t *mtx, long *dest, long value)
{
	mutex_handle(mtx, "LOCK");
	*dest = value;
	mutex_handle(mtx, "UNLOCK");
}

long	long_getter(pthread_mutex_t *mtx, long *value)
{
	long	ret;

	mutex_handle(mtx, "LOCK");
	ret = *value;
	mutex_handle(mtx, "UNLOCK");
	return (ret);
}

bool	simulation_finished(t_table *table)
{
	return (bool_getter(&table->table_mutex, &table->stop_simulation));
}
