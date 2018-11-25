#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

// Déclarations des variables globales.
int or = 0;
int nbr_p = 0;
// Déclarations des sémaphores.
sem_t mine;
sem_t achat;
pthread_mutex_t caisse; //la caisse est un mutex vu que les mineurs ne peuvent diposer en meme temps

void * mineur () {
	int piocher = 0;

	sem_wait (&mine);
	nbr_p++;
	piocher = rand() % 1000;
	printf("Le nombre de mineurs en SC est : %d.\t ils ont piocher %d\n", nbr_p,piocher);
	nbr_p--;
	sem_post (&mine);

	// Accès à la caisse.
	pthread_mutex_lock(&caisse);
	or += piocher;
	pthread_mutex_unlock(&caisse);
}

void *achteur(){
	sem_wait(&achat);
	int poids = 0;
	poids = rand() % 500;
	//P(mutex)
	pthread_mutex_lock(&caisse);
	if (poids <= or){ 
		or -= poids;
		printf("acheteur achete %d\n",poids); 
		//V(mutex)
		pthread_mutex_unlock(&caisse);
		sem_post(&achat);
	}else{pthread_mutex_unlock(&caisse);}


}

int main () {
	time_t t = clock();
	srand(t);

	pthread_mutex_init(&caisse, NULL);
	sem_init (&mine, 0, 3); // pas plus de 3 mineur en mine 
	sem_init(&achat,0,1);

	printf("entrez le nombre de mineurs : "); 
	int nb_mineurs;
	scanf("%d", &nb_mineurs);
	pthread_t pth_mineurs[nb_mineurs];
	
	printf("entrez le nombre d'acheteurs : "); 
	int nb_achteurs;
	scanf("%d", &nb_achteurs);
	pthread_t pth_acheteur[nb_achteurs];
	int i, resultat;
	
	for (i = 0; i < nb_mineurs; i++)
	{
		resultat = pthread_create (&pth_mineurs[i], NULL, mineur, 0);
		if (resultat) printf ("ERROR; return code from pthread_join() is %d\n", resultat);
	}
	for (i = 0; i < nb_achteurs; i++)
	{
		resultat = pthread_create (&pth_acheteur[i], NULL, achteur, 0);
		if (resultat) printf ("ERROR; return code from pthread_join() is %d\n", resultat);
	}
	
	for (i = 0; i < nb_achteurs; i++)
	{
		pthread_join(pth_acheteur[i], NULL);
			
	}
	for (i = 0; i < nb_mineurs; i++)
	{
		pthread_join(pth_mineurs[i], NULL);
			
	}
	
	printf("Valeur de l'or retournée : %d grammes.\n", or);

	return 0;
}