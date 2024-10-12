/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:42:24 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/03 19:20:12 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		start_dinner(&table);
		clean(&table);
	}
	else
	{
		handel_error("Wrong input!\n" GREEN_TEXT "Corect is: "
			GREEN_TEXT "./philo 800 500 400 200 "RSC);
	}
}
