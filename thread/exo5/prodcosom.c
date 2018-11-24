#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#define SLOTS 10
#define MAX_PROD 4
#define MAX_CONS 4
 
pthread_mutex_t mutex; //allow access to buffer one thread at a time
sem_t empty; //block consumers from accessing buffer when buffer is empty
sem_t full; //block producers from accessing buffer when buffer is full
volatile int global = 0;
 
int buffer[SLOTS] = {0};//set to 0, no item available, else one item is available
 
 
int increment(int variable)
{
    return variable + 1;
}
 
int produire(){
    return (rand()% SLOTS)+1;
} 

void *produce(void* args)
{
    while(1){
        sem_wait(&empty); //producer must wait until one slot is empty
        //insertion
        for(size_t i = 0; i < SLOTS; i++){
            if(buffer[i] == 0){
                //lock global and buffer
                pthread_mutex_lock(&mutex);
                global = increment(global);
                buffer[i] = produire();
                printf("I added %d to the buffer\n",buffer[i]);
                
                pthread_mutex_unlock(&mutex);
                //unlock global and buffer
                //break;
            }
        }
        sleep(2);
        sem_post(&full); //consumer may eat something
    }
 
    pthread_exit(NULL);
}
 
void *consume(void* args)
{
     
    //extraction
    while(1){
 
        sem_wait(&full); //consumer must wait until producer added something
        for(size_t i = 0; i < SLOTS; i++){
             
            if(buffer[i] > 0){
                pthread_mutex_lock(&mutex);
                printf("I've just consumed %d \n", buffer[i]);
                buffer[i] = 0;
                pthread_mutex_unlock(&mutex);
                //break;
            }
        }
        sleep(2);
        sem_post(&empty); //producer may add something to the buffer
    }
 
    pthread_exit(NULL);
}
 
int main(int argc, char *argv[])
{
    //initalize semaphore for empty slots,
    //upon start up all slots are empty
    //producers may hence write in the buffer
 
    //initialize semaphore for full slots
    //upon start up the buffer is empty
    //consumer may therefore NOT extract data
    sem_init(&empty, 0, SLOTS);
    sem_init(&full, 0, 0);
 
    //init consumer thread
    //init producer thread
    pthread_t consumer[MAX_CONS], producer[MAX_PROD];
 
    for(size_t i = 0; i < MAX_CONS; i++){
        if(pthread_create(&consumer[i], NULL, consume, NULL)){
            perror("");
        }
    }
 
    for(size_t i = 0; i < MAX_PROD; i++){
        if(pthread_create(&producer[i], NULL, produce, NULL)){
            perror("");
        }
    }
 
    //wait until producer and consumer finishes their jobs
    for(size_t i = 0; i < MAX_CONS; i++){
        if(pthread_join(consumer[i], NULL)){
            perror("");
        }
    }
 
    for(size_t i = 0; i < MAX_PROD; i++){
        if(pthread_join(producer[i], NULL)){
            perror("");
        }
    }
 
    //destroy semaphores
    sem_destroy(&full);
    sem_destroy(&empty);
        
    
 
    return 0;
}