GCC_VERSION := -std=c99
FLAGS := -Wall -Wextra -g
INCLUDE_DIR := include

MAIN_EXECUTABLE := main

all: compile_main
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) main.o -o $(MAIN_EXECUTABLE)
	$(MAKE) clean_obj

compile_main: main.c
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c main.c -o main.o

clean_executable:
	rm $(MAIN_EXECUTABLE)

clean_obj:
	rm *.o
