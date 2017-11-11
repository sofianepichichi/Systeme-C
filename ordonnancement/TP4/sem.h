#ifndef SEM_H_INCLUDED
#define SEM_H_INCLUDED
#include<stdio.h>
#define MAGIC 0XDEADBEEF


typedef void (*func_t)(void *);

enum state {init,active, terminer,bloque};
struct sem_s
{
  int compteur;
  struct ctx_s *ctx_bloques;
  int magic;
};
struct ctx_s
{
    void* ctx_esp;
    void* ctx_ebp;
    int ctx_magic;
    func_t f;
    void * arg;
    void * stack;
    enum state etat;
   struct ctx_s *suivant;
   struct ctx_s *sem_suivant;
};
void sem_init(struct sem_s *sem,unsigned int cpt);
void sem_down(struct sem_s *sem);
void sem_up(struct sem_s *sem);
int create_ctx(int stack_size,func_t f, void * args);

int switch_to(struct ctx_s *pctx);
void yield();

#endif
