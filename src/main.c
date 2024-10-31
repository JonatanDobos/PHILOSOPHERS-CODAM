/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/31 17:46:25 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	dinner_time(t_main *m)
{
	if (init_mutex(m->forks, m->param.p_amount))
		return (save_errno(errno));
	pthread_mutex_lock(&m->param.mutex[START]);
	if (create_philo_threads(m->philo, m->forks, &m->param))
	{
		destroy_mutex(m->forks, m->param.p_amount);
		return (EXIT_FAILURE);
	}
	monitor(m);
	if (join_threads(m->philo, m->param.p_amount))
		return (destroy_mutex(m->forks, m->param.p_amount), 1);
	return (destroy_mutex(m->forks, m->param.p_amount), 0);
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
	if (dinner_time(&m))
		return (cleanup(&m), save_errno(RETURN_SAVED_ERRNO));
	cleanup(&m);
	return (save_errno(RETURN_SAVED_ERRNO));
}
