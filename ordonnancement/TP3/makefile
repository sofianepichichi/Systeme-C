ROOTDIR=/home/fianso/M1S1/ASE/TP3/libhardware-linux-x86-r114

CFLAGS= -W -Wall -m32 -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

start_schedule: start_schedule.o create_ctx.o
	gcc $(CFLAGS) -o start_schedule start_schedule.o create_ctx.o $(LIBS)

ping_pong: ping_pong.o create_ctx.o
		gcc $(CFLAGS) $(LIBS) -o ping_pong ping_pong.o create_ctx.o

start_schedule.o: start_schedule.c hw_config.h create_ctx.h
		gcc $(CFLAGS) $(INCS) -o start_schedule.o -c start_schedule.c

create_ctx.o: create_ctx.c
	gcc $(CFLAGS) $(INCS) -o create_ctx.o -c create_ctx.c

ping_pong.o: ping_pong.c create_ctx.h hw_config.h
	gcc $(CFLAGS) $(INCS) -o ping_pong.o -c ping_pong.c

.PHONY: clean realclean depend
	clean:
		$(RM) *.o
	realclean: clean
		$(RM) start_schedule ping_pong create_ctx
