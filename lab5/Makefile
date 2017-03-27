MAKEFLAGS += --no-print-directory
CC=gcc
SHELL=/bin/bash
CFLAGS=-std=gnu89 -Wall -Wno-unknown-pragmas -fopenmp
ifneq ($(CHUNK),)
	CFLAGS += -DCHUNK=$(CHUNK)
endif
ifneq ($(SCHEDULE),)
	CFLAGS += -DSCHEDULE=$(SCHEDULE)
endif

LDFLAGS=-lm 
SOURCE=lab5.c

seq: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS) -o lab4-$(CC)-$(SCHEDULE)-$(CHUNK)

clean:
	rm -rf lab5-*
