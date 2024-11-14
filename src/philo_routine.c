/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/14 16:39:14 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_uint	calc_delay(t_philosopher *philo)
{
	const int		id = philo->id;
	const t_uint	p_amount = philo->param->p_amount;
	const t_uint	time_to_die = philo->param->time_to_die;

	return ((1 - id % 2) * p_amount * (time_to_die / 10));
}

void	set_time_of_death(t_philosopher *philo)
{
	const t_ulong	time_to_die = philo->param->time_to_die;

	pthread_mutex_lock(&philo->param->mutex[M_DEATH_TIME]);
	philo->time_of_death = get_time_ms() + time_to_die;
	pthread_mutex_unlock(&philo->param->mutex[M_DEATH_TIME]);
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

static void	dining_finished(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->param->mutex[M_EAT_COUNT]);
	philo->dine_status = JUST_FINISHED;
	pthread_mutex_unlock(&philo->param->mutex[M_EAT_COUNT]);
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
		if (!take_forks(philo))
			return (NULL);
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
	}
	dining_finished(philo);
	return (NULL);
}
