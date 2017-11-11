#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED
#define MAGIC 0XDEADBEEF
#include<stdio.h>

typedef void (*func_t)(void *);

enum state {init,activable, term};

struct ctx_s
{
    void* ctx_esp;
    void* ctx_ebp;
    int ctx_magic;
    func_t f;
    void * arg;
    void * stack;
    enum state etat;
};

int init_ctx(struct ctx_s *pctx, int stack_size,func_t f, void * args);

int switch_to(struct ctx_s *pctx);

#endif // TRY_H_INCLUDED
