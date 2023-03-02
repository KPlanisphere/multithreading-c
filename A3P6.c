#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS

// La funcion que es utilizada en un hijo
// Debera de retornar un puntero sin tipo
void *ImprimeSaludo(void *threadid){
	long tid;
	// Aqui se castea lo que fue pasado
	// Al hilo como atributos
	tid = (long)threadid;
	printf("Hola esto se ejecuta en el hilo #%ld\n",tid);
	pthread_exit(NULL);
}

// ---Aqui finaliza la funcion que
// sera lamada en el hilo

int main (int argc, char *argv[]){
	pthread_t threads(NUM_THREADS);
	int rc;
	long t;
	for(t=0; t < NUM_THREADS; t++){
		printf("En Funcion main: creando el HIlo %ld\n",t);
		rc = pthread_create(&threads[t],NULL,ImprimeSaludo,(void *)t);
		if(rc){
			printf("ERROR: Return code from pthread_create() is &dn",rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
