/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/08 23:14:58 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_uint	calc_delay(t_philosopher *philo)
{
	const int		id = philo->id;
	const t_uint	p_amount = philo->param->p_amount;
	t_uint			multiplier;

	multiplier = (philo->param->time_to_eat + philo->param->time_to_sleep \
		+ philo->param->time_to_die) / 25;
	return ((1 - id % 2) * p_amount * multiplier);
}

static void	set_time_of_death(t_philosopher *philo)
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

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_uint			start_delay;
	philo = (t_philosopher *)arg;
	start_delay = calc_delay(philo);
	set_time_of_death(philo);
	pthread_mutex_lock(&philo->param->mutex[M_START]);
	pthread_mutex_unlock(&philo->param->mutex[M_START]);
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
	pthread_mutex_lock(&philo->mutex[M_DINE_STAT]);
	philo->dine_status = JUST_FINISHED;
	pthread_mutex_unlock(&philo->mutex[M_DINE_STAT]);
	return (NULL);
}
