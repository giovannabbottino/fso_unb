/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: codigo secreto
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int counter = 0;
void trata_sinal(int sinal);

int main (void) {

    signal(SIGINT, trata_sinal);
    signal(SIGUSR2, trata_sinal);
    signal(SIGTERM, trata_sinal);
    signal(SIGUSR1, trata_sinal);

    while(1){
        pause();
    }
    return 0;
}

void trata_sinal(int sinal){
	printf("Recebi %d\n", sinal);
	if(counter == 0 && sinal == SIGINT)
        	counter++;
    	else if(counter == 1 && sinal == SIGUSR2)
        	counter++;
    	else if(counter ==2 && sinal == SIGTERM){
        	counter++;
        	printf("Senha acionada\n");
    	}else if(sinal == SIGINT)
        	counter = 1;	
        else if( counter == 3 && sinal == SIGUSR1){
        	printf("Tchau \n");
        	exit(0);
    	}else{
        counter = 0;
    	}
}

