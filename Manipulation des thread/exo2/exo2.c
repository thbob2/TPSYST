#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *c; /* variable global du caractere*/
int x=0;
//fonction du thread du lecture
void *thread_read(void *k){
	while(c!='f' || c!='F');
		{
			while(x!=0)// attente du la l ecriture du caractere 
			{printf("donnez caractere a transférer\n");
			scanf("%c",&c);
			x=1;
		}
	}
		pthread_exit(NULL);

}

void *thread_write(void *k){
while(c!='f' || c!='F');
		{
			while(x!=1){ // attente du la lecture du caractere 
			printf("\nle caractere transferé est %s\n",c);
			x=0;
		}
	}
		pthread_exit(NULL);

}


int main(int argc, char const *argv[])
{	pthread_t pth_id[2];
	if(pthread_create(pth_id,0,thread_write,NULL)){ perror("Erreur de la creation du thread"); exit(EXIT_FAILURE);}
	if(pthread_create(pth_id+1,0,thread_read,NULL)){ perror("Erreur de la creation du thread"); exit(EXIT_FAILURE);}
	if(pthread_join(pth_id,NULL)) perror("erreur d'attente du thread");
	if(pthread_join(pth_id+1,NULL)) perror("erreur d'attente du thread");
	return 0;
}