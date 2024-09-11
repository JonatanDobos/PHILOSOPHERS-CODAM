/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 14:42:06 by jdobos        #+#    #+#                 */
/*   Updated: 2024/09/11 14:49:42 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&mutexes[i++], NULL))
			exit(EXIT_FAILURE);
	}
}

void	destroy_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_destroy(&mutexes[i++]))
			exit(EXIT_FAILURE);
	}
}
