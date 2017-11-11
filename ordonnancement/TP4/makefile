
ROOTDIR=/home/fianso/M1S1/ASE/TP4/libhardware-linux-x86-r114

CFLAGS= -W -Wall -m32 -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib 

prodcons: prodcons.o sem.o
		gcc $(CFLAGS) -o prodcons prodcons.o sem.o $(LIBS)

sem.o: sem.c
	gcc $(CFLAGS) $(INCS) -o sem.o -c sem.c

prodcons.o: prodcons.c sem.h
	gcc $(CFLAGS) $(INCS) -o prodcons.o -c prodcons.c

.PHONY: clean realclean depend
	clean:
		$(RM) *.o
	realclean: clean
		$(RM) prodcons sem
