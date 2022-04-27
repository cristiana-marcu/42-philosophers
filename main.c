/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:56:54 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/27 17:45:22 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo(t_philo *philo)
{
	int	i;
	int	ph;

	i = 0;
	philo->common->timestamp = get_timestamp();
	ph = philo->common->params[N_PHILOS];
	while (i < ph)
	{
		if (pthread_create(&(philo[i].thread), NULL,
				&routine, &(philo[i])))
			return (1);
		philo[i].last_meal_ms = get_timestamp();
		i++;
	}
	check_death(philo);
	return (0);
}

int	joiner(t_common *common, t_philo *philo)
{
	int	i;
	int	ph;

	i = 0;
	ph = common->params[N_PHILOS];
	while (i < ph && ph > 0)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (1);
		pthread_mutex_destroy(&common->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&common->access);
	pthread_mutex_destroy(&common->print);
	free(common->fork);
	free(philo);
	free(common->params);
	return (0);
}

int	main(int argc, char **argv)
{
	t_common	common;
	t_philo		*philos;

	if (check_args_fill_common(&common, argc, argv))
		return (print_error("Arguments not valid"));
	if (init_and_fill(&common, &philos))
		return (print_error("Error initializing threads"));
	if (philo(philos))
		return (print_error("No more than one threat created"));
	if (joiner(&common, philos))
		return (print_error("Couldn't join properly"));
	return (0);
}
