#include "../philo.h"

int	_atoi(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		++i;
	while (str[i])
	{
		ret = ret * 10 + (str[i] - '0');
		++i;
	}
	return (ret);
}

uint64_t	_get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000));
}

void	print_action(t_philosopher *philo, char *message)
{
	const uint64_t	time = _get_time_ms() - philo->param->start_time;
	
	pthread_mutex_lock(&philo->write);
	printf("%llu %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->write);
}