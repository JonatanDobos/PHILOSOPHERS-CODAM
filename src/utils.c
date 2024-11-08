/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:12 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/08 12:08:50 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_ulong	get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	usleep_interval(t_param *param, t_ulong time_to_sleep)
{
	t_tv	tv;
	t_ulong	time_in_us;

	gettimeofday(&tv, NULL);
	time_in_us = ((tv.tv_sec % 100000L) * 1000000L) + tv.tv_usec;
	time_to_sleep += time_in_us;
	while (time_in_us < time_to_sleep && !death_check(param))
	{
		usleep(param->sleep_time_us);
		gettimeofday(&tv, NULL);
		time_in_us = ((tv.tv_sec % 100000L) * 1000000L) + tv.tv_usec;
	}
}

bool	death_check(t_param *param)
{
	bool	status;

	pthread_mutex_lock(&param->mutex[M_DEATH_FLAG]);
	status = param->death_flag;
	pthread_mutex_unlock(&param->mutex[M_DEATH_FLAG]);
	return (status);
}

// input negative value to return current_errno without changing it
int	save_errno(int new_errno)
{
	static int	current_errno;

	if (new_errno >= 0)
		current_errno = new_errno;
	return (current_errno);
}

void	print_activity(int id, t_param *param, short activity)
{
	t_ulong		time;
	const char	output[5][17] = {"is eating", "is sleeping", \
		"is thinking", "has taken a fork", "died"};

	pthread_mutex_lock(&param->mutex[M_PRINT]);
	time = get_time_ms() - param->start_time;
	printf("%lu %d %s\n", time, id, output[activity]);
	pthread_mutex_unlock(&param->mutex[M_PRINT]);
}
