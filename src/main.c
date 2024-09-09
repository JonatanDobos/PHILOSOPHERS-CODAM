#include "../philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		print_activity(philo->id, philo->param, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		print_activity(philo->id, philo->param, "has taken fork");
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		print_activity(philo->id, philo->param, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		print_activity(philo->id, philo->param, "has taken fork");
	}
}

void	clean_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
}

void	eating(t_philosopher *philo)
{
	__uint64_t	tod;

	if (philo->param->death_flag)
		return ;
	tod = _get_time_ms() + (__uint64_t)(philo->param->time_to_die + philo->param->time_to_eat);
	philo->param->states[philo->id - 1] = tod;
	usleep(philo->param->time_to_eat * 1000);
	philo->times_eaten++;
}

void	sleeping(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, "is sleeping");
	usleep(philo->param->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	if (philo->param->death_flag)
		return ;
	print_activity(philo->id, philo->param, "is thinking");
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while ((!philo->param->max_meals
			|| philo->times_eaten < philo->param->max_meals)
			&& !philo->param->death_flag)
	{
		take_forks(philo);
		eating(philo);
		clean_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
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

bool	 setup_threads(t_param *param)
{
	pthread_t		philosophers[param->number_of_philosophers];
	pthread_mutex_t	forks[param->number_of_philosophers];
	__uint64_t		philo_states[param->number_of_philosophers];
	t_philosopher	phil_data[param->number_of_philosophers];

	init_mutex(forks, param->number_of_philosophers);
	param->states = philo_states;
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