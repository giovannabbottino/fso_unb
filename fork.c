/*
* aluna: Giovanna Borges Bottino
* matricula: 170011267
* exercicio: codigo secreto
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void fazoqueopaifaz();
void fazoqueofilhofaz();

int main(void){
	pid_t p;
	p = fork();

	if(p>0) fazoqueopaifaz();
	else if(p==0) fazoqueofilhofaz();
	else printf("FORK falhou\n");

	sleep(50);
}

void fazoqueopaifaz(){
	printf("%d Sou o pai\n", getpid());
	sleep(5);
	exit(0);
}

void fazoqueofilhofaz(){
	printf("%d Sou o filho e o meu pai eh o %d\n", getpid(), getppid());
	sleep(10);
	printf("%d Sou o filho e o meu pai eh o %d\n", getpid(), getppid());

}
