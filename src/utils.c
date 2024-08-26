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

double	_get_time(double start)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (((double)tv.tv_usec / 1000) - start);
}
