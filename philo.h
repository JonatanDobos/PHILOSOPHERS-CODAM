/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:33 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/11 17:43:35 by jdobos        ########   odam.nl         */
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
Values lower than 1 not allowed!"

enum	e_error
{
	RETURN_SAVED_ERRNO = -1
};

enum	e_finish_state
{
	JUST_FINISHED = 0,
	FINISHED,
	DINING
};

enum	e_mutex_param
{
	M_PRINT = 0,
	M_DEATH_FLAG,
	M_START
};

enum	e_mutex_phil
{
	M_DINE_STAT = 0,
	M_DEATH_TIME,
};

enum	e_action
{
	EAT = 0,
	SLEEP,
	THINK,
	FORK,
	DIED
};

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;
typedef struct timeval	t_tv;

typedef struct s_param
{
	t_uint			p_amount;
	t_uint			time_to_die;
	t_uint			time_to_eat;
	t_uint			time_to_sleep;
	t_uint			max_meals;
	bool			death_flag;
	t_ulong			start_time;
	t_uint			sleep_time_us;
	bool			uneven;
	pthread_mutex_t	mutex[3];
}	t_param;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				l_fork;
	int				r_fork;
	t_uint			times_eaten;
	short			dine_status;
	t_ulong			time_of_death;
	pthread_mutex_t	*forks;
	t_param			*param;
	pthread_mutex_t	mutex[2];
}	t_philosopher;

typedef struct s_main
{
	t_param			param;
	pthread_mutex_t	*forks;
	t_philosopher	*philo;
}	t_main;

// philo_routine.c
void		*philo_routine(void *arg);
void		set_time_of_death(t_philosopher *philo);

// input_handling.c
bool		init_parameters(int argc, char **argv, t_param *param);
bool		check_input(t_main *m, int argc, char **argv);

// utils.c
t_ulong		get_time_ms(void);
bool		usleep_interval(t_param *param, t_ulong time_to_sleep);
bool		death_check(t_param *param);
int			save_errno(int new_errno);
void		print_activity(int id, t_param *param, short activity);

// malloc_and_free.c
bool		malloc_structs(t_main *main);
void		cleanup(t_main *main);
int			init_philo_mutex(t_philosopher *philo, t_uint amount);
int			destr_philo_mutex(t_philosopher *philo, t_uint amount);

// math.c
double		sqrt_approx(double num);
t_uint		calc_delay(t_philosopher *philo);

// acivities.c
void		take_forks(t_philosopher *philo);
void		clean_forks(t_philosopher *philo);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		thinking(t_philosopher *philo);

// observer.c
void		monitor(t_main *m);

// utils_pthread.c
int			init_mutex(pthread_mutex_t *mutexes, t_uint amount);
int			destroy_mutex(pthread_mutex_t *mutexes, t_uint amount);
int			create_philo_threads(
				t_philosopher *philo, pthread_mutex_t *forks, t_param *param);
int			join_threads(t_philosopher *philos, t_uint amount);

// init.c
void		init_philosopher_data(t_philosopher *philo, t_param *param, int i);
void		safety_init(t_main *main);

#endif