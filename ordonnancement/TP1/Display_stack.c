#include <stdio.h>

void display_adress(){

   void * esp;
   void * ebp;

   asm( "movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	:"=r" (esp)
	,"=r" (ebp));
}

 // ------------------la méthode main------------------------------

 int main(){
   void * esp;
   void * ebp;

        display_adress();
        printf( "ebp : %p\n", ebp );
        printf( "esp : %p\n", esp );

  return 0;
}
