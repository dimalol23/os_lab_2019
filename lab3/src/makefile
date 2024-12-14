CC=gcc
FLAGS=-I

all: sequential_min_max find_min_max parallel_min_max utils code

code: code.c 
	gcc -c code.c
sequential_min_max: sequential_min_max.c find_min_max.h utils.h 
	gcc -c sequential_min_max.c 

sequential_min_max.o:
	gcc -c sequential_min_max.c

find_min_max: find_min_max.c find_min_max.h 
	gcc -c find_min_max.c 

find_min_max.o:
	gcc -c find_min_max.c

parallel_min_max: parallel_min_max.c find_min_max.h utils.h
	gcc -c parallel_min_max.c

parallel_min_max.o: 
	gcc -c parallel_min_max.c 

utils: utils.h
	gcc -c utils.h
