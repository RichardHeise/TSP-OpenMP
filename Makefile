FLAGS=-O3 -fopenmp

CC=gcc

RM=rm -f

EXEC=tspp

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o -lm
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC) -lm

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
