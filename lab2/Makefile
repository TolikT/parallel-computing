CC=gcc
ICC=icc
CFLAGS=-std=gnu89 -Wall -Werror -Iinclude
LDFLAGS=-lm
PARFLAGS_GCC=-floop-parallelize-all -ftree-parallelize-loops=$(K)
PARFLAGS_ICC=-O0 -parallel -par-threshold=$(K)
SOURCE=lab2.c

lab_seq_c99: lab2.c
	$(CC) $(CFLAGS) -std=gnu99 $(SOURCE) $(LDFLAGS) -o lab1-seq -shared -fPIE -fPIC -O0

optimize: lab2.c
	$(CC) $(CFLAGS) -std=gnu99 -O$O $(SOURCE) $(LDFLAGS) -o lab1-seq-o$O

lab_seq_c89: lab2.c
	$(CC) $(CFLAGS) -std=gnu89 $(SOURCE) $(LDFLAGS) -o lab1-seq-c89

parallel: lab2.c
	$(CC) $(CFLAGS) $(PARFLAGS_GCC) $(SOURCE) -lm -o lab1-par-$K

parallel_icc: lab2.c
	$(ICC) $(PARFLAGS_ICC) -o lab1-icc-par-$K $(SOURCE)	

clean:
	rm -rf lab1-*
