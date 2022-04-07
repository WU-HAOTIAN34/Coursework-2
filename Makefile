# code details

EXE = ./library
SRC= main.c book_management.c interface.c librarian.c user.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 
all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:      main.c interface.h book_management.h
interface.o: interface.c interface.h book_management.h user.h librarian.h   
book_management.o: book_management.c book_management.h interface.h
user.o:      user.c user.h interface.h librarian.h
librarian.o: librarian.c librarian.h interface.h book_management.h
