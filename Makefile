TARGET	= mpsh
CFLAGS	= -g -c -std=c99
LDFLAGS	=

all: mpsh

mpsh: pa1.o
	gcc $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.dSYM
