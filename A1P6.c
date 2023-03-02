#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionThread(void *parametro);

int contador = 100;

main(){
	pthread_t iHilo;
	int error;
	int i;
	/*Pasamos atributos del nuevo thread NULL para que  los atrib
		por default
	Pasamos la funcion que se ejecutara en el nuevo hilo
	Pasamos NULL como parmaetro para esa funcion*/

	error = pthread_create(&iHilo,NULL,functionThread,NULL);

	if(error != 0){
		perror("No puedo crear thread");
		exit(-1);
 	}

	for(i=0;i<10;i++){
		contador++;
		printf("\nPadre: %d\n",contador);
		sleep(1);
	}
	exit(0);
}
	/* Funcion que se ejecuta en el thread hijo*/

void *functionThread(void *parametro){
	int i;
	/*Bucle infinito para decrementar contado y mostrarlo en pantalla*/
	for(i=0;i<10;i++){
		contador--;
		printf("\nHijo: %d\n", contador);
		sleep(1);
	}
	exit(0);
}
