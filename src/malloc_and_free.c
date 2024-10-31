/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_and_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 15:31:50 by joni          #+#    #+#                 */
/*   Updated: 2024/10/31 16:33:32 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	malloc_structs(t_main *m)
{
	const int	num = m->param.p_amount;

	m->philo = (t_philosopher *)malloc(sizeof(t_philosopher) * num);
	if (!m->philo)
		return (save_errno(errno), cleanup(m), EXIT_FAILURE);
	m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!m->forks)
		return (save_errno(errno), cleanup(m), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	cleanup(t_main *m)
{
	destroy_mutex(m->param.mutex, 5);
	if (m->forks)
		free(m->forks);
	if (m->philo)
		free(m->philo);
}
