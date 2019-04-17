FILES = execute.o main.o parse.o utils.o

all: $(FILES)
	gcc $(FILES) -o nilsh

execute.o: execute.c
	gcc -c execute.c

main.o: main.c
	gcc -c main.c

parse.o: parse.c
	gcc -c parse.c

utils.o: utils.c
	gcc -c utils.c

clean:
	rm *.o
