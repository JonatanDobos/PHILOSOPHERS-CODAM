/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 16:30:45 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/23 13:06:33 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	__uint64_t	time;
	const char	output[5][15] = {"is eating", "is sleeping", \
		"is thinking", "has taken fork", "died"};

	// implement color for easier debugging?
	pthread_mutex_lock(&param->write_lock);
	time = get_time_ms() - param->start_time;
	printf("%5llu  %-3d %s\n", time, id, output[activity]);
	pthread_mutex_unlock(&param->write_lock);
}
