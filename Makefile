TARGET	= mpsh
CFLAGS	= -g -c -D_POSIX_C_SOURCE
CFLAGS += -std=c99 -Wimplicit-function-declaration -Werror
CFLAGS += # Add your own cflags here
LDFLAGS	=

all: mpsh toy

mpsh: pa1.o parser.o
	gcc $(LDFLAGS) $^ -o $@

toy: toy.o
	gcc $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) toy *.o *.dSYM
