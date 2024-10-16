/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:33 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/17 16:28:28 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>
# include <termios.h>
# include <pthread.h>

# define PROMPT "Syntax Error! correct usage:\n./philo \
[number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat](optional)\n\
philosophers min: 60  max: 200\n"

# ifndef EXPLICIT_RULES
#  define EXPLICIT_RULES true
# endif

// # ifndef PRINT_COLOR
// #  define PRINT_COLOR false
// # endif

enum	e_error
{
	GET_SAVED_ERRNO = -1
};

enum	e_finish_state
{
	JUST_FINISHED,
	FINISHED,
	EATING
};

enum	e_action
{
	EAT = 0,
	SLEEP,
	THINK,
	FORK,
	DIED
};

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
	__uint64_t		start_time;
	pthread_mutex_t	write_lock;
	// pthread_mutex_t	state_lock;
}	t_param;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				l_fork;
	int				r_fork;
	int				times_eaten;
	short			finished;
	__uint64_t		time_of_death;
	pthread_mutex_t	*forks;
	t_param			*param;
}	t_philosopher;

typedef struct s_main
{
	t_param			param;
	pthread_mutex_t	*forks;
	t_philosopher	*philo;
}	t_main;

// main.c
void		*philo_routine(void *arg);

// utils.c
__uint64_t	get_time_ms(void);
bool		init_parameters(int argc, char **argv, t_param *param);
bool		check_input(t_main *m, int argc, char **argv);

// utils_print.c
int			save_errno(int new_errno);
void		print_activity(int id, t_param *param, short activity);

// malloc_and_free.c
bool		malloc_structs(t_main *main);
void		cleanup(t_main *main);

// acivities.c
void		take_forks(t_philosopher *philo);
void		clean_forks(t_philosopher *philo);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		thinking(t_philosopher *philo);

// observer.c
void		observer_routine(t_main *m);

// utils_pthread.c
bool		init_mutex(pthread_mutex_t *mutexes, int amount);
bool		destroy_mutex(pthread_mutex_t *mutexes, int amount);
bool		create_philo_threads(
			t_philosopher *philo, pthread_mutex_t *forks, t_param *param);
bool		join_threads(t_philosopher *philos, int amount);

// init.c
void		init_philosopher_data(t_philosopher *philo, t_param *param, int i);
void		safety_init(t_main *main);

#endif