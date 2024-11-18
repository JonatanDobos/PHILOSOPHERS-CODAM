/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_and_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 15:31:50 by joni          #+#    #+#                 */
/*   Updated: 2024/11/18 15:16:01 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	malloc_structs(t_main *m)
{
	const int	num = m->param.p_amount;

	m->philo = (t_philosopher *)malloc(sizeof(t_philosopher) * num);
	if (!m->philo)
		return (save_errno(errno), cleanup(m), FAILURE);
	m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!m->forks)
		return (save_errno(errno), cleanup(m), FAILURE);
	if (init_philo_mutex(m->philo, m->param.p_amount))
		return (cleanup(m), save_errno(RETURN_SAVED_ERRNO));
	return (save_errno(RETURN_SAVED_ERRNO));
}

void	cleanup(t_main *m)
{
	if (m->forks)
		free(m->forks);
	if (m->philo)
		free(m->philo);
	destroy_mutex(m->param.mutex, 2);
}

int	init_philo_mutex(t_philosopher *philo, t_uint amount)
{
	t_uint	i;
	int		err;

	i = 0;
	while (i < amount)
	{
		err = init_mutex(&(philo[i]).mutex, 1);
		if (err)
			return (destr_philo_mutex(philo, i), save_errno(err));
		++i;
	}
	return (SUCCESS);
}

int	destr_philo_mutex(t_philosopher *philo, t_uint amount)
{
	t_uint	i;
	int		err;

	i = 0;
	while (i < amount)
	{
		err = destroy_mutex(&(philo[i]).mutex, 1);
		if (err)
			save_errno(err);
		++i;
	}
	return (save_errno(RETURN_SAVED_ERRNO));
}
