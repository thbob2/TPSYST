#include <pthread.h>

Int nbtours, tours; /* Variable globale du nombre de tours*/
Char choix2, choix1 ; /*variable des choix de chaque jouer*/

/* fonction executee par le thread du joueur 1*/
Void *thread_joueur1(void *k) {
	While (tours<=nbtours)
	{ while(x1==1) ;
		printf("joueur 1 : faites votre choix") ;
		Scanf("%s",&choix1) ;
		X1==0 ;
	} pthread_exit (NULL);
}

/* fonction executee par le thread du joueur 2*/
Void *thread_ joueur2 (void *k) {
	While (tours<=nbtours);
	{
		while(x2==1) ;
			printf(" joueur 2 : faites votre choix") ;
			Scanf("%s",&choix2) ;
			X2==0 ;
	} pthread_exit (NULL);
}

/* fonction executee par le thread de l’arbitre*/
Void *thread_ arbitre (void *k) {
	Int cpt1,cpt2,cpt ;
	While (tours<=nbtours);
	{while(x1==1) ;
		While(x2==1) ;
		/* Faire les comparaisons pour déterminer le nombre de points cpt1 et cpt2 */
		tours ++; x1=0 ;x2=0;
	} pthread_exit (NULL);
}

Int main() ;
{
	printf(" Donner le nombre de partie a jouer") ;
	Scanf("%d",&nbtours) ;
	pthread_t pth_id[3];
	if(pthread_create(pth_id, 0, thread_ joueur1, NULL) ){ perror("Erreur de creation du thread "); exit(EXIT_FAILURE); }
	if(pthread_create(pth_id+1, 0, thread_ joueur2, NULL)) { perror("Erreur de creation du thread "); exit(EXIT_FAILURE); }
	if(pthread_create(pth_id+2, 0, thread_ arbitre, NULL)) { perror("Erreur de creation du thread "); exit(EXIT_FAILURE); }
	if(pthread_join (pth_id+2, NULL)) perror("Erreur attente du thread ");
	printf("joueur 1 a totalisé :%d ",cpt1 ) ;
	printf("joueur 2 a totalisé :%d ",cpt2 ) ;
}
