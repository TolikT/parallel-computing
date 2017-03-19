CC=gcc
CFLAGS=-std=gnu89 -Wall -Werror -fopenmp
ifneq ($(CHUNK),)
	CFLAGS += -DCHUNK=$(CHUNK)
endif
ifneq ($(SCHEDULE),)
	CFLAGS += -DSCHEDULE=$(SCHEDULE)
endif
LDFLAGS=-lm
SOURCE=lab3.c

seq: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS) -o lab3-$(CC)-$(SCHEDULE)-$(CHUNK)

clean:
	rm -rf lab3-*
