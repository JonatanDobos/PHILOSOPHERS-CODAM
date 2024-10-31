/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 12:36:26 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/31 14:31:03 by jdobos        ########   odam.nl         */
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
	//check if 1 philo, or error from init
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
