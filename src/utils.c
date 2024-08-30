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

__uint64_t	_get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(int p_id, char *message)
{
	const __uint64_t	time = _get_time_ms();
	
	printf("%lu %d %s\n", time, p_id, message);
}