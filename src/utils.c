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

double	_get_time(double start)// deprecated??
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return (((double)tv.tv_usec / 1000) - start);
}

double	_get_time_static(bool set_start)
{
	t_tv				tv;
	static long long	starting_point = 0;

	gettimeofday(&tv, NULL);
	if (set_start)
		starting_point = tv.tv_usec;
	return ((double)(tv.tv_usec - starting_point) / 1000);
}

void	print_action(int p_id, char *message)
{
	const double	time = _get_time_static(false);
	
	printf("%.3f %s%d%s %s\n", time, C_BOLD, p_id, C_RESET, message);
}