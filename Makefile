GCC_VERSION := -std=c99
FLAGS := -Wall -Wextra -g

INCLUDE_DIR := include
OBJ_DIR := obj
SRC_DIR := src

OBJ_FILES := $(OBJ_DIR)/main.o $(OBJ_DIR)/initialize.o $(OBJ_DIR)/character.o
HEADER_FILES := $(INCLUDE_DIR)/*.h

LINKER_FILES := -lallegro -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec

MAIN_EXECUTABLE := main

all: $(OBJ_FILES) $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/*.o -o $(MAIN_EXECUTABLE) $(LINKER_FILES)

$(OBJ_DIR)/main.o: main.c
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c main.c -o $(OBJ_DIR)/main.o $(LINKER_FILES)

$(OBJ_DIR)/initialize.o: $(SRC_DIR)/initialize.c $(INCLUDE_DIR)/initialize.h
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/initialize.c -o $(OBJ_DIR)/initialize.o $(LINKER_FILES)

$(OBJ_DIR)/character.o: $(SRC_DIR)/character.c $(INCLUDE_DIR)/character.h
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/character.c -o $(OBJ_DIR)/character.o $(LINKER_FILES)

clean_executable:
	rm $(MAIN_EXECUTABLE)

clean_obj:
	rm $(OBJ_DIR)/*.o

