/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:49:23 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/01 13:40:45 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(t_mtx *mutex, int *dest, int value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

int	get_int(t_mtx *mutex, int *value)
{
	int	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

int	simul_finish(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end_similation));
}