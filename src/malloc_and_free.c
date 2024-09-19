/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_and_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 15:31:50 by joni          #+#    #+#                 */
/*   Updated: 2024/09/19 15:09:28 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	malloc_structs(t_main *main)
{
	const int	num = main->param->p_amount;

	main->param->state = (__uint64_t *)malloc(sizeof(__uint64_t) * num);
	if (!main->param->state)
		return (EXIT_FAILURE);
	main->philo = (pthread_t *)malloc(sizeof(pthread_t) * num);
	if (!main->philo)
		return (free(main->param->state), EXIT_FAILURE);
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!main->forks)
		return (free(main->param->state), free(main->philo), EXIT_FAILURE);
	main->p_data = (t_philosopher *)malloc(sizeof(t_philosopher) * num);
	if (!main->p_data)
		return (free(main->param->state), free(main->philo), \
				free(main->p_data), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	cleanup(t_main *main)
{
	free(main->forks);
	free(main->p_data);
	free(main->philo);
	free(main->param->state);
}
