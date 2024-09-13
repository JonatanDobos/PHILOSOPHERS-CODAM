/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/13 13:40:59 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->param->death_flag)
	{
		take_forks(philo);
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	philo->param->state[philo->id - 1] = -1;
	return (NULL);
}

bool	create_philo_threads(
	t_philosopher *phil_data,
	pthread_mutex_t *forks,
	t_param *param,
	pthread_t *philosophers)
{
	int	i;

	i = 0;
	while (i < param->p_amount)
	{
		phil_data[i].forks = forks;
		init_philosopher_data(&phil_data[i], param, i);
		if (pthread_create(&philosophers[i], NULL, routine, &phil_data[i]))
			return (EXIT_FAILURE);
		usleep(100);
		++i;
	}
	return (EXIT_SUCCESS);
}

bool	join_threads(
	pthread_t *observer, pthread_t *philosophers, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->p_amount)
	{
		if (pthread_join(philosophers[i++], NULL) != 0)
			return (EXIT_FAILURE);
	}
	if (pthread_join(*observer, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	setup_threads(t_main *m)
{
	init_mutex(m->forks, m->param->p_amount);
	m->param->start_time = _get_time_ms();
	if (create_philo_threads(m->p_data, m->forks, m->param, m->philo))
		return (EXIT_FAILURE);
	if (pthread_create(&m->observer, NULL, observer_routine, m))
		return (EXIT_FAILURE);
	pthread_detach(m->observer);
	if (join_threads(&m->observer, m->philo, m->param))
		return (destroy_mutex(m->forks, m->param->p_amount), 0);
	return (destroy_mutex(m->forks, m->param->p_amount), 1);
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_param	param;
	bool	errornum;

	if (argc < 5 || argc > 6 || init_parameters(argc, argv, &param))
	{
		printf("Syntax Error!\nUsage: %s %s", argv[0], PROMPT);
		return (EXIT_FAILURE);
	}
	init_mutex(&param.write_lock, 1);
	param.death_flag = false;
	main.param = &param;
	if (malloc_structs(&main))
		return (EXIT_FAILURE);
	errornum = setup_threads(&main);
	destroy_mutex(&param.write_lock, 1);
	cleanup(&main);
	if (errornum)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
