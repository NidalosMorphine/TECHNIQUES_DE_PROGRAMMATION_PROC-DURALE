# Ex 7 - premier Makefile (une règle par .o) :
#
# notes: main.o stats.o
# 	gcc main.o stats.o -o notes
#
# main.o: main.c stats.h
# 	gcc -c main.c
#
# stats.o: stats.c stats.h
# 	gcc -c stats.c
#
# Si on modifie seulement stats.c, make ne recompile que stats.o puis refait le lien.

# Ex 8 - version réutilisable

CC = cc
CFLAGS = -std=c11 -Wall -Wextra -g
EXE = notes
OBJ = main.o stats.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

%.o: %.c stats.h
	$(CC) $(CFLAGS) -c $<

run: $(EXE)
	./$(EXE)

clean:
	rm -f *.o $(EXE)

.PHONY: all run clean
