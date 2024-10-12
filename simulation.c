/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:24:08 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/03 19:39:25 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *av)
{
	t_philo	*philo;

	philo = (t_philo *) av;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->running_threads);
	write_status(FIRST_FORK, philo, DEBUG_MODE);
	while (!simul_finish(philo->table))
		usleep(200);
	return (NULL);
}

void	think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

void	eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->second_fork->fork, LOCK);
	write_status(SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_coun == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 0);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->running_threads);
	while (!simul_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_die, philo->table);
		think(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (1 == table->philo_number)
		safe_thread(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
	{
		while (i++ < table->philo_number)
			safe_thread(&table->philos[i].thread_id,
				simulation, &table->philos[i], CREATE);
	}
	safe_thread(&table->monitor, monitor_dinner, table, CREATE);
	table->start_similation = get_time(MILISECOND);
	set_int(&table->table_mutex, &table->threads_ready, 0);
	i = 0;
	while (i++ < table->philo_number)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_int(&table->table_mutex, &table->end_similation, 0);
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}
