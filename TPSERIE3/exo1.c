#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	/* code */
int tube[2];	
pipe( tube);

int pid1;

char b = 'c';
char string[31]="Bonjour fils je suis ton pêre!";
char strfils[31];

pid1= fork();
if(pid1==0){
	waitpid(getppid(),NULL,0);
	char bb ;
	close(tube[1]);
	read(tube[0],&strfils,sizeof(string));
	printf("%s\n",strfils);

}else
	{
	close(tube[0]);
	write(tube[1],&string,sizeof(string));
	//waitpid(pid1,NULL,0);
}

return 0;
}