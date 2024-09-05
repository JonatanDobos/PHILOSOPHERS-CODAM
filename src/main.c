#include "../philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		print_action(philo, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		print_action(philo, "has taken fork");
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		print_action(philo, "has taken fork");
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		print_action(philo, "has taken fork");
	}
}

bool	clean_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->forks[philo->l_fork]);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	__uint64_t		timestamp;

	philo = (t_philosopher *)arg;
	while (!philo->param->max_meals
			|| philo->times_eaten < philo->param->max_meals)
	{
		timestamp = _get_time_ms();
		take_forks(philo);
		usleep(philo->param->time_to_eat * 1000);
		philo->times_eaten++;
		clean_forks(philo);
		print_action(philo->id, "is sleeping");
		usleep(philo->param->time_to_sleep * 1000);
		print_action(philo->id, "is thinking");
	}
	return (NULL);
}

bool	 setup_threads(t_param *param)
{
	pthread_t		philosophers[param->number_of_philosophers];
	pthread_mutex_t	forks[param->number_of_philosophers];
	pthread_t		observer;
	t_philosopher	phil_data[param->number_of_philosophers];
	int				i;

	init_mutex(forks, param->number_of_philosophers);
	i = 0;
	param->start_time = _get_time_ms();
	if (pthread_create(&observer, NULL, observer_routine, param))
		return (destroy_mutex(forks, param->number_of_philosophers), 0);
	while (i < param->number_of_philosophers)
	{
		phil_data->forks = forks;
		init_philosopher_data(&phil_data[i], param, i);
		if (pthread_create(&philosophers[i], NULL, routine, &phil_data[i]))
			exit(EXIT_FAILURE);
		++i;
	}
	while (i < param->number_of_philosophers)
	{
		if (pthread_join(philosophers[i++], NULL) != 0)
			return (destroy_mutex(forks, param->number_of_philosophers), 0);
	}
	return (destroy_mutex(forks, param->number_of_philosophers), 1);
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_mutex_t	write_lock;
	bool			death_flag;

	if (argc < 5 || argc > 6 || !input_handling(argc, argv))
	{
		printf("Syntax Error!\nUsage: %s %s", argv[0], PROMPT);
		return (EXIT_FAILURE);
	}
	death_flag = false;
	init_mutex(&write_lock, 1);
	param.write_lock = write_lock;
	param.death_flag = &death_flag;
	if (!setup_threads(&param))
		return (destroy_mutex(&write_lock, 1), EXIT_FAILURE);
	return (destroy_mutex(&write_lock, 1), EXIT_SUCCESS);
}