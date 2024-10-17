/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/17 16:19:50 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
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
	philo->finished = JUST_FINISHED;
	return (NULL);
}

static bool	dinner_time(t_main *m)
{
	if (init_mutex(m->forks, m->param.p_amount))
		return (EXIT_FAILURE);
	m->param.start_time = get_time_ms();
	if (create_philo_threads(m->philo, m->forks, &m->param))
		return (cleanup(m), EXIT_FAILURE);
	observer_routine(m);
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
	if (init_mutex(&m.param.write_lock, 1))
		return (save_errno(GET_SAVED_ERRNO));
	m.param.death_flag = false;
	if (malloc_structs(&m))
		return (save_errno(GET_SAVED_ERRNO));
	dinner_time(&m);
	cleanup(&m);
	destroy_mutex(&m.param.write_lock, 1);
	return (save_errno(GET_SAVED_ERRNO));
}
