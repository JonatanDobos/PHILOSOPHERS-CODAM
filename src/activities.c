/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:43:37 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/12 23:13:33 by joni          ########   odam.nl         */
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
		print_activity(philo->id, philo->param, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, "has taken fork");
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		if (philo->param->death_flag)
			return ;
		print_activity(philo->id, philo->param, "has taken fork");
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
			(__uint64_t)(philo->param->time_to_die + \
			philo->param->time_to_eat + philo->param->time_to_sleep);
	print_activity(philo->id, philo->param, "is eating");
	usleep(philo->param->time_to_eat * 1000);
	philo->times_eaten++;
}

void	sleeping(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, "is sleeping");
	usleep(philo->param->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, "is thinking");
}
