#include "philo.h"
#include <math.h>

t_ulong	get_time_ms(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

bool	usleep_interval(t_param *param, t_ulong time_to_sleep)
{
	t_tv	tv;
	t_ulong	time_in_us;
	bool	death;

	gettimeofday(&tv, NULL);
	time_in_us = ((tv.tv_sec % 100000L) * 1000000L) + tv.tv_usec;
	time_to_sleep += time_in_us;
	while (time_in_us < time_to_sleep && !death)
	{
		usleep(param->sleep_time_us);
		gettimeofday(&tv, NULL);
		time_in_us = ((tv.tv_sec % 100000L) * 1000000L) + tv.tv_usec;
		death = death_check(param);
	}
	return (death);
}

bool	death_check(t_param *param)
{
	bool	status;

	pthread_mutex_lock(&param->mutex[M_DEATH_FLAG]);
	status = param->death_flag;
	pthread_mutex_unlock(&param->mutex[M_DEATH_FLAG]);
	return (status);
}

// input negative value to return current_errno without changing it
int	save_errno(int new_errno)
{
	static int	current_errno;

	if (new_errno >= 0)
		current_errno = new_errno;
	return (current_errno);
}


// ----------- UTILS /\ ------------

static bool	p_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static t_uint	p_atoui(char *str)
{
	t_uint	i;
	t_ulong	ret;

	i = 0;
	ret = 0;
	while (str[i])
		++i;
	if (i > 10)
		return (save_errno(EINVAL));
	i = 0;
	while (str[i] && p_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - '0');
		++i;
	}
	if (ret > UINT_MAX)
		return (save_errno(EINVAL));
	return ((t_uint)ret);
}

bool	init_parameters(int argc, char **argv, t_param *param)
{
	int	tmp;

	param->p_amount = p_atoui(argv[1]);
	param->time_to_die = p_atoui(argv[2]);
	param->time_to_eat = p_atoui(argv[3]);
	param->time_to_sleep = p_atoui(argv[4]);
	if (save_errno(RETURN_SAVED_ERRNO) == EINVAL || param->p_amount < 1
		|| param->time_to_die < 1 || param->time_to_eat < 1
		|| param->time_to_sleep < 1)
		return (FAILURE);
	if (argc == 6)
	{
		tmp = p_atoui(argv[5]);
		if (tmp == 0)
			return (FAILURE);
		param->max_meals = tmp;
	}
	else
		param->max_meals = 0;
	param->sleep_time_us = (t_uint)(sqrt_approx(param->p_amount) * 25.0) + 100;
	printf("INTERVAL: %d\n", param->sleep_time_us);//test
	param->sleep_time_us = (param->p_amount * 2) + 100;
	printf("test INTERVAL: %d\n", param->sleep_time_us);//test
	param->uneven = param->p_amount % 2;
	return (SUCCESS);
}

bool	check_input(t_main *m, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (printf("%s", PROMPT), FAILURE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] && p_isdigit(argv[i][j]))
			++j;
		if (argv[i][j] != '\0')
			return (printf("%s", PROMPT), FAILURE);
		++i;
	}
	if (init_parameters(argc, argv, &m->param))
		return (printf("%s", PROMPT), FAILURE);
	return (SUCCESS);
}

double	sqrt_approx(double num)
{
	double	guess;
	t_uint	iter;

	if (num < 0)
		return (-1);
	iter = 6;
	guess = num / 2.0F;
	while (iter--)
	{
		guess = (guess + num / guess) / 2.0F;
	}
	return (guess);
}

t_uint	calc_delay(t_philosopher *philo)
{
	const int		id = philo->id;
	const double	p_amount = philo->param->p_amount;
	double			value;
	double			multiplier;

	multiplier = ((philo->param->time_to_eat + philo->param->time_to_sleep \
		+ (philo->param->time_to_die * 3)) / 10.0F) + 1.0F;
	value = ((sqrt_approx(p_amount) * sqrt_approx(multiplier)) * 5.0) + 100.0;
	return ((1 - id % 2) * (t_uint)(value));
}

t_uint	T_calc_delay(t_philosopher *philo)
{
	const int		id = philo->id;
	const double	p_amount = philo->param->p_amount;
	double			value;
	double			multiplier;

	multiplier = ((philo->param->time_to_eat + philo->param->time_to_sleep \
		+ (philo->param->time_to_die * 3)) / 10.0F) + 1.0F;
	value = ((sqrt_approx(p_amount) * sqrt_approx(multiplier)) * 5.0) + 100.0;
	return ((1 - id % 2) * (t_uint)(value));
}

int	main(int argc, char **argv)
{
	unsigned long	t_delay;
	unsigned long	t_inter;
	unsigned long	delay;
	unsigned long	inter;
	t_main			m;
	t_philosopher	philo1;
	t_philosopher	philo2;

	save_errno(0);
	if (check_input(&m, argc, argv))
		return (save_errno(RETURN_SAVED_ERRNO));
	philo1.param = &m.param;
	philo2.param = &m.param;
	philo1.id = 1;
	philo2.id = 2;
	printf("DELAY: [1] %d	[2] %d\n", calc_delay(&philo1), calc_delay(&philo2));//test
	printf("test DELAY: [1] %d	[2] %d\n", T_calc_delay(&philo1), T_calc_delay(&philo2));//test
	return (save_errno(RETURN_SAVED_ERRNO));
}
