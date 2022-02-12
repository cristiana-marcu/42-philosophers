/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:46:56 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/12 10:42:32 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/*
* En este archivo lo que queremos es devolver el valor de la función que se le
* pasa a la creación del hilo, al main.
*/

void *roll_dice()
{
	//No podemos devolver la referencia a una variable local porque será dealocada
	// del stack. Lo que queramos devolver lo tenemos que alocar dinámicamente
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	printf("Thread result: %p\n", result);
	printf("Value %d\n", value);
	return (void*) result;
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
	//El join recibe una referencia a un puntero y le cambia el valor a lo que
	// sea que haya en la función del hilo que le pasa al join
	if (pthread_join(th, (void**) &res) != 0)
	{
		return 2;
	}
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res); //Este free viene del malloc de roll_dice
	return (0);
}
