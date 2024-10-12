/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_pthread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/12 23:09:33 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	init_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&mutexes[i++], NULL))
			return (save_errno(errno), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	destroy_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_destroy(&mutexes[i++]))
			return (save_errno(errno), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	create_philo_threads(
	t_philosopher *philo, pthread_mutex_t *forks, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->p_amount)
	{
		philo[i].forks = forks;
		init_philosopher_data(&philo[i], param, i);
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
			return (EXIT_FAILURE);
		usleep(42);
		++i;
	}
	return (EXIT_SUCCESS);
}

bool	join_threads(t_philosopher *philos, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_join(philos[i++].thread, NULL) != 0)
			return (save_errno(errno), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
