/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/11 15:07:51 by jdobos        ########   odam.nl         */
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
	while (i < param->number_of_philosophers)
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

bool	join_philo_threads(pthread_t *philosophers, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_join(philosophers[i++], NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	setup_threads(t_param *param)
{
	// SHOULD BE MALLOCED, LOOK IN UTILS!
	pthread_t		philosophers[param->number_of_philosophers];
	pthread_mutex_t	forks[param->number_of_philosophers];
	__uint64_t		philo_states[param->number_of_philosophers];
	t_philosopher	phil_data[param->number_of_philosophers];

	init_mutex(forks, param->number_of_philosophers);
	param->state = philo_states;
	param->start_time = _get_time_ms();
	if (create_philo_threads(phil_data, forks, param, philosophers))
		return (EXIT_FAILURE);
	if (pthread_create(&param->observer, NULL, observer_routine, param))
		return (EXIT_FAILURE);
	pthread_detach(param->observer);
	if (join_philo_threads(philosophers, param))
		return (destroy_mutex(forks, param->number_of_philosophers), 0);
	return (destroy_mutex(forks, param->number_of_philosophers), 1);
}

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc < 5 || argc > 6 || init_parameters(argc, argv, &param))
	{
		printf("Syntax Error!\nUsage: %s %s", argv[0], PROMPT);
		return (EXIT_FAILURE);
	}
	init_mutex(&param.write_lock, 1);
	param.death_flag = false;
	if (!setup_threads(&param))
		return (destroy_mutex(&param.write_lock, 1), EXIT_FAILURE);
	return (destroy_mutex(&param.write_lock, 1), EXIT_SUCCESS);
}
