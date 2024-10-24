/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:26:40 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/24 10:06:16 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->table->start_similation;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if ((FIRST_FORK == status || SECOND_FORK == status)
		&& !simul_finish(philo->table))
		printf("%-6ld"RSC"Philosopher %d has taken a fork\n",
			elapsed, philo->id);
	else if (EATING == status && !simul_finish(philo->table))
		printf("%-6ld"RSC"Philosopher %d is eating\n"RSC, elapsed, philo->id);
	else if (SLEEPING == status && !simul_finish(philo->table))
		printf("%-6ld " RSC "Philosopher %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simul_finish(philo->table))
		printf("%-6ld"RSC"Philosopher %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED_TEXT "%-6ld Philosopher %d died\n" RSC, elapsed, philo->id);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
