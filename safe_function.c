/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:34:38 by ekechedz          #+#    #+#             */
/*   Updated: 2024/10/24 09:59:31 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		handel_error("Erro with the malloc");
	return (ret);
}

int	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	int	status;

	status = 0;
	if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	if (status != 0)
	{
		handel_error("Mutex operation failed");
	}
	return (status);
}

static void	handel_thread(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		handel_error(RED_TEXT "The value is invalid" RSC);
	else if (EINVAL == status && INIT == opcode)
		handel_error(RED_TEXT "The value is invalid" RSC);
	else if (EDEADLK == status)
		handel_error(RED_TEXT"A deadlock would occur"RSC);
	else if (EPERM == status)
		handel_error(RED_TEXT"The tread does not hold a lock on mutex"RSC);
	else if (ENOMEM == status)
		handel_error(RED_TEXT "Not enoyg memory to create another mutex");
	else if (EBUSY == status)
		handel_error(RED_TEXT"Mutex is locked" RSC);
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
					void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handel_thread(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handel_thread(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handel_thread(pthread_detach(*thread), opcode);
	else
		handel_error(RED_TEXT"Wrong opcode fot thread_handel" RSC);
}
