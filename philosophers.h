/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:08:43 by cmarcu            #+#    #+#             */
/*   Updated: 2022/04/27 19:15:04 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define N_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define EAT_X_TIMES 4
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define FORK "has taken a fork"

typedef struct s_common
{
	int				*params;
	pthread_mutex_t	*fork;
	pthread_mutex_t	access;
	pthread_mutex_t	print;
	bool			done;
	bool			dead;
	long long		timestamp;
}	t_common;

typedef struct s_philo
{
	int			id;
	int			ate;
	bool		died;
	t_common	*common;
	int			l_fork;
	int			r_fork;
	long long	last_meal_ms;
	pthread_t	thread;
}	t_philo;

int			check_args_fill_common(t_common *common, int argc, char **argv);
void		check_done(t_philo *philo, t_common *common);
void		check_death(t_philo *philo);

int			init_and_fill(t_common *common, t_philo **philos);
int			init_philo(t_philo *philo, t_common *common, int i);

void		sleeping(t_common *common, long long time);
void		*routine(void *philosopher);
int			eat(t_philo *philo, t_common *common);
int			joiner(t_common *common, t_philo *philo);
int			philo(t_philo *philo);

int			ft_atoi(const char *str);
void		print(char *msg, int philo_id, t_common *common);
long long	get_timestamp(void);
int			print_error(char *msg);

#endif
