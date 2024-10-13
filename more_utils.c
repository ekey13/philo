/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:06:37 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/13 10:53:29 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while(++i < table->philo_number)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&table->write_mutex , DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void syn_philo(t_philo *philo)
{
	if (philo->table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo-> id % 2)
			think(philo, true);
	}
}
