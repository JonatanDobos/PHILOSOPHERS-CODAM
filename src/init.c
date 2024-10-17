/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:41:49 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/17 15:26:33 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philosopher_data(t_philosopher *philo, t_param *param, int i)
{
	philo->id = i + 1;
	philo->l_fork = i;
	philo->r_fork = (i + 1) % param->p_amount;
	philo->param = param;
	philo->times_eaten = 0;
	philo->finished = false;
	philo->time_of_death = get_time_ms() + (__uint64_t)(param->time_to_die \
							+ param->time_to_eat + param->time_to_sleep);
}

void	safety_init(t_main *main)
{
	main->param.exit_flag = false;
	main->param.death_flag = false;
	main->param.start_time = 0;
	main->philo = NULL;
	main->forks = NULL;
}
