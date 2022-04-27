/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:27:30 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/27 19:15:54 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_common *common, long long time)
{
	long long	now;

	now = get_timestamp();
	while (!common->dead)
	{
		if (get_timestamp() - now >= time)
			break ;
		usleep(50);
	}
}

int	eat(t_philo *philo, t_common *common)
{
	pthread_mutex_lock(&common->fork[philo->l_fork]);
	print(FORK, philo->id, common);
	if (common->params[N_PHILOS] == 1)
		return (1);
	pthread_mutex_lock(&common->fork[philo->r_fork]);
	print(FORK, philo->id, common);
	pthread_mutex_lock(&common->access);
	print(EATING, philo->id, common);
	philo->last_meal_ms = get_timestamp();
	pthread_mutex_unlock(&common->access);
	sleeping(common, common->params[TIME_TO_EAT]);
	philo->ate += 1;
	pthread_mutex_unlock(&common->fork[philo->l_fork]);
	pthread_mutex_unlock(&common->fork[philo->r_fork]);
	return (0);
}

void	*routine(void *philosopher)
{
	t_common	*common;
	t_philo		*philo;
	int			ph;

	philo = (t_philo *)philosopher;
	common = philo->common;
	if (philo->id % 2 == 0)
		usleep(1000);
	ph = common->params[N_PHILOS];
	while (!common->dead)
	{
		if (eat(philo, common))
			break ;
		if (common->params[EAT_X_TIMES] == philo->ate || common->done)
			break ;
		print(SLEEPING, philo->id, common);
		sleeping(common, common->params[TIME_TO_SLEEP]);
		print(THINKING, philo->id, common);
	}
	return (NULL);
}
