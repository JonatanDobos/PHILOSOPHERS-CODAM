#include "../philo.h"

bool	lock_fork(t_philosopher *philo, __uint64_t timestamp, bool fork)
{
	while (_get_time_ms() - timestamp < philo->time_to_die)
	{
		if (fork && !pthread_mutex_lock(&philo->forks[philo->right_fork]))
			return (print_action(philo->id, "has taken a fork"), true);
		if (!fork && !pthread_mutex_lock(&philo->forks[philo->left_fork]))
			return (print_action(philo->id, "has taken a fork"), true);
	}
	return (false);
}

bool	lock_forks(t_philosopher *philo, double timestamp)
{
	if (philo->id % 2 == 0)
	{
		if (!lock_fork(philo, timestamp, false))
			return (false);
		if (!lock_fork(philo, timestamp, true))
			return (pthread_mutex_unlock(&philo->forks[philo->left_fork]), false);
		return (print_action(philo->id, "is eating"), true);
	}
	if (!lock_fork(philo, timestamp, true))
		return (false);
	if (!lock_fork(philo, timestamp, false))
		return (pthread_mutex_unlock(&philo->forks[philo->right_fork]), false);
	return (print_action(philo->id, "is eating"), true);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	__uint64_t		timestamp;

	philo = (t_philosopher *)arg;
	while (!(*philo->death) && philo->times_eaten < philo->max_meals)
	{
		timestamp = _get_time_ms();
		print_action(philo->id, "is thinking");
		if (!lock_forks(philo, timestamp))
			return (print_action(philo->id, "died"), *philo->death = true, NULL);
		usleep(philo->time_to_eat);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
		print_action(philo->id, "is sleeping");
		usleep(philo->time_to_sleep);
	}
	return NULL;
}

void	init_philosopher_data(
	t_philosopher *philo, t_inp_param *input, pthread_mutex_t *forks, int i)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % input->number_of_philosophers;
	philo->forks = forks;
	philo->time_to_eat = input->time_to_eat;
	philo->time_to_sleep = input->time_to_sleep;
	philo->time_to_die = input->time_to_die;
	philo->max_meals = (input->max_meals == -1) ? 999999 : input->max_meals;
	philo->times_eaten = 0;
}

void	 execution(t_inp_param *input)
{
	pthread_t		philosophers[input->number_of_philosophers];
	pthread_mutex_t	forks[input->number_of_philosophers];
	t_philosopher	phil_data[input->number_of_philosophers];
	bool			death_signal;
	int				i;

	i = 0;
	while (i < input->number_of_philosophers)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	death_signal = false;
	while (i < input->number_of_philosophers)
	{
		phil_data[i].death = &death_signal;
		init_philosopher_data(&phil_data[i], input, forks, i);
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