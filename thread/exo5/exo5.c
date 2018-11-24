#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 10
// the shared space will be a table of 10 elements for exemple
int T[MAX];
// our two semaphores empty and full 

sem_t empty,full,mutex;

void prod(){
	int j = 0;
	T[j%MAX] = rand()%MAX;
	printf("the producted value is %d\n",T[j]);
	j++;
}

void consume(){
	int i = 0;
	printf("consumed value is %d\n",T[i%MAX]);
	i++;
}

void* productor(void *k){
	
	for (int i = 0; i < MAX;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		prod();
		sem_post(&mutex);
		sem_post(&full);		
	}
}

void* consumer(void *k){
	
	for (int i = 0; i < MAX;i++){
		sem_wait(&full);
		sem_wait(&mutex);
		consume();
		sem_post(&mutex);
		sem_post(&empty);		
	}
}



int main(int argc, char const *argv[]){

	sem_init(&full,0,0);
	sem_init(&empty,0,MAX);
	sem_init(&mutex,0,1);
	
	pthread_t pro,cons;

	pthread_create(&pro,NULL,productor,NULL);
	pthread_create(&cons,NULL,consumer,NULL);

	if(pthread_join(pro,NULL))	perror("pthread_join");
	if(pthread_join(cons,NULL))	perror("pthread_join");

	sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

	return 0;
}