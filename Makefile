CC = gcc
CCFLAGS = -Wall 
LIBS =
LIBSDIR =
IDIR =


SRC =  labyrinthAPI.c clientAPI.c main.c
OBJ = $(SRC:.c=.o)
EXEC = Laby


all: $(EXEC)



labyrinthAPI.o: labyrinthAPI.h clientAPI.h
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $< $(IDIR)

clientAPI.o: clientAPI.h
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $< $(IDIR)

main.o: labyrinthAPI.h
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $< $(IDIR)



$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBSDIR)


clean:
	rm -f *.o
	ls $(OBJ)
mproper:
	rm -f $(EXEC) *.o
