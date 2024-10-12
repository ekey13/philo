/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:43:14 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/03 19:23:51 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		handel_error(YELLOW_TEXT "How it can be negative?" RSC);
	if (!is_digit(*str))
		handel_error("The input is not digit");
	nbr = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		handel_error(RED_TEXT "The value is too big, INT_MAX is the limit" RSC);
	return (nbr);
}

static long	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) +(*str++ - 48);
	if (num > INT_MAX)
		handel_error(RED_TEXT "The value is too big, INT_MAX is the limit" RSC);
	return (num);
}


void	parse_input(t_table *table, char **av)
{
	table->philo_number = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (table->time_to_sleep < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_die < 6e4)
		handel_error("Use timestamp more than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atoi(av[5]);
	else
		table->nbr_limit_meals = -1;
}
