
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pthread.h>
//#include<time.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/ipc.h>
//#include<sys/sem.h>
#define Nb_tr 3

int a1 = 0, a2 =0;
sem_t s1,s2,s3,s4;

// votre solution est correcte ... vous pouvier initialisez &S3 a1 et &s4 a 1 et enlever le sem_post au debut de chaque joueur
//tres bien
void *anonce1 (void* k)
{
  int i;
  sem_post(&s3);
  for(i=0;i<Nb_tr;i++)
  {
      sem_wait(&s3);
      a1 = rand() % 3 + 1;

      if ( a1 == 1 ){ printf("joueur 1 anonce ciseau \n");}
      if ( a1 == 2 ){ printf("joueur 1 anonce pierre \n");}
      if ( a1 == 3 ){ printf("joueur 1 anonce feuille \n");}
      sem_post(&s1);

  }
}

void *anonce2 (void* k)
{

  int i;

  sem_post(&s4);
  for(i=0;i<Nb_tr;i++)
  {
sleep(3);
      sem_wait(&s4);
      a2 = rand() % 3 + 1;

      if ( a2 == 1 ){ printf("joueur 2 anonce ciseau \n");}
      if ( a2 == 2 ){ printf("joueur 2 anonce pierre \n");}
      if ( a2 == 3 ){ printf("joueur 2 anonce feuille \n");}
      sem_post(&s2);


  }
}
// 1 --> ciseau
// 2 --> pierre
// 3 --> feuille

void *arbitrer (void* k)
{
  int i, cpt1 = 0 ,cpt2 = 0;

  for(i=0;i<Nb_tr;i++)
  {

	sem_wait(&s1);
	sem_wait(&s2);
	if(a1 == a2)			{ printf("egalité rejouer un autre round \n");}

	if (a1 == 1 && a2 == 2)		{ printf("joueur 2 gagne le round %d \n",i);		cpt2++;}
	if (a1 == 2 && a2 == 1)		{ printf("joueur 1 gagne le round %d \n",i);		cpt1++;}

	if (a1 == 1 && a2 == 3)		{ printf("joueur 1 gagne le round %d \n",i);		cpt1++;}
	if (a1 == 3 && a2 == 1)		{ printf("joueur 2 gagne le round %d \n",i);		cpt2++;}

	if (a1 == 2 && a2 == 3)		{ printf("joueur 2 gagne le round %d \n",i);		cpt2++;}
	if (a1 == 3 && a2 == 2)		{ printf("joueur 1 gagne le round %d \n",i);		cpt1++;}

	sem_post(&s3);
	sem_post(&s4);
  }

	if (cpt1 == cpt2 && Nb_tr ==10) 	printf("partie nul %d a %d \n",cpt1,cpt2);
	if (cpt1 > cpt2 && Nb_tr ==10) 		printf("joueur 1 l'emporte avec %d point et joueur 2 a eu %d points \n",cpt1,cpt2);
	if (cpt1 < cpt2 && Nb_tr ==10) 		printf("joueur 2 l'emporte avec %d point et joueur 1 a eu %d points \n",cpt2,cpt1);

}

main()
{

  pthread_t id1,id2,idarb;

   //initialisation des semaphores
  sem_init(&s1,0,0);
  sem_init(&s2,0,0);
  sem_init(&s3,0,0);
  sem_init(&s4,0,0);
   //creation des thread
    pthread_create(&id1, 0, anonce1, NULL);
    pthread_create(&id2, 0, anonce2, NULL);
    pthread_create(&idarb, 0, arbitrer, NULL);


    // join pour attendre la terminaison des thread

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(idarb,NULL);

    //destruction des semaphre
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    sem_destroy(&s4);
    // les mutex protege la var partagé de lanonce mé n'assure pas l'execution mutuelle c pourkoi on va sorionté aux semaphore
   }
