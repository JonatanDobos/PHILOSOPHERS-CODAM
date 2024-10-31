/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/31 01:18:15 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->param->mutex[START]);
	pthread_mutex_unlock(&philo->param->mutex[START]);
	usleep((1 - philo->id % 2) * philo->param->p_amount * 2);
	while (!philo->param->death_flag)
	{
		take_forks(philo);
		eating(philo);
		clean_forks(philo);
		if (philo->times_eaten == philo->param->max_meals)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	pthread_mutex_lock(&philo->param->mutex[EAT_COUNT]);
	philo->dine_status = JUST_FINISHED;
	pthread_mutex_unlock(&philo->param->mutex[EAT_COUNT]);
	return (NULL);
}

static int	dinner_time(t_main *m)
{
	if (init_mutex(m->forks, m->param.p_amount))
		return (save_errno(errno));
	pthread_mutex_lock(&m->param.mutex[START]);
	if (create_philo_threads(m->philo, m->forks, &m->param))
		return (cleanup(m), EXIT_FAILURE);
	monitor(m);
	if (join_threads(m->philo, m->param.p_amount))
		return (destroy_mutex(m->forks, m->param.p_amount), 1);
	return (destroy_mutex(m->forks, m->param.p_amount));
}

int	main(int argc, char **argv)
{
	t_main	m;

	save_errno(0);
	if (check_input(&m, argc, argv))
		return (EINVAL);
	safety_init(&m);
	if (init_mutex(m.param.mutex, 5))
		return (save_errno(RETURN_SAVED_ERRNO));
	if (malloc_structs(&m))
		return (save_errno(RETURN_SAVED_ERRNO));
	dinner_time(&m);
	cleanup(&m);
	return (save_errno(RETURN_SAVED_ERRNO));
}
