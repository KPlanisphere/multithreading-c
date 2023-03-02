# Multithreading in C

## Description
This project contains a series of C programs that demonstrate various aspects of multithreading using the pthread library. These programs illustrate the creation and management of threads, synchronization between threads, and passing parameters to threads. Each file showcases different aspects of multithreading, providing a comprehensive overview of how to use pthreads in C.

### Key Features
- **Thread Creation**: Examples of creating new threads using the `pthread_create` function.
- **Thread Synchronization**: Demonstrations of using `pthread_join` to synchronize threads.
- **Thread Parameters**: Usage of passing parameters to threads and handling return values.
- **Thread Execution**: Examples of executing functions within threads and managing thread lifecycle.

### Files
1. **A1P6.c**
    - Demonstrates the creation of a thread and concurrent execution of a function in the main thread and the child thread.
    - **Key Code Snippet**:
        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <pthread.h>

        void *functionThread(void *parametro);

        int contador = 100;

        int main(){
            pthread_t iHilo;
            int error;
            int i;

            error = pthread_create(&iHilo, NULL, functionThread, NULL);
            if (error != 0){
                perror("No puedo crear thread");
                exit(-1);
            }

            for(i = 0; i < 10; i++){
                contador++;
                printf("\nPadre: %d\n", contador);
                sleep(1);
            }
            exit(0);
        }

        void *functionThread(void *parametro){
            int i;
            for(i = 0; i < 10; i++){
                contador--;
                printf("\nHijo: %d\n", contador);
                sleep(1);
            }
            exit(0);
        }
        ```
        This code creates a new thread that runs concurrently with the main thread, modifying a shared variable.

2. **A2P6.c**
    - Illustrates the use of `pthread_join` to wait for a thread to finish and handle the returned value.
    - **Key Code Snippet**:
        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <pthread.h>

        void *functionThread(void *parametro);

        int main(){
            pthread_t iHilo;
            pthread_attr_t atributos;
            int error;
            char *valorDevuelto = NULL;

            pthread_attr_init(&atributos);
            pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

            error = pthread_create(&iHilo, &atributos, functionThread, NULL);
            if (error != 0){
                perror("No puedo crear thread");
                exit(-1);
            }

            printf("Padre: Espero al thread\n");
            pthread_join(iHilo, (void **)&valorDevuelto);
            printf("Padre: Ya ha terminado el thread\n");
            printf("Padre: devuelve \"%s\"\n", valorDevuelto);
        }

        void *functionThread(void *parametro){
            sleep(1);
            printf("Hijo: Termino\n");
            pthread_exit((void *)"Ya esta");
        }
        ```
        This code creates a thread and waits for it to finish, demonstrating synchronization between the main thread and the child thread.

3. **A3P6.c**
    - Demonstrates the creation of multiple threads and passing parameters to them.
    - **Key Code Snippet**:
        ```c
        #include <pthread.h>
        #include <stdio.h>
        #include <stdlib.h>
        #define NUM_THREADS 5

        void *ImprimeSaludo(void *threadid){
            long tid;
            tid = (long)threadid;
            printf("Hola esto se ejecuta en el hilo #%ld\n", tid);
            pthread_exit(NULL);
        }

        int main(int argc, char *argv[]){
            pthread_t threads[NUM_THREADS];
            int rc;
            long t;
            for(t = 0; t < NUM_THREADS; t++){
                printf("En Funcion main: creando el Hilo %ld\n", t);
                rc = pthread_create(&threads[t], NULL, ImprimeSaludo, (void *)t);
                if(rc){
                    printf("ERROR: Return code from pthread_create() is %d\n", rc);
                    exit(-1);
                }
            }
            pthread_exit(NULL);
        }
        ```
        This code creates multiple threads, each executing a function that prints a message along with its thread ID.

## How to Use
1. **Compilation**: Each C file can be compiled using a C compiler such as `gcc` with the `-pthread` flag to link the pthread library.
    ```bash
    gcc A1P6.c -o A1P6 -pthread
    gcc A2P6.c -o A2P6 -pthread
    gcc A3P6.c -o A3P6 -pthread
    ```

2. **Execution**: Run the compiled programs to see the output of multithreading operations.
    ```bash
    ./A1P6
    ./A2P6
    ./A3P6
    ```
