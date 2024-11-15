/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:02 by jdobos        #+#    #+#                 */
/*   Updated: 2024/11/15 16:21:36 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	dinner_time(t_main *m)
{
	if (init_mutex(m->forks, m->param.p_amount))
		return (save_errno(errno));
	if (create_philo_threads(m->philo, m->forks, &m->param))
	{
		destroy_mutex(m->forks, m->param.p_amount);
		return (FAILURE);
	}
	usleep(42);
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
	if (init_mutex(m.param.mutex, 3))
		return (save_errno(RETURN_SAVED_ERRNO));
	if (malloc_structs(&m))
		return (save_errno(RETURN_SAVED_ERRNO));
	dinner_time(&m);
	destr_philo_mutex(m.philo, m.param.p_amount);
	cleanup(&m);
	return (save_errno(RETURN_SAVED_ERRNO));
}
