/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:13:17 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/03 19:36:33 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_number;
	philo->first_fork = &forks[position];
	philo->second_fork = &forks[(position + 1) % philo_nbr];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}


static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_coun = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_similation = false;
	table->threads_ready = 1;
	table->running_threads = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
		handel_error("Memory allocation failed for philosophers.");
	// safe_mutex(&table->table_mutex, INIT);
	// safe_mutex(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_number);
	if (!table->forks)
		handel_error("Memory allocation failed for forks.");
	while (++i < table->philo_number)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
