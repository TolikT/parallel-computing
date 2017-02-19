CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-lm
SOURCE=lab1.c

lab_seq_c99: lab1.c
	$(CC) $(CFLAGS) -std=gnu99 lab1.c $(LDFLAGS) -o lab1-seq

lab_seq_c89: lab1.c
	$(CC) $(CFLAGS) -std=gnu89 lab1.c $(LDFLAGS) -o lab1-seq

parallelize: lab1.c
	$(CC) $(CFLAGS) -floop-parallelize-all -ftree-parallelize-loops=$K lab1.c -lm -o lab1-par-$K

clean:
	rm -rf lab1 lab1-par-*
