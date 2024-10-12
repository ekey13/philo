/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:26:40 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/01 13:43:30 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (FIRST_FORK == status && !simul_finish(philo->table))
	{
		printf("%ld "RSC"%d has taken the 1st fork"
			"\t\t[B] [%d] \n" RSC,
			elapsed, philo->id, philo->first_fork->fork_id);
	}
	else if (SECOND_FORK == status && !simul_finish(philo->table))
	{
		printf("%ld "RSC"%d has taken the 2nd fork"
			"\t\t[B] [%d] \n" RSC,
			elapsed, philo->id, philo->second_fork->fork_id);
	}
	else if (EATING == status && !simul_finish(philo->table))
	{
		printf("%ld" " %d is eating"
			"\t\t[Y] [%ld meals]\n" RSC,
			elapsed, philo->id, philo->meals_coun);
	}
	else if (SLEEPING == status && !simul_finish(philo->table))
		printf("%ld"RSC" %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simul_finish(philo->table))
		printf("%ld"RSC" %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED_TEXT "\t\t%ld %d died\n" RSC, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, int debug)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->table->start_similation;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		write_status_debug(status, philo, elapsed);
		if ((FIRST_FORK == status || SECOND_FORK == status)
			&& !simul_finish(philo->table))
			printf("%-6ld "RSC" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simul_finish(philo->table))
			printf("%-6ld "RSC" %d is eating\n" RSC, elapsed, philo->id);
		else if (SLEEPING == status && !simul_finish(philo->table))
			printf("%-6ld "RSC" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simul_finish(philo->table))
			printf("%-6ld "RSC" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED_TEXT"%-6ld %d died\n"RSC, elapsed, philo->id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
