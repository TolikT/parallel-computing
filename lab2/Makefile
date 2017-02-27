CC=gcc
ICC=icc
CFLAGS=-Wall -Werror -Iinclude
LDFLAGS=-lm -LFW_1.3.1_Lin64/lib  -lfwBase -lfwImage -lfwJPEG -lfwSignal -lfwVideo
PARFLAGS_GCC=-floop-parallelize-all -ftree-parallelize-loops=$(K)
PARFLAGS_ICC=-O0 -parallel -par-threshold=$(K)
SOURCE=lab2.c

lab_seq_c99: lab2.c
	$(CC) $(CFLAGS) -std=gnu99 $(SOURCE) $(LDFLAGS) -O0 -o lab2-seq

optimize: lab2.c
	$(CC) $(CFLAGS) -std=gnu99 -O$O $(SOURCE) $(LDFLAGS) -o lab2-seq-o$O

lab_seq_c89: lab2.c
	$(CC) $(CFLAGS) -std=gnu89 $(SOURCE) $(LDFLAGS) -o lab2-seq-c89

parallel: lab2.c
	$(CC) $(CFLAGS) $(PARFLAGS_GCC) $(SOURCE) -lm -o lab2-par-$K

parallel_icc: lab2.c
	$(ICC) $(PARFLAGS_ICC) -o lab2-icc-par-$K $(SOURCE)	

clean:
	rm -rf lab2-*
