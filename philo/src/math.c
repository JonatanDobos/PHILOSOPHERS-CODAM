/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 16:06:11 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/15 00:13:53 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

double	sqrt_approx(double num)
{
	double	guess;
	t_uint	iter;

	if (num < 0)
		return (-1);
	iter = 6;
	guess = num / 2.0F;
	while (iter--)
	{
		guess = (guess + num / guess) / 2.0F;
	}
	return (guess);
}

t_uint	calc_delay(t_param *param)
{
	const double	p_amount = param->p_amount;
	double			value;
	double			multiplier;

	multiplier = ((param->time_to_eat + param->time_to_sleep \
		+ (param->time_to_die * 3)) / 10.0F) + 1.0F;
	value = ((sqrt_approx(p_amount) * sqrt_approx(multiplier)) * 5.0) + 100.0;
	return ((t_uint)(value));
}

t_uint	calc_interval(t_param *param)
{
	return ((t_uint)(sqrt_approx(param->p_amount) * 22.0) + 100);
}
