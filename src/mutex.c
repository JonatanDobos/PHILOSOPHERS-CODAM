#include "../philo.h"

void	init_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;
	
	i = 0;
	while (i < amount)
		pthread_mutex_init(&mutexes[i++], NULL);
}

void	destroy_mutex(pthread_mutex_t *mutexes, int amount)
{
	int	i;
	
	i = 0;
	while (i < amount)
		pthread_mutex_destroy(&mutexes[i++]);
}
