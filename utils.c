/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:54:39 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:54:39 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*value;

	value = malloc(bytes);
	if (value == NULL)
		error_exit("Memory allocation problem!");
	return (value);
}

long	get_current_time(char *code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		error_exit("gettimeofday() error");
	if (ft_strcmp(code, "SECOND") == 0)
		return (tv.tv_sec);
	else if (ft_strcmp(code, "MILLISECOND") == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (ft_strcmp(code, "MICROSECOND") == 0)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	error_exit("Wrong input code!");
	return (-1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 != '\0' || *s2 != '\0')
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (0);
}

void	ft_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_current_time("MICROSECOND");
	while (get_current_time("MICROSECOND") - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_current_time("MICROSECOND") - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while (get_current_time("MICROSECOND") - start < usec)
				;
	}
}

void	desynchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			ft_usleep(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2 == 1)
			thinking(philo, true);
	}
}
