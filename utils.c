/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:23:54 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/27 17:59:42 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

long long	get_timestamp(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	print(char *msg, int philo_id, t_common *common)
{
	pthread_mutex_lock(&common->print);
	if (!common->dead)
		printf("%lli ms %i %s\n", get_timestamp() - common->timestamp,
			philo_id, msg);
	pthread_mutex_unlock(&common->print);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	number;
	int	is_neg;

	a = 0;
	is_neg = 1;
	number = 0;
	while (str[a] == '\t' || str[a] == '\n' || str[a] == '\v'
		|| str[a] == '\f' || str[a] == '\r' || str[a] == ' ')
		a++;
	if (str[a] == '-')
	{
		is_neg = -1;
		a++;
	}
	else if (str[a] == '+')
		a++;
	while (str[a] != '\0' && str[a] >= '0' && str[a] <= '9')
	{
		number = number * 10 + (str[a] - '0');
		a++;
	}
	return ((int)number * is_neg);
}
