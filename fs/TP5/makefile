ROOTDIR=/home/enseign/ASE

CFLAGS= -W -Wall -m32 -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

all : dmps frmt
dmps: dmps.o drive.o
		gcc $(CFLAGS) -o dmps dmps.o drive.o $(LIBS)

frmt: frmt.o drive.o
				gcc $(CFLAGS) -o frmt frmt.o drive.o $(LIBS)

drive.o: drive.c
	gcc $(CFLAGS) $(INCS) -o drive.o -c drive.c

dmps.o: dmps.c drive.h
	gcc $(CFLAGS) $(INCS) -o dmps.o -c dmps.c

frmt.o: frmt.c drive.h
		gcc $(CFLAGS) $(INCS) -o frmt.o -c frmt.c

.PHONY: clean realclean depend

clean:
		$(RM) *.o
realclean: clean
		$(RM) dmps frmt drive vdiskA.bin vdiskB.bin
