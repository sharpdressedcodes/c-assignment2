#/****************************************************************************
#* COSC2138/CPT220 - Programming Principles 2A
#* Study Period  2  2014 Assignment #2 - Brazilian Coffee Shop system
#* Full Name        : EDIT HERE
#* Student Number   : EDIT HERE
#* Start up code provided by the CTEACH team
#****************************************************************************/

RM		= rm -f
CC 		= gcc
FLAGS 	= -ansi -Wall -pedantic
OBJS 	= bcs.o bcs_utility.o bcs_options.o
EXE		= assignment2

$(EXE): $(OBJS)
	@echo 'Building $(EXE)'
	$(CC) -o $(EXE) $(OBJS)
	@echo 'Successfully built $(EXE)'
	@echo ' '
	
bcs.o: bcs.c bcs.h
	@echo 'Compiling bcs.o'
	$(CC) -c $(FLAGS) bcs.c
	@echo 'Successfully compiled bcs.o'
	@echo ' '
	
bcs_utiity.o: bcs_utility.c bcs_utility.h
	@echo 'Compiling bcs_utility.o'
	$(CC) -c $(FLAGS) bcs_utility.c
	@echo 'Successfully compiled bcs_utility.o'
	@echo ' '
	
bcs_options.o: bcs_options.c bcs_options.h
	@echo 'Compiling bcs_options.o'
	$(CC) -c $(FLAGS) bcs_options.c
	@echo 'Successfully compiled bcs_options.o'
	@echo ' '
	
clean:
	@echo 'Deleting $(OBJS)'
	$(RM) $(OBJS)
	@echo ' '
	@echo 'Deleting $(EXE)'
	$(RM) $(EXE)
	@echo ' '
	@echo 'Clean done'
	@echo ' '
