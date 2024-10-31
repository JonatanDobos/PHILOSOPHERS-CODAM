/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 10:59:02 by joni          #+#    #+#                 */
/*   Updated: 2024/10/31 13:18:28 by jdobos        ########   odam.nl         */
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

static bool	p_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	init_parameters(int argc, char **argv, t_param *param)
{
	int	tmp;

	param->p_amount = p_atoi(argv[1]);
	param->time_to_die = p_atoi(argv[2]);
	param->time_to_eat = p_atoi(argv[3]);
	param->time_to_sleep = p_atoi(argv[4]);
	if (param->p_amount < 1 || param->time_to_die < 1
		|| param->time_to_eat < 1 || param->time_to_sleep < 1)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		tmp = p_atoi(argv[5]);
		if (tmp == 0)
			return (EXIT_FAILURE);
		param->max_meals = tmp;
	}
	else
		param->max_meals = 0;
	param->sleep_time_us = param->p_amount * 2 + 100;
	param->uneven = param->p_amount % 2;
	return (EXIT_SUCCESS);
}

bool	check_input(t_main *m, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (printf("%s", PROMPT), EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] && p_isdigit(argv[i][j]))
			++j;
		if (argv[i][j] != '\0')
			return (printf("%s", PROMPT), EXIT_FAILURE);
		++i;
	}
	if (init_parameters(argc, argv, &m->param))
		return (printf("%s", PROMPT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
