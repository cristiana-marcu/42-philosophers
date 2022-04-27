/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:26:31 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/27 19:04:29 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_philo *philo, t_common *common, int i)
{
	philo->id = i + 1;
	philo->ate = 0;
	philo->died = false;
	philo->common = common;
	if (pthread_mutex_init(&common->fork[i], NULL))
		return (1);
	philo->l_fork = i;
	if (i == common->params[N_PHILOS] - 1)
		philo->r_fork = 0;
	else
		philo->r_fork = i + 1;
	philo->last_meal_ms = 0;
	return (0);
}

int	init_and_fill(t_common *common, t_philo **philos)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = *philos;
	common->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* common->params[N_PHILOS]);
	if (!common->fork)
		return (1);
	common->timestamp = 0;
	common->done = false;
	common->dead = false;
	if (pthread_mutex_init(&common->access, NULL)
		|| pthread_mutex_init(&common->print, NULL))
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * common->params[N_PHILOS]);
	if (!philo)
		return (1);
	while (++i < common->params[N_PHILOS])
		init_philo(&philo[i], common, i);
	*philos = philo;
	return (0);
}
