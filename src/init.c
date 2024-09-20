/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:41:49 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/20 12:43:56 by jdobos        ########   odam.nl         */
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
	philo->param->state[i] = _get_time_ms() + (__uint64_t)(param->time_to_die \
							+ param->time_to_eat + param->time_to_sleep);
	printf("INIT DEATHTIME: %d: %llu\n", i + 1, philo->param->state[i]);//test
}
