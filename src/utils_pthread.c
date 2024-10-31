/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_pthread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/31 14:35:57 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex(pthread_mutex_t *mutexes, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&mutexes[i++], NULL))
			return (destroy_mutex(mutexes, i - 1), save_errno(errno));
	}
	return (EXIT_SUCCESS);
}

int	destroy_mutex(pthread_mutex_t *mutexes, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_destroy(&mutexes[i++]))
			save_errno(errno);
	}
	return (save_errno(RETURN_SAVED_ERRNO));
}

int	create_philo_threads(
	t_philosopher *philos, pthread_mutex_t *forks, t_param *param)
{
	t_uint	i;

	i = 0;
	while (i < param->p_amount)
	{
		philos[i].forks = forks;
		init_philosopher_data(&philos[i], param, i);
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (join_threads(philos, i), save_errno(errno));
		++i;
	}
	return (EXIT_SUCCESS);
}

int	join_threads(t_philosopher *philos, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_join(philos[i++].thread, NULL) != 0)
			save_errno(errno);
	}
	return (save_errno(RETURN_SAVED_ERRNO));
}
