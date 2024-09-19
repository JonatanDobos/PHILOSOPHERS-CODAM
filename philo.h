/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:33 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/19 15:16:09 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct timeval	t_tv;

typedef struct s_param
{
	__uint16_t		p_amount;
	__uint16_t		time_to_die;
	__uint16_t		time_to_eat;
	__uint16_t		time_to_sleep;
	__uint16_t		max_meals;
	bool			death_flag;
	bool			exit_flag;
	__uint64_t		*state;
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

typedef struct s_main
{
	t_param			*param;
	pthread_t		*philo;
	pthread_mutex_t	*forks;
	t_philosopher	*p_data;
	pthread_t		observer;
}	t_main;

int			_atoi(char *str);
__uint64_t	_get_time_ms(void);
void		print_activity(int id, t_param *param, char *message);
bool		init_parameters(int argc, char **argv, t_param *param);

bool		malloc_structs(t_main *main);
void		cleanup(t_main *main);

void		take_forks(t_philosopher *philo);
void		clean_forks(t_philosopher *philo);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		thinking(t_philosopher *philo);

void		*observer_routine(void *arg);

void		init_mutex(pthread_mutex_t *mutexes, int amount);
void		destroy_mutex(pthread_mutex_t *mutexes, int amount);

void		init_philosopher_data(t_philosopher *philo, t_param *param, int i);
#endif