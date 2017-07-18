# Yuval Hamberg
# yuval.hamberg@gmail.com
# 15/07/2017
# chats windows udp multicast

# File names
EXE_NAME1 = reader
EXE_NAME2 = writer
#SOURCES = $(wildcard *.cpp)
#OBJECTS = $(SOURCES:.cpp=.o)
#H_FILES = $(wildcard *.h)

NEEDED_LIB = list/build/liblist.a

CC = gcc
CFLAGS = -g -Wall -pedantic -I../src/ 

.Phony : clean rebuild all run

# Main target
$(EXE_NAME1): reader.o reader.c netUDP_MultiCast.o netUDP_MultiCast.c 
	$(CC) $(CFLAGS) reader.o netUDP_MultiCast.o -o $(EXE_NAME1) 

$(EXE_NAME2): writer.o writer.c netUDP_MultiCast.o netUDP_MultiCast.c
	$(CC) $(CFLAGS) writer.o netUDP_MultiCast.o -o $(EXE_NAME2)
 

all: $(EXE_NAME1) $(EXE_NAME2)
	


# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NEEDED_LIB) :
	$(MAKE) all -C list

clean:
	rm -f *.o src/*.o
	rm -f *~
	rm -f $(EXE_NAME1) $(EXE_NAME2) $(EXE_NAME3)
	rm -f a.out

rebuild : clean $(EXE_NAME1) $(EXE_NAME2)


