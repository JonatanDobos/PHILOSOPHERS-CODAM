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

typedef struct s_input_param
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
}	t_inp_param;

typedef struct s_philosopher
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eaten;
	pthread_mutex_t	*forks;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				max_meals;
}	t_philosopher;

int		_atoi(char *str);
double	_get_time(double start);
double	_get_time_static(bool set_start);
void	print_action(int p_id, char *message);

#endif