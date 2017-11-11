#include<stdio.h>
#include<stdlib.h>
#include "drive.h"
#include "hardware.h"
#include "hw_config.h"

static void
empty_it(void)
{
  return;
}
static void
timer_it() {
    static int tick = 0;
    fprintf(stderr, "hello from IT %d\n", ++tick);
    _out(TIMER_ALARM,0xFFFFFFFE);
}

int main()
{
  unsigned int i;
  unsigned char *buf = malloc(sizeof(unsigned char)*HDA_SECTORSIZE);

    /* init hardware */
    if (init_hardware(HARDWARE_INI) == 0) {
	fprintf(stderr, "Error in hardware initialization\n");
	exit(EXIT_FAILURE);
    }

    /* dummy interrupt handlers */
    for (i=0; i<14; i++)

	IRQVECTOR[i] = empty_it;

    /* program timer */

    IRQVECTOR[TIMER_IRQ] = timer_it ;
    _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
    _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */
    read_sector(0,0,buf);
    for(int k=0; k<HDA_SECTORSIZE;k++){
      printf("%02x ",buf[k]);
    }
   /* allows all IT */
    _mask(1);

    /* count for a while... */
    for (i=0; i<(1<<28); i++)
	;

  exit(EXIT_SUCCESS);
}
