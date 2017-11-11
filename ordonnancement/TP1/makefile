CFLAGS= -W -Wall -m32 -g

try_mul: try_mul.o try.o
		gcc $(CFLAGS) -o try_mul try_mul.o try.o

try.o: try.c
	gcc $(CFLAGS) -o try.o -c try.c

try_mul.o: try_mul.c try.h
	gcc $(CFLAGS) -o try_mul.o -c try_mul.c
