/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:43:37 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/08 15:55:07 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		if (death_check(philo->param))
			return (pthread_mutex_unlock(&philo->forks[philo->r_fork]));
		print_activity(philo->id, philo->param, FORK);
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (death_check(philo->param))
			return (pthread_mutex_unlock(&philo->forks[philo->r_fork]), \
				pthread_mutex_unlock(&philo->forks[philo->l_fork]));
		print_activity(philo->id, philo->param, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (death_check(philo->param))
			return (pthread_mutex_unlock(&philo->forks[philo->l_fork]));
		print_activity(philo->id, philo->param, FORK);
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		if (death_check(philo->param))
			return (pthread_mutex_unlock(&philo->forks[philo->l_fork]), \
				pthread_mutex_unlock(&philo->forks[philo->r_fork]));
		print_activity(philo->id, philo->param, FORK);
	}
	return (0);
}

void	clean_forks(t_philosopher *philo)
{
	if (death_check(philo->param))
		return ;
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
}

void	eating(t_philosopher *philo)
{
	if (death_check(philo->param))
		return ((void)pthread_mutex_unlock(&philo->forks[philo->r_fork]), \
			(void)pthread_mutex_unlock(&philo->forks[philo->l_fork]));
	pthread_mutex_lock(&philo->mutex[M_DEATH_TIME]);
	philo->time_of_death = get_time_ms() + \
			(t_ulong)(philo->param->time_to_die);
	pthread_mutex_unlock(&philo->mutex[M_DEATH_TIME]);
	print_activity(philo->id, philo->param, EAT);
	usleep_interval(philo->param, philo->param->time_to_eat * 1000);
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
