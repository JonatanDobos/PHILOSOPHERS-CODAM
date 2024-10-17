/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   observer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:09 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/17 16:29:23 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	death(t_param *param, __uint16_t i)
{
	param->death_flag = true;
	print_activity(i + 1, param, DIED);
}

void	observer_routine(t_main *m)
{
	__uint16_t	i;
	__uint16_t	finished;

	finished = 0;
	while (finished < m->param.p_amount)
	{
		i = 0;
		while (i < m->param.p_amount)
		{
			if (m->philo[i].finished == JUST_FINISHED)
			{
				++finished;
				m->philo[i].finished = FINISHED;
			}
			else if (m->philo[i].finished == EATING
				&& get_time_ms() > m->philo[i].time_of_death)
			{
				death(&m->param, i);
				return ;
			}
			++i;
		}
	}
}
