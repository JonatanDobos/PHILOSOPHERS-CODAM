#include "../philo.h"

void	*observer_routine(void *arg)
{
	t_param		*param;
	__uint64_t	cur_time;
	__uint16_t	i;

	param = (t_param *)arg;
	cur_time = _get_time_ms();
	while (1)
	{
		i = 0;
		while (i < param->number_of_philosophers)
		{
			if (_get_time_ms() > param->states[i])
			{
				param->death_flag = true;
				print_activity(i, param, "died");
				exit(EXIT_SUCCESS);
			}
			++i;
		}
	}
	exit(EXIT_SUCCESS);
}