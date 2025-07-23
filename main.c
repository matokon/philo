/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokon <mokon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:53:01 by mokon             #+#    #+#             */
/*   Updated: 2025/07/23 11:53:01 by mokon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		input_parsing(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit("Wrong input!\n");
	return (0);
}
