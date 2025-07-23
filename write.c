/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/07/23 11:54:47 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:54:47 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(long elapsed, int id, char *msg)
{
	printf("%-6ld %d %s\n", elapsed, id, msg);
}

void	write_status(t_philo *philo, char *status)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_current_time("MILLISECOND")
		- philo->table->start_simulation;
	mutex_handle(&philo->table->write_mutex, "LOCK");
	if (!simulation_finished(philo->table))
	{
		if (!ft_strcmp(status, "TAKE_FIRST_FORK")
			|| !ft_strcmp(status, "TAKE_SECOND_FORK"))
			print_status(elapsed, philo->philo_id, "has taken a fork");
		else if (!ft_strcmp(status, "EATING"))
			print_status(elapsed, philo->philo_id, "is eating");
		else if (!ft_strcmp(status, "SLEEPING"))
			print_status(elapsed, philo->philo_id, "is sleeping");
		else if (!ft_strcmp(status, "THINKING"))
			print_status(elapsed, philo->philo_id, "is thinking");
	}
	else if (!ft_strcmp(status, "DIED"))
		print_status(elapsed, philo->philo_id, "died");
	mutex_handle(&philo->table->write_mutex, "UNLOCK");
}
