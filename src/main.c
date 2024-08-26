#include "../philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	double			start;
	double			pre;
	double			post;

	philosopher = (t_philosopher *)arg;
	start = _get_time(0);
	while (philosopher->times_eaten < philosopher->max_meals)
	{
		// Pick up forks (lock mutexes)
		pthread_mutex_lock(&philosopher->forks[philosopher->left_fork]);
		pthread_mutex_lock(&philosopher->forks[philosopher->right_fork]);
		post = _get_time(start);
		if (post - pre > (double)philosopher->time_to_die)
		{
			pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
			pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
			printf("%.3f %d died\n", post, philosopher->id);
			return (NULL);
		}
		printf("%.3f %d has taken a fork\n", post, philosopher->id);
		// Simulate eating
		pre = _get_time(start);
		printf("%.3f %d is eating\n", pre, philosopher->id);
		usleep(philosopher->time_to_eat);
		philosopher->times_eaten++;
		// Put down forks (unlock mutexes)
		pthread_mutex_unlock(&philosopher->forks[philosopher->right_fork]);
		pthread_mutex_unlock(&philosopher->forks[philosopher->left_fork]);
		// Simulate sleeping
		pre = _get_time(start);
		printf("%.3f %d is sleeping\n", pre, philosopher->id);
		usleep(philosopher->time_to_sleep);
		// Simulate thinking (no specific action needed)
		pre = _get_time(start);
		printf("%.3f %d is thinking\n", pre, philosopher->id);
	}
	return NULL;
}

void	 execution(t_inp_param *input)
{
	pthread_t		philosophers[input->number_of_philosophers];
	pthread_mutex_t	forks[input->number_of_philosophers];
	t_philosopher	phil_data[input->number_of_philosophers];
	int				i;

	// Initialize mutexes
	i = 0;
	for (int i = 0; i < input->number_of_philosophers; i++) {
		pthread_mutex_init(&forks[i], NULL);
	}
	// Initialize and create philosopher threads
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
	// Join all threads (wait for them to finish)
	i = 0;
	while (i < input->number_of_philosophers)
		pthread_join(philosophers[i++], NULL);
	// Destroy mutexes
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