/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:06:37 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/01 16:13:55 by ekechedz         ###   ########.fr       */
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

	i = 0;
	while( i++ < table->philo_number)
	{
		philo = table->philos + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	//safe_mutex(&philo->write_mutex , DESTROY);
	//safe_mutex(&philo->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
