/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_pthread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/30 16:08:50 by jdobos        ########   odam.nl         */
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
			return (save_errno(errno));
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
			return (save_errno(errno));
	}
	return (EXIT_SUCCESS);
}

int	create_philo_threads(
	t_philosopher *philo, pthread_mutex_t *forks, t_param *param)
{
	t_uint	i;

	i = 0;
	while (i < param->p_amount)
	{
		philo[i].forks = forks;
		init_philosopher_data(&philo[i], param, i);
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
			return (save_errno(errno));
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
			return (save_errno(errno));
	}
	return (EXIT_SUCCESS);
}
