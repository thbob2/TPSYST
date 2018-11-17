#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/ipc.h>


int j=0 , j2=0;

sem_t s4,s1,s2,s3;

void *joue1 (void* k)
{

  //sem_post(&s3);
  //sem_wait(&s3);
  srand(time(NULL));
  j = rand() % 3 + 1;

      if ( j == 1 ){ printf("joueur 1 a choisie ciseau \n");}
      if ( j == 2 ){ printf("joueur 1 a choisie pierre \n");}
      if ( j == 3 ){ printf("joueur 1 a choisie feuille \n");}

  sem_post(&s1);

}

void *joue2 (void* k)
{

  sem_post(&s3);
      sem_wait(&s3);
      srand(time(NULL));
      j2 = rand() % 3 + 1;

      if ( j2 == 1 ){ printf("joueur 2 a choisie ciseau \n");}
      if ( j2 == 2 ){ printf("joueur 2 a choisie pierre \n");}
      if ( j2 == 3 ){ printf("joueur 2 a choisie feuille \n");}
      sem_post(&s2);
}

void *arbitrer (void* k)
{
	sem_wait(&s3);
	//sem_wait(&s2);
	if(j == j2)			{ printf("égalité. \n");}

	if (j == 1 && j2 == 2)		{ printf("joueur 2 gagne. \n");}
	if (j == 2 && j2 == 1)		{ printf("joueur 1 gagne. \n");}

	if (j == 1 && j2 == 3)		{ printf("joueur 1 gagne. \n");}
	if (j == 3 && j2 == 1)		{ printf("joueur 2 gagne. \n");}

	if (j == 2 && j2 == 3)		{ printf("joueur 2 gagne. \n");}
	if (j == 3 && j2 == 2)		{ printf("joueur 1 gagne. \n");}

	sem_post(&s1);
	sem_post(&s2);
 }


main()
{
	pthread_t id1,id2,idarb;

   //initialisation des semaphores
  	sem_init(&s1,0,0);
  	sem_init(&s2,0,0);
  	sem_init(&s3,0,0);
  	//sem_init(&s4,0,0);
    //creation des thread
    pthread_create(&id1, 0, joue1, NULL);
    pthread_create(&id2, 0, joue2, NULL);
    pthread_create(&idarb, 0, arbitrer, NULL);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(idarb,NULL);

    //destruction des sémaphore
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    //sem_destroy(&s4);

}