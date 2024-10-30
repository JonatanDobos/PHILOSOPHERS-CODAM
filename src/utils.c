/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:12 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/30 11:21:20 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

__uint64_t	get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / (__uint64_t)1000));
}

int	usleep_interval(t_param *param, __uint64_t time_to_sleep)
{
	t_tv		tv;
	__uint64_t	time_in_us;

	if (gettimeofday(&tv, NULL))
		return (EXIT_FAILURE);
	time_in_us = ((tv.tv_sec % 10000) * 1000000) + tv.tv_usec;
	time_to_sleep += time_in_us;
	while (time_in_us < time_to_sleep && param->death_flag == false)
	{
		usleep(500);
		if (gettimeofday(&tv, NULL))
			return (EXIT_FAILURE);
		time_in_us = ((tv.tv_sec % 10000) * 1000000) + tv.tv_usec;
	}
	return (EXIT_SUCCESS);
}
