hashset.o: hashset.c hashset.h
	gcc -c hashset.c
pt1.o: pt1.c hashset.h
	gcc -c pt1.c
pt1: hashset.o pt1.o
	gcc hashset.o pt1.o -o pt1

