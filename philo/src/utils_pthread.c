/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_pthread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/20 15:42:47 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex(pthread_mutex_t *mutexes, t_uint amount)
{
	t_uint	i;
	int		err;

	i = 0;
	while (i < amount)
	{
		err = pthread_mutex_init(&mutexes[i], NULL);
		if (err)
			return (destroy_mutex(mutexes, i), save_errno(err));
		++i;
	}
	return (SUCCESS);
}

int	destroy_mutex(pthread_mutex_t *mutexes, t_uint amount)
{
	t_uint	i;
	int		err;

	i = 0;
	while (i < amount)
	{
		err = pthread_mutex_destroy(&mutexes[i++]);
		if (err)
			save_errno(err);
	}
	return (save_errno(RETURN_SAVED_ERRNO));
}

int	create_philo_threads(
	t_philosopher *phil, pthread_mutex_t *forks, t_param *param)
{
	t_uint	i;
	int		err;

	i = 0;
	pthread_mutex_lock(&param->mutex[M_DEATH_FLAG]);
	while (i < param->p_amount)
	{
		phil[i].forks = forks;
		init_philosopher_data(&phil[i], param, i);
		err = pthread_create(&phil[i].thread, NULL, philo_routine, &phil[i]);
		if (err)
		{
			param->death_flag = true;
			pthread_mutex_unlock(&param->mutex[M_DEATH_FLAG]);
			return (join_threads(phil, i), save_errno(err));
		}
		usleep(10);
		++i;
	}
	return (SUCCESS);
}

int	join_threads(t_philosopher *philos, t_uint amount)
{
	t_uint	i;
	int		err;

	i = 0;
	while (i < amount)
	{
		err = pthread_join(philos[i++].thread, NULL);
		if (err)
			save_errno(err);
	}
	return (save_errno(RETURN_SAVED_ERRNO));
}
