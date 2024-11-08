/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:09 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/08 12:27:24 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	death(t_param *param, t_uint id)
{
	pthread_mutex_lock(&param->mutex[M_DEATH_FLAG]);
	param->death_flag = true;
	pthread_mutex_unlock(&param->mutex[M_DEATH_FLAG]);
	print_activity(id, param, DIED);
}

static bool	finish_and_death_checks(t_philosopher *philo, t_uint *finished)
{
	short	status;
	t_ulong	time_of_death;

	pthread_mutex_lock(&philo->param->mutex[M_EAT_COUNT]);
	status = philo->dine_status;
	fprintf(stderr, "EAT_COUNT\n");
	pthread_mutex_unlock(&philo->param->mutex[M_EAT_COUNT]);
	pthread_mutex_lock(&philo->param->mutex[M_DEATH_TIME]);
	time_of_death = philo->time_of_death;
	fprintf(stderr, "DEATH_TIME\n");
	pthread_mutex_unlock(&philo->param->mutex[M_DEATH_TIME]);
	if (status == DINING && get_time_ms() > time_of_death)
		return (death(philo->param, philo->id), EXIT_FAILURE);
	else if (status == JUST_FINISHED)
	{
		++(*finished);
		philo->dine_status = FINISHED;
	}
	return (EXIT_SUCCESS);
}

void	monitor(t_main *m)
{
	t_uint	i;
	t_uint	finished;

	finished = 0;
	pthread_mutex_unlock(&m->param.mutex[M_START]);
	m->param.start_time = get_time_ms();
	while (finished < m->param.p_amount)
	{
		i = 0;
		while (i < m->param.p_amount)
		{
			if (finish_and_death_checks(&m->philo[i], &finished))
				return ;
			++i;
		}
	}
}
