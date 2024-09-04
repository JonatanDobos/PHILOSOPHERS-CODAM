#include "../philo.h"

bool	lock_fork(t_philosopher *philo, __uint64_t timestamp, bool fork)
{
	while (_get_time_ms() - timestamp < philo->param->time_to_die)
	{
		if (fork && !pthread_mutex_lock(&philo->forks[philo->r_fork]))
			return (print_action(philo->id, "has taken a fork"), true);
		if (!fork && !pthread_mutex_lock(&philo->forks[philo->l_fork]))
			return (print_action(philo->id, "has taken a fork"), true);
	}
	return (false);
}

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
	return NULL;
}

void	 setup_threads(t_param *param)
{
	pthread_t		philosophers[param->number_of_philosophers];
	pthread_mutex_t	forks[param->number_of_philosophers];
	pthread_mutex_t	monitors[param->number_of_philosophers];
	t_philosopher	phil_data[param->number_of_philosophers];
	int				i;

	init_mutex(forks, param->number_of_philosophers);
	init_mutex(&write, 1);
	i = 0;
	param->start_time = _get_time_ms();
	while (i < param->number_of_philosophers)
	{
		phil_data->forks = forks;
		init_philosopher_data(&phil_data[i], param, i);
		pthread_create(&philosophers[i], NULL, routine, &phil_data[i]);
		pthread_detach(philosophers[i]);
		++i;
	}
	destroy_mutex(forks, param->number_of_philosophers);
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_mutex_t	write;
	bool			death_signal;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s %s", argv[0], PROMPT);
		return 1;
	}
	param.number_of_philosophers = _atoi(argv[1]);
	param.time_to_die = _atoi(argv[2]);
	param.time_to_eat = _atoi(argv[3]);
	param.time_to_sleep = _atoi(argv[4]);
	if (argc == 6)
		param.max_meals = _atoi(argv[5]);
	else
		param.max_meals = 0;
	param.write = write;
	setup_threads(&param);
	return (0);
}