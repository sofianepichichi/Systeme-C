#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "switch.h"

enum state etat;
struct ctx_s *ctx_courant = NULL;

int init_ctx(struct ctx_s *pctx, int stack_size,func_t f, void * arg){
  pctx -> ctx_magic = MAGIC;
  pctx -> f=f;
  pctx -> arg = arg;
  pctx ->stack = malloc(stack_size);
  assert(pctx -> stack != NULL);
  pctx -> ctx_esp = malloc(stack_size) + stack_size - sizeof(void*);
  pctx -> ctx_ebp = malloc(stack_size) + stack_size - sizeof(void*);
  etat = init;
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

	assert(ctx->ctx_magic == MAGIC);

	asm("movl %0, %%esp"nouv = (struct ctx_s *)malloc(sizeof(struct ctx_s));

	"\n\t"
	"movl %1, %%ebp"
      :
			:"r" (ctx->ctx_esp)
			,"r" (ctx->ctx_ebp));
	//printf("esp : %p\n", ctx_courant->ctx_esp);
	//printf("ebp : %p\n", ctx_courant->ctx_ebp);

  if(ctx_courant -> etat == init){
    ctx_courant -> etat = activable;
    ctx_courant -> f(ctx_courant -> arg);
    assert(0);
  }else if(ctx_courant -> etat == activable){
    return ;
  } else {
    assert(0); // cracher l'ordonnaceur et l'arreter
  }

}
