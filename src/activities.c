/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:43:37 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/30 11:23:28 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, FORK);
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, FORK);
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, FORK);
	}
}

void	clean_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
}

void	eating(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	philo->time_of_death = get_time_ms() + \
			(__uint64_t)(philo->param->time_to_die);
	print_activity(philo->id, philo->param, EAT);
	usleep_interval(philo->param, philo->param->time_to_eat * 1000);
	philo->times_eaten++;
}

void	sleeping(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, SLEEP);
	usleep_interval(philo->param, philo->param->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, THINK);
}
