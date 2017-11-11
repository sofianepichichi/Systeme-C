CFLAGS= -W -Wall -m32 -g


ping_pong: ping_pong.o switch.o
		gcc $(CFLAGS) -o ping_pong ping_pong.o switch.o

switch.o: switch.c
	gcc $(CFLAGS) -o switch.o -c switch.c

ping_pong.o: ping_pong.c switch.h
	gcc $(CFLAGS) -o ping_pong.o -c ping_pong.c
