/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: prova
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>


int counter = 0;
void trata_sinal(int sinal);

int main(){
    signal(SIGUSR1,trata_sinal);
    signal(SIGALRM,trata_sinal);
    
    while(1){
        pause();
    }

    return 0;
}

void trata_sinal(int sinal){
    if(sinal == SIGUSR1){
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    }else if(sinal == SIGALRM && counter != 2){
    	counter++;
        printf("Ai que sono, quero dormir mais um pouco\n");
    }else if(sinal == SIGALRM && counter == 2){
        printf("Os incomodados que se mudem, tchau\n");
        exit(0);
    }
}
