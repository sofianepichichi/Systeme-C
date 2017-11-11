#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "create_ctx.h"
#include "hw_config.h"
#include "hardware.h"

enum state etat;
struct ctx_s *ctxs = NULL;
struct ctx_s *ctx_courant = NULL;

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
  struct ctx_s *ctx_term = NULL;

  if(ctx_courant != NULL){
    while(ctx_courant -> suivant -> etat == term){
      _mask(15);
      ctx_term = ctx_courant -> suivant;
      assert(ctx_courant != ctx_courant -> suivant);
      ctx_courant -> suivant = ctx_courant -> suivant -> suivant ;
      free(ctx_term -> stack);
      free(ctx_term);
    }
    switch_to(ctx_courant -> suivant);
    }else {
      assert(ctxs != NULL);
      switch_to(ctxs);
    }
    _mask(1);
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

  asm("movl %0, %%esp"
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
    ctx_courant -> etat == term;
    yield();
  }


}
