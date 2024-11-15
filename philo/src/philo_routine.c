/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/15 16:00:03 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_time_of_death(t_philosopher *philo)
{
	const t_ulong	time_to_die = philo->param->time_to_die;

	pthread_mutex_lock(&philo->mutex[M_DEATH_TIME]);
	philo->time_of_death = get_time_ms() + time_to_die;
	pthread_mutex_unlock(&philo->mutex[M_DEATH_TIME]);
}

static bool	one_philo_exception(t_philosopher *philo)
{
	if (death_check(philo->param))
		return (true);
	if (philo->param->p_amount == 1)
	{
		print_activity(1, philo->param, FORK);
		usleep(philo->param->time_to_die * 1000);
		return (true);
	}
	return (false);
}

static void	set_status_finished(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->mutex[M_DINE_STAT]);
	philo->dine_status = JUST_FINISHED;
	pthread_mutex_unlock(&philo->mutex[M_DINE_STAT]);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_uint			start_delay;

	philo = (t_philosopher *)arg;
	start_delay = philo->param->delay_time_us * (1 - philo->id % 2);
	pthread_mutex_lock(&philo->param->mutex[M_START]);
	pthread_mutex_unlock(&philo->param->mutex[M_START]);
	set_time_of_death(philo);
	if (one_philo_exception(philo))
		return (NULL);
	usleep(start_delay);
	while (!death_check(philo->param))
	{
		thinking(philo);
		if (!take_forks(philo))
			return (NULL);
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
	}
	set_status_finished(philo);
	return (NULL);
}
