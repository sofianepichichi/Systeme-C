#include<stdio.h>
#include<assert.h>
#include "try.h"


int try(struct ctx_s * ctx, func_t *f, int arg) {

	ctx->ctx_magic = MAGIC;
	asm("movl %%esp, %0"
	"\n\t"
	"movl %%ebp, %1"
			:"=r" (ctx->ctx_esp)
			,"=r" (ctx->ctx_ebp));
	printf("esp : %p\n", ctx->ctx_esp);
	printf("ebp : %p\n", ctx->ctx_ebp);
	return f(arg);
}

int throw(struct ctx_s * pctx, int r) {

	assert(pctx->ctx_magic == MAGIC);

	int throw_val = r;
	asm("movl %0, %%esp"
	"\n\t"
	"movl %1, %%ebp"
      :
			:"r" (pctx->ctx_esp)
			,"r" (pctx->ctx_ebp));
	printf("esp : %p\n", pctx->ctx_esp);
	printf("ebp : %p\n", pctx->ctx_ebp);

	return throw_val;

}
