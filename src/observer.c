#include "../philo.h"

void	*observer_routine(void *arg)
{
	t_param		*param;
	__uint64_t	cur_time;

	param = (t_param *)arg;
	cur_time = _get_time_ms();
	while (cur_time <= param->states[//DOES NOT WORK PROBS NEEDS INDIVIDUAL OBSERVERS!]) LEFTOFF!
		cur_time = _get_time_ms();
	param->death_flag = true;
	exit(EXIT_SUCCESS);
}