/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:12 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/12 23:04:57 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	p_atoi(char *str)
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

__uint64_t	get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / (__uint64_t)1000));
}

static bool	p_isdigit(char c)
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
		while (argv[i][j] && p_isdigit(argv[i][j]))
			++j;
		if (argv[i][j] != '\0')
			return (1);
		++i;
	}
	param->p_amount = p_atoi(argv[1]);
	param->time_to_die = p_atoi(argv[2]);
	param->time_to_eat = p_atoi(argv[3]);
	param->time_to_sleep = p_atoi(argv[4]);
	if (param->p_amount < 1 || param->time_to_die < 1
		|| param->time_to_eat < 1 || param->time_to_sleep < 1)
		return (1);
	if (argc == 6)
		param->max_meals = p_atoi(argv[5]);
	else
		param->max_meals = 0;
	return (0);
}

bool	check_input(t_main *m, int argc, char **argv)
{
	if (argc < 5 || argc > 6 || init_parameters(argc, argv, &m->param))
	{
		printf("Syntax Error!\nUsage: %s %s", argv[0], PROMPT);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
