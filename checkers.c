/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:25:19 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/27 18:49:35 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args_fill_common(t_common *common, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	common->params = (int *)malloc(sizeof(int) * argc);
	if (!common->params)
		return (1);
	if (argc == 5)
		common->params[EAT_X_TIMES] = -1;
	i = 1;
	while (argv[i])
	{
		common->params[i - 1] = ft_atoi(argv[i]);
		if (common->params[i - 1] <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_done(t_philo *philo, t_common *common)
{
	int	i;
	int	ph;
	int	n_eat;

	i = 0;
	ph = common->params[N_PHILOS];
	n_eat = common->params[EAT_X_TIMES];
	while (n_eat > 0 && i < ph && philo[i].ate >= n_eat)
		i++;
	if (i == ph)
		common->done = true;
}

void	check_death(t_philo *philo)
{
	int			i;
	t_common	*common;

	common = philo->common;
	while (!common->done)
	{
		i = 0;
		while (!common->dead && i < common->params[N_PHILOS])
		{
			pthread_mutex_lock(&common->access);
			if (get_timestamp() - philo[i].last_meal_ms
				>= common->params[TIME_TO_DIE])
			{
				print(DIED, philo[i].id, common);
				common->dead = true;
			}
			pthread_mutex_unlock(&common->access);
			usleep(100);
			i++;
		}
		if (common->dead)
			break ;
		check_done(philo, common);
	}
}
