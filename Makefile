main.o: main.c Pong.h EvolutiveSystem.h Extras.h
	gcc -c main.c

Pong.o: Pong.c Pong.h
	gcc -c Pong.c

EvolutiveSystem.o: EvolutiveSystem.c EvolutiveSystem.h
	gcc -c EvolutiveSystem.c

Extras.o: Extras.c Extras.h
	gcc -c Extras.c

allPrl: main.o Pong.o EvolutiveSystem.o Extras.o
	gcc -o EvolutivePong main.o Pong.o EvolutiveSystem.o Extras.o -lncurses -fopenmp

run: EvolutivePong
	./EvolutivePong
