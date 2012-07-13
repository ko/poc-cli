SRC_FILES = \
	cli.c \
	command.c

BINARY = clid

all: 
	gcc -o $(BINARY) $(SRC_FILES)
clean:
	rm $(BINARY)
