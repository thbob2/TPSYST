#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/ipc.h>
#define MAX 10
#define MAX_PROD 4
#define MAX_CONS 4



// the shared space will be a table of 10 elements for exemple
int T[MAX] = {0};
int global;
// our two semaphores empty and full 

sem_t empty,full;
//sem_t mutex;
pthread_mutex_t mutex; //allow access to buffer one thread at a time

void prod(){
	if(T[global] == 0){
		
		T[global] = (rand()%MAX)+1;
		printf("the producted value is %d \n",T[global]);
		global++;
	}
}

void consume(int i){
	printf("consumed value is %d\n",T[i]);
	T[i]=0;
	}


void* productor(void *k){
	while(1){
		sem_wait(&empty);
		for (int i = 0; i < MAX;i++){
			
			pthread_mutex_lock(&mutex);
			prod();
			pthread_mutex_unlock(&mutex);
		}
		sleep(2);
		sem_post(&full);	
	}
	pthread_exit(NULL);
}

void* consumer(void *k){
	
	while(1){
		sem_wait(&full);
		
		for (int i = 0; i < MAX;i++){	
			if(T[i]>0){
				pthread_mutex_lock(&mutex);
				consume(i);
				pthread_mutex_unlock(&mutex);		
			}
		}
		sleep(2);
		sem_post(&empty);		
	}	
	pthread_exit(NULL);
}


int main(int argc, char const *argv[]){

	sem_init(&full,0,0);
	sem_init(&empty,0,MAX);
	//sem_init(&mutex,0,1);
	
	pthread_t pro[MAX_CONS],cons[MAX_PROD];
	for (int i = 0; i < MAX_PROD;i++){
		pthread_create(&pro[i],NULL,productor,NULL);
	}
	
	for (int i = 0; i < MAX_CONS;i++){
		pthread_create(&cons[i],NULL,consumer,NULL);
	}
	//wait until producer and consumer finishes their jobs
    for(int i = 0; i < MAX_CONS; i++){
        if(pthread_join(cons[i], NULL)){
            perror("pthread_join");
        }
    }
 
    for(int i = 0; i < MAX_PROD; i++){
        if(pthread_join(pro[i], NULL)){
            perror("pthread_join");
        }
    }
	sem_destroy(&full);
    sem_destroy(&empty);
    //sem_destroy(&mutex);
	return 0;
}