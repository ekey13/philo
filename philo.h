/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:23:18 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/03 19:18:04 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/time.h"
#include "limits.h"
#include "errno.h"
#include "stdbool.h"

#define RSC "\033[0m"
#define RED_TEXT    "\033[31m"
#define BLUE_TEXT   "\033[34m"
#define GREEN_TEXT  "\033[32m"
#define YELLOW_TEXT "\033[33m"

#define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;


typedef struct s_philo
{
	int			id;
	long		meals_coun;
	int			is_valid;
	long		last_meal_time;
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_similation;
	long	running_threads;
	bool	end_similation;
	bool	threads_ready;
	pthread_t	monitor;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;

}	t_table;

void	handel_error(char *error);
void	parse_input(t_table *table, char **av);
void	*safe_malloc(size_t bytes);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
					void *data, t_opcode opcode);
int	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	data_init(t_table *table);

bool		simul_finish(t_table *table);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);

void	wait_threads(t_table *table);

long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	write_status(t_philo_status status, t_philo *philo, bool debug);

void	start_dinner(t_table *table);

bool		all_threads(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	*monitor_dinner(void *data);
void	clean(t_table *table);
