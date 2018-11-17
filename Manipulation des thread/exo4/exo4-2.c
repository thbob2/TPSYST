#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int nbtour=0,val1,val2;;
int cpt1 = 0,cpt2=0;; 
pthread_mutex_t m1,m2;

void* jou1 (void* name){
	int nb=0;
	printf("tour du joueur 1");
	while (nb<nbtour){
		pthread_mutex_lock(&m1); /* choix du premier joueur dans val1*/ pthread_mutex_unlock(&m1);
	}
 return NULL;
}

void* jou2 (void* name){
	printf("tour du joueur 2");
	int nb=0;
	while (nb<nbtour){
		pthread_mutex_lock(&m2); /* choix du premier joueur dans val1*/ pthread_mutex_unlock(&m2);
	}
 return NULL;
}

void* compte (void* k){
	int nb=0; printf("dans compte");
	while (nb<nbtour)
	{ nb ++;
		pthread_mutex_lock(&m1);
		pthread_mutex_lock(&m2);
		if ((val1=2) && (val2==1)) cpt2++;
		if ((val1=3) && (val2==1)) cpt2++;
		if ((val1=1) && (val2==2)) cpt1++;
		if ((val1=3) && (val2==2)) cpt2++;
		if ((val1=1) && (val2==3)) cpt1++;
		if ((val1=2) && (val2==3)) cpt1++;
		pthread_mutex_unlock(&m1);
		pthread_mutex_unlock(&m2);
	}
  return NULL;
}

int main (void){
	nbtour=3; pthread_t j1, j2,comp;
	pthread_mutex_init(&m1,NULL);
	pthread_mutex_init(&m2,NULL);
	if (pthread_create(&j1, NULL, jou1, NULL)) { perror("Erreur de creation du thread"); exit(EXIT_FAILURE); }
	if (pthread_create(&j2, NULL, jou2, NULL)) { perror("Erreur de creation du thread "); exit(EXIT_FAILURE); }
	if (pthread_create(&comp, NULL, compte, NULL)) { perror("Erreur de creation du thread "); exit(EXIT_FAILURE); }
	if (pthread_join(j1, NULL)) perror("pthread_join");
	if (pthread_join(j2, NULL)) perror("pthread_join");
	if (pthread_join(comp, NULL)) perror("pthread_join");
	printf("joueur 1 a totalisé :%d ",cpt1 ) ;
	printf("joueur 2 a totalisé :%d ",cpt2 ) ;
 return (EXIT_SUCCESS);
}