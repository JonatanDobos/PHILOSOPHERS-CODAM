/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/11 17:47:19 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_time_of_death(t_philosopher *philo)
{
	const t_ulong	time_to_die = philo->param->time_to_die;

	pthread_mutex_lock(&philo->mutex[M_DEATH_TIME]);
	philo->time_of_death = get_time_ms() + (t_ulong)(time_to_die);
	pthread_mutex_unlock(&philo->mutex[M_DEATH_TIME]);
}

static bool	one_philo_exception(t_philosopher *philo, t_uint start_delay)
{
	if (death_check(philo->param))
		return (true);
	if (philo->param->p_amount == 1)
	{
		print_activity(1, philo->param, FORK);
		usleep(philo->param->time_to_die * 1000);
		return (true);
	}
	usleep(start_delay);
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
	start_delay = calc_delay(philo);
	pthread_mutex_lock(&philo->param->mutex[M_START]);
	pthread_mutex_unlock(&philo->param->mutex[M_START]);
	set_time_of_death(philo);
	if (one_philo_exception(philo, start_delay))
		return (NULL);
	while (!death_check(philo->param))
	{
		thinking(philo);
		take_forks(philo);
		if (death_check(philo->param))
			break ;
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
	}
	set_status_finished(philo);
	return (NULL);
}
