# Yuval Hamberg
# yuval.hamberg@gmail.com
# 17/07/2017
# WhatDown chat app

# File names
EXE_NAME1 = frontEnd
EXE_NAME2 = backEnd
EXE_NAME3 = reader
EXE_NAME4 = writer

CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -Isrc/ 

.Phony : clean rebuild all run run$(EXE_NAME1) run$(EXE_NAME2)

# Main target
all: $(EXE_NAME1) $(EXE_NAME2) $(EXE_NAME3) $(EXE_NAME4)
	

$(EXE_NAME1): 
	$(MAKE) all -C clientSide
	
$(EXE_NAME2): 	
	$(MAKE) all -C serverSide	
	
$(EXE_NAME3): 	
	$(MAKE) reader -C chats
	
$(EXE_NAME4): 	
	$(MAKE) writer -C chats

run$(EXE_NAME1): $(EXE_NAME1) $(EXE_NAME3) $(EXE_NAME4)
	./clientSide/whatDownApp
	
run$(EXE_NAME2): $(EXE_NAME2)
	./serverSide/whatDownApp
	
# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f *.o src/*.o client_test/*.o server/*.o
	rm -f *~
	rm -f $(EXE_NAME1) $(EXE_NAME2) $(EXE_NAME3) $(EXE_NAME4)
	rm -f a.out
	$(MAKE) clean -C clientSide
	$(MAKE) clean -C serverSide
	$(MAKE) clean -C chats

rebuild : clean all


