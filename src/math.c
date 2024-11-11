/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 16:06:11 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/11 16:55:40 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

double	sqrt_approx(double num)
{
	double	guess;
	t_uint	iter;

	if (num < 0)
		return (-1);
	iter = 5;
	guess = num / 2.0F;
	while (iter--)
	{
		guess = (guess + num / guess) / 2.0F;
	}
	return (guess);
}

t_uint	calc_delay(t_philosopher *philo)
{
	const int		id = philo->id;
	const double	p_amount = philo->param->p_amount;
	double			value;
	double			multiplier;

	multiplier = ((philo->param->time_to_eat + philo->param->time_to_sleep \
		+ (philo->param->time_to_die * 3)) / 10.0F) + 1.0F;
	value = ((sqrt_approx(p_amount) * multiplier) * 2.0) + 10.0;
	return ((1 - id % 2) * (t_uint)(value));
}
