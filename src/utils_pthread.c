/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_pthread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/08 13:41:38 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	save_the_threads(t_param *param)
{
	pthread_mutex_lock(&param->mutex[M_DEATH_FLAG]);
	param->death_flag = true;
	pthread_mutex_unlock(&param->mutex[M_DEATH_FLAG]);
	pthread_mutex_unlock(&param->mutex[M_START]);
}

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
	return (EXIT_SUCCESS);
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
	while (i < param->p_amount)
	{
		phil[i].forks = forks;
		init_philosopher_data(&phil[i], param, i);
		err = pthread_create(&phil[i].thread, NULL, philo_routine, &phil[i]);
		if (err)
		{
			save_the_threads(param);
			return (join_threads(phil, i), save_errno(err));
		}
		++i;
	}
	return (EXIT_SUCCESS);
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
