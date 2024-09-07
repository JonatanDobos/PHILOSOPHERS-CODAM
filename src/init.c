#include "../philo.h"

void	init_philosopher_data(t_philosopher *philo, t_param *param, int i)
{
	philo->id = i + 1;
	philo->l_fork = i;
	philo->r_fork = (i + 1) % param->number_of_philosophers;
	philo->param = param;
	philo->times_eaten = 0;
	philo->param->states[i] = _get_time_ms() + (__uint64_t)(param->time_to_die);
}
