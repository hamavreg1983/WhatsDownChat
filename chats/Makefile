# Yuval Hamberg
# yuval.hamberg@gmail.com
# 04/07/2017
# TCP

# File names
EXE_NAME1 = writer
EXE_NAME2 = reader
#SOURCES = $(wildcard *.cpp)
#OBJECTS = $(SOURCES:.cpp=.o)
#H_FILES = $(wildcard *.h)

NEEDED_LIB = list/build/liblist.a

CC = gcc
CFLAGS = -g -Wall -pedantic -Isrc/ 

.Phony : clean rebuild all run

# Main target
$(EXE_NAME1): reader.o 
	$(CC) $(CFLAGS) reader.o -o $(EXE_NAME1) 

$(EXE_NAME2): writer.o
	$(CC) $(CFLAGS) writer.o -o $(EXE_NAME2)
 

all: $(EXE_NAME1) $(EXE_NAME2)

# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NEEDED_LIB) :
	$(MAKE) all -C list

clean:
	rm -f *.o src/*.o client_test/*.o server/*.o
	rm -f *~
	rm -f $(EXE_NAME1) $(EXE_NAME2) $(EXE_NAME3)
	rm -f a.out

rebuild : clean $(EXE_NAME1) $(EXE_NAME2)


