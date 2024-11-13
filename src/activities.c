/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:43:37 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/13 15:36:41 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->forks[philo->r_fork]);
	if (death_check(philo->param))
	{
		pthread_mutex_unlock(&philo->forks[philo->r_fork]);
		return (false);
	}
	print_activity(philo->id, philo->param, FORK);
	pthread_mutex_lock(&philo->forks[philo->l_fork]);
	if (death_check(philo->param))
	{
		clean_forks(philo);
		return (false);
	}
	print_activity(philo->id, philo->param, FORK);
	return (true);
}

void	clean_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
}

void	eating(t_philosopher *philo)
{
	if (death_check(philo->param))
		return ;
	set_time_of_death(philo);
	print_activity(philo->id, philo->param, EAT);
	if (usleep_interval(philo->param, philo->param->time_to_eat * 1000))
		return ;
	philo->times_eaten++;
}

void	sleeping(t_philosopher *philo)
{
	if (death_check(philo->param))
		return ;
	print_activity(philo->id, philo->param, SLEEP);
	usleep_interval(philo->param, philo->param->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	const t_ulong	time = philo->param->uneven * \
		(philo->time_of_death - get_time_ms());

	if (death_check(philo->param))
		return ;
	print_activity(philo->id, philo->param, THINK);
	usleep_interval(philo->param, time);
}
