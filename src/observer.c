/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   observer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:09 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/12 15:59:02 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	death(t_param *param, __uint16_t i)
{
	param->death_flag = true;
	print_activity(i + 1, param, "died");
	exit(EXIT_SUCCESS);
}

void	*observer_routine(void *arg)
{
	t_param		*param;
	__uint64_t	cur_time;
	__uint16_t	i;
	__uint16_t	finished;

	param = (t_param *)arg;
	cur_time = _get_time_ms();
	finished = 0;
	while (finished < param->p_amount)
	{
		i = 0;
		while (i < param->p_amount)
		{
			if (param->state[i] == -1)
			{
				++finished;
				param->state[i] = 0;
			}
			else if (param->state[i] && _get_time_ms() > param->state[i])
				death(param, i);
			++i;
		}
	}
	exit(EXIT_SUCCESS);
}
