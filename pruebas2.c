/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:46:56 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/11 23:52:59 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *roll_dice()
{
	int value = (rand() % 6) + 1;
	printf("Value %d\n", value);
}

int main(int argc, char **argv)
{
	int *res;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		return 1;
	}
	if (pthread_join(th, (void**) &res) != 0)
	{
		return 2;
	}

	return (0);
}
