/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: prova zombie
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

int counter = 0;
pid_t p;
void trata_sinal();

int main (){
    signal(SIGUSR1,trata_sinal);
    signal(SIGUSR2,trata_sinal);
    
    while(1){
        pause();
    }
    
    return 0;
}

void trata_sinal(){
    if(counter==0){
    	counter++;
        p = fork ();
        if (p==0){
            exit(0);
        }
    }else if(counter==1){
    	counter++;
        waitpid(-1, NULL, WNOHANG);
    }else{
        exit(0);
    }
}
