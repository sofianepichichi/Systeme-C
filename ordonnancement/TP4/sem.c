#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"sem.h"
//#include "hw_config.h"
#include "hardware.h"

enum state etat;
struct ctx_s *ctxs = NULL;
struct ctx_s *ctx_courant = NULL;
struct ctx_s *ctx_bloques = NULL;
struct sem_s *sem_suivant = NULL;
int compteur;


void sem_init(struct sem_s *sem, unsigned int cpt){
  sem -> compteur = cpt;
  sem -> ctx_bloques = NULL;
  sem -> magic = MAGIC;
}


void sem_down(struct sem_s *sem){

//_mask(15);
//assert(sem->magic == MAGIC);
sem->compteur--;
    if(sem->compteur<=0){
      ctx_courant->etat== bloque;
      ctx_courant->sem_suivant=sem->ctx_bloques;
      sem->ctx_bloques=ctx_courant;
      yield();
    }
    //_mask(1);
}

void sem_up(struct sem_s *sem){
//_mask(15);
//assert(sem->magic == MAGIC);
sem->compteur++;
     if(sem->compteur<=0){
       //assert(sem->ctx_bloques!=NULL);
       //assert(sem->ctx_bloques->etat=bloque);
       sem->ctx_bloques->etat == active;
       sem->ctx_bloques=sem->ctx_bloques->sem_suivant;
     }
//_mask(1);
}

int create_ctx( int stack_size,func_t f, void * arg){

struct ctx_s *nouveau_ctx = NULL;
nouveau_ctx = (struct ctx_s *)malloc(sizeof(struct ctx_s));

assert(nouveau_ctx != NULL);
nouveau_ctx -> ctx_magic = MAGIC;
nouveau_ctx -> f=f;
nouveau_ctx -> arg = arg;
nouveau_ctx ->stack = malloc(stack_size);
assert(nouveau_ctx -> stack != NULL);
nouveau_ctx -> ctx_esp = nouveau_ctx -> stack + stack_size - sizeof(void*);
nouveau_ctx -> ctx_ebp = nouveau_ctx -> stack + stack_size - sizeof(void*);
nouveau_ctx -> etat = init;

if(ctxs == NULL){
  ctxs = nouveau_ctx;
  ctxs -> suivant = ctxs;
}else{
  nouveau_ctx -> suivant = ctxs -> suivant;
  ctxs -> suivant = nouveau_ctx;
}
}


void yield(){
struct ctx_s *ctx_terminer = NULL;
struct ctx_s *ctx_suivant  = NULL;

if(ctx_courant != NULL){
    ctx_suivant = ctx_courant -> suivant;
    while(ctx_suivant -> etat == terminer || etat == bloque){
      assert(ctx_suivant != ctx_courant);

      if(ctx_suivant -> etat == terminer){
        free(ctx_terminer -> stack);
        free(ctx_terminer);
      ctx_suivant = ctx_suivant -> suivant ;
      }else{
        ctx_suivant= ctx_suivant -> suivant ;
      }
 }


 switch_to(ctx_courant -> suivant);
     }else {
       assert(ctxs != NULL);
       switch_to(ctxs);
     }
 }


 int switch_to(struct ctx_s * ctx) {

   if(ctx_courant !=NULL ){
     asm("movl %%esp, %0"
     "\n\t"
     "movl %%ebp, %1"
         :"=r" (ctx_courant->ctx_esp)
         ,"=r" (ctx_courant->ctx_ebp));
     //printf("esp : %p\n", ctx->ctx_esp);
     //printf("ebp : %p\n", ctx->ctx_ebp);
   }

   ctx_courant = ctx;

   //assert(ctx->ctx_magic == MAGIC);

   asm("movl %0, %%esp"
   "\n\t"
   "movl %1, %%ebp"
       :
       :"r" (ctx->ctx_esp)
       ,"r" (ctx->ctx_ebp));
   //printf("esp : %p\n", ctx_courant->ctx_esp);
   //printf("ebp : %p\n", ctx_courant->ctx_ebp);

   if(ctx_courant -> etat == init){
     ctx_courant -> etat = active;
     ctx_courant -> f(ctx_courant -> arg);
  //   assert(0);
   }else if(ctx_courant -> etat == active){
     return ;
   } else {
     ctx_courant -> etat == terminer;
     yield();
   }
 }
