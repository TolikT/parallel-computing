CC=gcc
ICC=icc
CFLAGS=-Wall -Werror
LDFLAGS=-lm
SOURCE=lab1.c

lab_seq_c99: lab1.c
	$(CC) $(CFLAGS) -std=gnu99 lab1.c $(LDFLAGS) -o lab1-seq

optimize: lab1.c
	$(CC) $(CFLAGS) -std=gnu99 -O$O lab1.c $(LDFLAGS) -o lab1-seq-o$O

lab_seq_c89: lab1.c
	$(CC) $(CFLAGS) -std=gnu89 lab1.c $(LDFLAGS) -o lab1-seq-c89

parallel: lab1.c
	$(CC) $(CFLAGS) -floop-parallelize-all -ftree-parallelize-loops=$K lab1.c -lm -o lab1-par-$K

parallel_icc: lab1.c
	$(ICC) -parallel -par-threshold=$K -o lab1-icc-par-$K lab1.c	

clean:
	rm -rf lab1-*
