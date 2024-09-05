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

# define PROMPT "number_of_philosophers time_to_die time_to_eat \
				time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

// TEST!
# define C_RESET "\033[0m"
# define C_BOLD "\033[1m"

typedef struct timeval	t_tv;

typedef struct s_param
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	bool			*death_flag;
	__uint64_t		start_time;
	pthread_mutex_t	write_lock;
}	t_param;

typedef struct s_philosopher
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				times_eaten;
	pthread_mutex_t	*forks;
	t_param			*param;
}	t_philosopher;

int			_atoi(char *str);
__uint64_t	_get_time_ms(void);
void		print_action(t_philosopher *philo, char *message);
bool		init_parameters(int argc, char **argv, t_param *param);

void		*observer_routine(void *arg);

void		init_mutex(pthread_mutex_t *mutexes, int amount);
void		destroy_mutex(pthread_mutex_t *mutexes, int amount);

void		init_philosopher_data(t_philosopher *philo, t_param *param, int i);
#endif