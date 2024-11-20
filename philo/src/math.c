/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 16:06:11 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/20 15:54:50 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_uint	calc_delay(t_param *param)
{
	const t_uint	p_amount = param->p_amount;
	long			spare_time_us;
	t_uint			value;

	spare_time_us = ((param->time_to_die - (param->time_to_sleep \
		+ (param->time_to_eat * (1 + (p_amount % 2))))) * 1000) - 100;
	value = (t_uint)(((double)(p_amount * 30 + 100)) * MULTIPLIER);
	if (spare_time_us > 0 && value > spare_time_us)
		return (spare_time_us);
	return (value);
}

t_uint	calc_interval(t_param *param)
{
	t_uint	value;

	value = (t_uint)(((double)(param->p_amount * 3 + 100)) * MULTIPLIER);
	if (value > 990)
		return (990);
	return (value);
}

t_uint	calc_thinktime(t_param *param)
{
	const t_uint	p_amount = param->p_amount;
	long			spare_time_us;
	t_uint			value;

	spare_time_us = ((param->time_to_die - (param->time_to_sleep \
		+ (param->time_to_eat * (1 + (p_amount % 2))))) * 1000) - 100;
	value = (t_uint)(((double)((p_amount * 30 + 100) * (p_amount % 2))) \
		* MULTIPLIER);
	if (spare_time_us > 0 && value > spare_time_us)
		return (spare_time_us);
	return (value);
}

t_uint	calc_monitor_rest(t_param *param)
{
	t_uint	value;

	value = (t_uint)(((double)(param->p_amount * 2)) * MULTIPLIER);
	if (value > 790)
		return (790);
	return (value);
}
