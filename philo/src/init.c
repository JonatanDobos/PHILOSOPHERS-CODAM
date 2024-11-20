/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:41:49 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/20 15:45:06 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(
	t_philosopher *philo, t_param *param, int i, bool r_high)
{
	if (r_high == true)
	{
		philo->l_fork = i;
		philo->r_fork = (i + 1) % param->p_amount;
	}
	else
	{
		philo->r_fork = i;
		philo->l_fork = (i + 1) % param->p_amount;
	}
}

void	init_philosopher_data(t_philosopher *philo, t_param *param, int i)
{
	philo->id = i + 1;
	if (philo->id % 2 == 0)
		assign_forks(philo, param, i, false);
	else
		assign_forks(philo, param, i, true);
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
