/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:41:49 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/15 16:17:38 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philosopher_data(t_philosopher *philo, t_param *param, int i)
{
	philo->id = i + 1;
	if (philo->id % 2 == 0)
	{
		philo->l_fork = i;
		philo->r_fork = (i + 1) % param->p_amount;
	}
	else
	{
		philo->r_fork = i;
		philo->l_fork = (i + 1) % param->p_amount;
	}
	// if (philo->id == param->p_amount)
	// {
	// 	philo->r_fork = i;
	// 	philo->l_fork = (i + 1) % param->p_amount;
	// }
	// else
	// {
	// 	philo->l_fork = i;
	// 	philo->r_fork = (i + 1) % param->p_amount;
	// }
	// fprintf(stderr, "P[%d] LF[%d]%p	RF[%d]%p\n", philo->id, \
	// 	philo->l_fork, &philo->forks[philo->l_fork], philo->r_fork, &philo->forks[philo->r_fork]);//t
	philo->param = param;
	philo->times_eaten = 0;
	philo->dine_status = DINING;
	philo->time_of_death = ULONG_MAX;
}

void	safety_init(t_main *main)
{
	main->param.death_flag = false;
	main->param.start_time = 0;
	main->philo = NULL;
	main->forks = NULL;
}
