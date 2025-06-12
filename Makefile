GCC_VERSION := -std=c99
FLAGS := -Wall -Wextra -g

INCLUDE_DIR := include
OBJ_DIR := obj
SRC_DIR := src

OBJ_FILES := obj/main.o

MAIN_EXECUTABLE := main

all: $(OBJ_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/*.o -o $(MAIN_EXECUTABLE)

obj/main.o: main.c
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c main.c -o $(OBJ_DIR)/main.o

clean_executable:
	rm $(MAIN_EXECUTABLE)

clean_obj:
	rm $(OBJ_DIR)/*.o

