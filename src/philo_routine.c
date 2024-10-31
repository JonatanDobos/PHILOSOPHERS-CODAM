/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/31 17:11:38 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_uint	calc_delay(int id, t_uint p_amount, t_uint time_to_die)
{
	return ((1 - id % 2) * p_amount * (time_to_die / 10));
}

static t_ulong	calc_tod(t_uint time_to_die)
{
	return (get_time_ms() + (t_ulong)(time_to_die));
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

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_uint			start_delay;

	philo = (t_philosopher *)arg;
	start_delay = calc_delay(philo->id, philo->param->p_amount, \
		philo->param->time_to_die);
	philo->time_of_death = calc_tod(philo->param->time_to_die);
	pthread_mutex_lock(&philo->param->mutex[START]);
	pthread_mutex_unlock(&philo->param->mutex[START]);
	if (one_philo_exception(philo))
		return (NULL);
	usleep(start_delay);
	while (!philo->param->death_flag)
	{
		thinking(philo);
		take_forks(philo);
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
	}
	pthread_mutex_lock(&philo->param->mutex[EAT_COUNT]);
	philo->dine_status = JUST_FINISHED;
	pthread_mutex_unlock(&philo->param->mutex[EAT_COUNT]);
	return (NULL);
}
