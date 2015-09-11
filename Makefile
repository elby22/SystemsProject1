COMPILER = gcc
CCFLAGS  = -Wall -ansi -pedantic -g
all: tokenizer

tokenizer: tokenizer.o
	$(COMPILER) $(CCFLAGS) -o tokenizer tokenizer.o
tokenizer.o: tokenizer.c tokenizer.h
	$(COMPILER) $(CCFLAGS) -c tokenizer.c
clean:
	rm -f tokenizer tokenizer.o
