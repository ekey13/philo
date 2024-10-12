/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:59:26 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/01 15:55:09 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (1);
	elapsed = get_time(MILISECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (0);
	return (1);
}


void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads(&table->table_mutex,
			&table->running_threads, table->philo_number))
		;
	while (!simul_finish(table))
	{
		i = 0;
		while (i++ < table->philo_number && !simul_finish(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_similation, 0);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}

	}
	return (NULL);
}
