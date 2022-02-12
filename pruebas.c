/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:03:53 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/12 13:17:13 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/*
* Cositas importantes: los hilos ccomparten memoria (al contrario que los procesos)
* Por lo tanto es delicado que haya varios hilos intentando cambiar la misma
* porción de memoria (véase el valor de una variable)
*
* Podemos compilar gcc -S main.c y en main.s tendremos el código en emsamblador
* Probablemente tenga en un array de pthread_t philos[n] donde n me lo han pasado
*
* Para que nuestro programa sea realmente multihilo no podemos crear y esperar
* con join a que acabe un hilo en el mismo bucle, porque nunca habrá más de
* un hilo corriendo a la vez
*
* Para compilar: gcc -g -pthread pruebas.c && ./a.out
* Para limpiar hilos podemos hacer sanitize=threads
*
* Los filósofos no pueden coger los dos tenedores a la vez: primero cogen uno
* y luego mira si puede o no coger el otro. Si no puede, deja el que ya cogió.
*
* MUTEX viene de MUTual EXclusion y permite sincronizar el uso de un recurso
* compartido entre hilos, véase un tenedor :)
*
*
*
*/
int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int main (int argc, char **argv)
{
	pthread_t th[4]; //thread 1
	pthread_mutex_init(&mutex, NULL);
	int i = 0;
	//Orden de parámetros: Hilo, configuracion, puntero a funcion, argumentos que le pasarías a la función puntero
	for (i = 0; i < 4; i++) //Bucle que crea tantos hilos como queramos (philos)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			return 1;
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++) //Bucle que espera a los hilos a terminar
	{
		if (pthread_join(th[i], NULL) != 0)//El null sería el valor de retorno del proceso de join
		{
			return 2; //pthread_join espera al hilo especificado a terminar
		}
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}
