KEY_FOR_CREATOR_COND=-DINITAL
KEY_FOR_MEMORY=--leak-check=full
KEY_FOR_MAIN=-DCOUNT_TRANZAKTS_SIMULATION=10

main: gpss
	

gpss: main.cpp Simulation.h creator_conditional.o
	g++ ${KEY_FOR_MAIN} -o gpss main.cpp Simulation.h creator_conditional.o

creator_conditional.o: creator_conditional.cpp creator_conditional.h
	g++ ${KEY_FOR_CREATOR_COND} -c creator_conditional.cpp

valgrind: main
	valgrind ${KEY_FOR_MEMORY} ./gpss

clear:
	rm -f Simulation.o creator_conditional.o gpss logger