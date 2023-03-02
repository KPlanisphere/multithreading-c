#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionThread(void *parametro);

main(){
	pthread_t iHilo;
	pthread_attr_t atributos;
	int error;

	/* Valor que va a devolver el thread hijo*/
	char *valorDevuelto = NULL;

	/*Inicializamos los atributos con sus valores por defecto*/
	pthread_attr_init(&atributos);

	/*Aseguramos que el thread que vamos a poder esperar por el thread que * vamos a crear */

	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE);

	error = pthread_create(&iHilo,NULL,functionThread,NULL);

	/* COmprobamos el error al arrancar el thread*/
	if(error != 0){
		perror("No puedo crear thread");
		exit(-1);
 	}

	/*EL hilo principal espera al hilo hijo, indicado por pantalla cuando:
	* empieza la espera y cuando termina*/
	printf("Padre: Espero al thread\n");
	pthread_join(iHilo,(void **)&valorDevuelto);
	printf("Padre: Ya ha terminado el thread\n");

	/*Se saca en pantalla el valor devuelto*/
	printf("Padre: devuelve \"%s\"\n",valorDevuelto);
}

/* Funcion que se ejecuta en el thread hijo
 Espera un segundo y termina devolviendo la cadena de caracteres*/

void *functionThread(void *parametro){
	/*EL hijo espera un seugndo y sale, indicando cuando empieza a esperar y cuando termina*/
	sleep(1);
	printf("Hijo: Termino\n");

	/*Termina el thread y devuelve una cadena*/
	pthread_exit((void *)"Ya esta");
}

