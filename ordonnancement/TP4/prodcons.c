#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "sem.h"
//#include"hardware.h"


#define N  100
typedef int objet_t;

struct sem_s *mutex, *vide, *plein;

void retirer_objet(objet_t obj){
  printf("1");
}
void mettre_objet(objet_t obj){
  printf("A");
}
void utiliser_objet(objet_t obj){
  printf("B");
}
void produire_objet(objet_t obj){
  printf("2");
}


void producteur (void){

  objet_t objet;
while (1) {
   produire_objet(&objet);
   sem_down(&vide);    /* decrémenter le nombre de places Libres*/
   sem_down(&mutex);
   mettre_objet(objet);
   sem_up(&mutex);
   sem_up(&plein);     /*incrémenter le Nb de place occupées*/
}
}

void consommateur (void){
  objet_t objet;

  while (1) {
    sem_down(&plein);  /*decrémenter le nombre de places occupéés*/
    sem_down(&mutex);
    retirer_objet(&objet);
    sem_up(&mutex);
    sem_up(&vide);
    utiliser_objet(objet);
  }
}


// la méthode main
int main(int argc, char const *argv[]) {

  sem_init(&mutex,1);
  sem_init(&vide,N);
  sem_init(&plein,0);

  create_ctx(16384,producteur,NULL);
  create_ctx(16384,consommateur,NULL);
  yield();

  exit(EXIT_SUCCESS);
}
