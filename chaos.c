/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: Procurando pseudo-aleatorios modulados
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXRANDOM 100000

int somaglobal = 0;
int mi = 0;
sem_t semaforo;

struct args {
    int s;
	pthread_t thid;
    int v[MAXRANDOM];
    int bi;
};
void * verifica(void * arg);
void * calcula_perguntas(void * arg);

int main(void){
	int s1, s2;
	scanf(" %d", &s1);
    scanf(" %d", &s2);

    struct args *arg1 = (struct args *)malloc(sizeof(struct args));
	arg1->s = s1;

    struct args *arg2 = (struct args *)malloc(sizeof(struct args));
	arg2->s = s2;


    pthread_create(&arg1->thid, NULL, calcula_perguntas, (void*)arg1);
	pthread_create(&arg2->thid, NULL, calcula_perguntas, (void*)arg2);

    pthread_join(arg1->thid,NULL);
    pthread_join(arg2->thid,NULL);

	int bi;
    while(scanf("%d %d", &mi, &bi) != EOF ){
        if (mi == EOF || bi == EOF){
            break;
        }
        somaglobal = 0;
        sem_init(&semaforo, 0, 1);

        arg1->bi = bi;
        arg2->bi = bi;
        pthread_create(&arg1->thid, NULL, &verifica, (void*)arg1);
        pthread_create(&arg2->thid, NULL, &verifica, (void*)arg2);
        pthread_join(arg1->thid, NULL);
        pthread_join(arg2->thid, NULL);

        printf("%d\n",somaglobal);
    }

	return 0;
}

void * calcula_perguntas(void * arg)
{
    struct args * argumentos =(struct args*) arg;
    int s = (int ) argumentos->s;
    for(int i=0;i<MAXRANDOM;i++)
        argumentos->v[i]=rand_r(&s);

}

void * verifica(void * arg){
    struct args * argumentos =(struct args*) arg;
    for(int i = 0; i < MAXRANDOM; i++) {
        if(argumentos->v[i] % mi == argumentos->bi) {
            sem_wait(&semaforo);
                somaglobal++;
            sem_post(&semaforo);
        }
    }
}