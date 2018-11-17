#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include <string.h>
#include <ctype.h>
#define max 100
int main(int argc, char const *argv[])
{
	/* code */
	int tube[2];	
	pipe( tube);

	int pid1;

	char b = 'c';
	char string[max];
	char strfils[max];

	pid1= fork();
	if(pid1==0){
	
		close(tube[1]);
		read(tube[0],&strfils,sizeof(string));
		int i =0;
		while(i<strlen(strfils)){
			if(isalpha(strfils[i])!=0){
			printf("%c",strfils[i]);
			i++;
			}else i++;

	}
		printf("%s",strfils);
	}else
	{
	gets(string);
	printf("%s\n",string );
	close(tube[0]);
	write(tube[1],&string,sizeof(string));
	//waitpid(pid1,NULL,0);
}

return 0;
}
