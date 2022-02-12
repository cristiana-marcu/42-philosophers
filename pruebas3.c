/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:42:41 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/12 11:06:58 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/*
* En este documento vamos a ver cómo pasar argumentos a los hilos
* Entre el tiempo que el hilo se crea y se inicia, el valor que hemos  pasado
* ha cambiado.
*
*/

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg)
{
	sleep(1);
	int index = *(int*) arg;
	printf("%d ", primes[index]);
	free(arg);
}

int main(int argc, char **argv)
{
	pthread_t th[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread");
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread");
		}
	}
	return (0);
}
