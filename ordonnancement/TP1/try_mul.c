#include<stdio.h>
#include "try.h"

static struct ctx_s ctx;

static int mul(int depth)
{
    int i;
        switch (scanf("%d", &i))
    {
      case EOF :
            return 1;
      case 0 :
            return mul(depth+1);
      case 1 :
        if (i)
            return i * mul(depth+1);
        else
            throw(&ctx,0);
    }
}


int main()
{
    int product;

    printf("la liste des registre\n");
    product = try(&ctx,mul,0);
    printf("product = %d\n", product);

    return 0;
}
