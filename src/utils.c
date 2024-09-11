/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:12 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/11 15:06:46 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	_atoi(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		++i;
	while (str[i])
	{
		ret = ret * 10 + (str[i] - '0');
		++i;
	}
	return (ret);
}

__uint64_t	_get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / (__uint64_t)1000));
}

void	print_activity(int id, t_param *param, char *message)
{
	const __uint64_t	time = _get_time_ms() - param->start_time;

	pthread_mutex_lock(&param->write_lock);
	printf("%05lu %d %s\n", time, id, message);
	pthread_mutex_unlock(&param->write_lock);
}

bool	_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	init_parameters(int argc, char **argv, t_param *param)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] && _isdigit(argv[i][j]))
			++j;
		if (argv[i][j] != '\0')
			return (1);
		++i;
	}
	param->number_of_philosophers = _atoi(argv[1]);
	param->time_to_die = _atoi(argv[2]);
	param->time_to_eat = _atoi(argv[3]);
	param->time_to_sleep = _atoi(argv[4]);
	if (param->number_of_philosophers < 1 || param->time_to_die < 1
		|| param->time_to_eat < 1 || param->time_to_sleep < 1)
		return (1);
	if (argc == 6)
		param->max_meals = _atoi(argv[5]);
	else
		param->max_meals = 0;
	return (0);
}

bool	malloc_structs()
{
	// LEFTOFF!!
}
