#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <termios.h>
# include <pthread.h>

// TEST!
# define C_RESET "\033[0m"
# define C_BOLD "\033[1m"

typedef struct timeval	t_tv;

typedef struct s_param
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	uint64_t	start_time;
}	t_param;

typedef struct s_philosopher
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				times_eaten;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_param			*param;
}	t_philosopher;

int			_atoi(char *str);
uint64_t	_get_time_ms(void);
void		print_action(t_philosopher *philo, char *message);

void		init_mutex(pthread_mutex_t *mutexes, int amount);
void		destroy_mutex(pthread_mutex_t *mutexes, int amount);

void		init_philosopher_data(t_philosopher *philo, t_param *param, int i);
#endif