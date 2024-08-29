#include "../philo.h"

bool	lock_fork(
	pthread_mutex_t *fork_mutex, double time_to_die, double timestamp)
{
	while (_get_time_static(false) - timestamp < time_to_die)
	{
		if (!pthread_mutex_lock(fork_mutex))
			return (true);
	}
	return (false);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	double			timestamp;

	philo = (t_philosopher *)arg;
	_get_time_static(true);
	while (philo->times_eaten < philo->max_meals)
	{
		pthread_mutex_lock(&philo->forks[philo->left_fork]);// LEFTOFF!!
		print_action(philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		if (_get_time_static(false) - timestamp > (double)philo->time_to_die)
		{
			print_action(philo->id, "died");
			pthread_mutex_unlock(&philo->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->forks[philo->left_fork]);
			return (NULL);
		}
		print_action(philo->id, "has taken a fork");
		print_action(philo->id, "is eating");
		usleep(philo->time_to_eat);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
		print_action(philo->id, "is sleeping");
		usleep(philo->time_to_sleep);
		timestamp = _get_time_static(false);
		print_action(philo->id, "is thinking");
	}
	return NULL;
}

void	 execution(t_inp_param *input)
{
	pthread_t		philosophers[input->number_of_philosophers];
	pthread_mutex_t	forks[input->number_of_philosophers];
	t_philosopher	phil_data[input->number_of_philosophers];
	int				i;

	i = 0;
	while (i < input->number_of_philosophers)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		phil_data[i].id = i + 1;
		phil_data[i].left_fork = i;
		phil_data[i].right_fork = (i + 1) % input->number_of_philosophers;
		phil_data[i].forks = forks;
		phil_data[i].time_to_eat = input->time_to_eat;
		phil_data[i].time_to_sleep = input->time_to_sleep;
		phil_data[i].time_to_die = input->time_to_die;
		phil_data[i].max_meals = (input->max_meals == -1) ? 1000 : input->max_meals; // Default to a high number if not specified
		phil_data[i].times_eaten = 0;
		pthread_create(&philosophers[i], NULL, philosopher_routine, &phil_data[i]);
		++i;
	}
	i = 0;
	while (i < input->number_of_philosophers)
		pthread_join(philosophers[i++], NULL);
	i = 0;
	while (i < input->number_of_philosophers)
		pthread_mutex_destroy(&forks[i++]);
}

int	main(int argc, char **argv)
{
	t_inp_param	input;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return 1;
	}
	input.number_of_philosophers = _atoi(argv[1]);
	input.time_to_die = _atoi(argv[2]);
	input.time_to_eat = _atoi(argv[3]);
	input.time_to_sleep = _atoi(argv[4]);
	input.max_meals = (argc == 6) ? _atoi(argv[5]) : -1;
	execution(&input);
	return (0);
}