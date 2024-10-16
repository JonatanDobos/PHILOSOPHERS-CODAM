#include "../philo.h"

// input negative value to return current_errno without changing it
int	save_errno(int new_errno)
{
	static int	current_errno;

	if (new_errno >= 0)
		current_errno = new_errno;
	return (current_errno);
}

void	print_activity(int id, t_param *param, char *message)
{
	const __uint64_t	time = get_time_ms() - param->start_time;

	pthread_mutex_lock(&param->write_lock);
	printf("%llu %d %s\n", time, id, message);
	pthread_mutex_unlock(&param->write_lock);
}
