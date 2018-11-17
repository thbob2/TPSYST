#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long compteur[3];

/*fonction executée par chaque thread */

void* fonc_thread(void *k){
	long j;
	j=(long)k;
	printf("Thread numero %ld : mon tidest %ld\n",j,pthread_self());
	for (;;)
	{
		compteur[j]++;
	}
}

	int main(int argc, char const *argv[])
	{
		long i,num;
		pthread_t pth_id[3];

		//creation des threads

		for (num = 0; num < 3; num++)
		{
			pthread_create(&pth_id[num],0,fonc_thread,(void *) num);
			printf("Main: thread numero %ldcreee :id = %ld\n",num,pth_id[num]);
		}
		sleep(1);
		printf("Affichage des compteurs (20 fois)\n");
		for (i = 0; i < 20; i++)
		{
			printf("%ld \t%ld \t%ld\n",compteur[0],compteur[1],compteur[2]);
			sleep(1);

		}
		exit(0);
	}