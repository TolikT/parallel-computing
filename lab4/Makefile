CC=gcc
SHELL=/bin/bash
CFLAGS=-std=gnu89 -Wall -Wno-unknown-pragmas
ifneq ($(CHUNK),)
	CFLAGS += -DCHUNK=$(CHUNK)
endif
ifneq ($(SCHEDULE),)
	CFLAGS += -DSCHEDULE=$(SCHEDULE)
endif

LDFLAGS=-lm 
SOURCE=lab4.c

seq: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS) -o lab4-$(CC)-$(SCHEDULE)-$(CHUNK)

clean:
	rm -rf lab4-*
