/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: vetores identicos
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * ordena(void * args);
int compara(const void * a, const void * b);
void * comparar(void *args);

int arr1[10000000];
int arr2[10000000];

struct args {
    int *arr;
    int tamanho;
	pthread_t thid;
};

struct compara_arg{
	int inicio;
	int fim;
	int resultado;
	pthread_t thid;
};

int main(void){
	int n, aux;
	scanf(" %d", &n);

	for (int i=0;i<n;i++){
        scanf(" %d", &arr1[i]);
    }
	for (int i=0;i<n;i++){
        scanf(" %d", &arr2[i]);
    }

	struct args *args1 = (struct args *)malloc(sizeof(struct args));
	args1->arr = arr1;
	args1->tamanho = n;

	struct args *args2 = (struct args *)malloc(sizeof(struct args));
	args2->arr = arr2;
	args2->tamanho = n;


	pthread_create(&args1->thid, NULL, ordena, (void*)args1);
	pthread_create(&args2->thid, NULL, ordena, (void*)args2);
	pthread_join(args1->thid, NULL);
	pthread_join(args2->thid, NULL);

	struct compara_arg tc1, tc2;
	tc1.inicio = 0;
	tc1.fim = n/2;
	tc2.inicio = n/2;
	tc2.fim = n;

	pthread_create(&tc1.thid,NULL,comparar,(void*)&tc1);
	pthread_create(&tc2.thid,NULL,comparar,(void*)&tc2);
	pthread_join(tc1.thid,NULL);
	pthread_join(tc2.thid,NULL);

	if(tc1.resultado == 1 && tc2.resultado == 1)
		printf("Mesmos elementos\n");
	else
		printf("Diferentes\n");

	return 0;
}

void * ordena(void * argumentos){
	struct args * arg =(struct args*) argumentos;
	qsort(arg->arr, arg->tamanho, sizeof(int), compara);
}

int compara(const void * a, const void * b){
	if(*(int*)a > *(int *) b) return 1;
	if(*(int*)a < *(int *) b) return -1;
	return 0;
}
void * comparar(void *argumentos){
	struct compara_arg *arg=(struct compara_arg*)argumentos;
	for (int i = arg->inicio; i < arg->fim; i++){
		if(arr1[i] != arr2[i]){
			arg->resultado = 0;
			return NULL;
		}
	}
	arg->resultado = 1;
}
