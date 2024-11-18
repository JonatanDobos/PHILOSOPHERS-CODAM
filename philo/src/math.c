/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 16:06:11 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/18 15:38:42 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_uint	calc_delay(t_param *param)
{
	const t_uint	p_amount = (double)param->p_amount;
	t_uint			spare_time_us;
	t_uint			value;

	spare_time_us = ((param->time_to_die - (param->time_to_sleep \
		+ (param->time_to_eat * (1 + p_amount % 2)))) * 1000) - 500;
	value = ((float)(p_amount * 25) + 100) * (float)SLOWPOKE_MULTIPLIER;
	if (spare_time_us > 0 && value > spare_time_us)
		return (spare_time_us);
	return (value);
}

t_uint	calc_interval(t_param *param)
{
	t_uint	value;

	value = ((float)(param->p_amount * 2) + 100) * (float)SLOWPOKE_MULTIPLIER;
	if (value > 990)
		return (990);
	return (value);
}
