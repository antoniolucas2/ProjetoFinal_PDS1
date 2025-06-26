GCC_VERSION := -std=c99
FLAGS := -Wall -Wextra -g

INCLUDE_DIR := include
OBJ_DIR := obj
SRC_DIR := src

OBJ_FILES := $(OBJ_DIR)/main.o $(OBJ_DIR)/initialize.o $(OBJ_DIR)/character.o $(OBJ_DIR)/player.o $(OBJ_DIR)/enemies.o $(OBJ_DIR)/bullet.o $(OBJ_DIR)/background.o
HEADER_FILES := $(INCLUDE_DIR)/*.h

LINKER_FILES := -lallegro -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_ttf

MAIN_EXECUTABLE := main

all: $(OBJ_FILES) $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/*.o -o $(MAIN_EXECUTABLE) $(LINKER_FILES)

$(OBJ_DIR)/main.o: main.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c main.c -o $(OBJ_DIR)/main.o $(LINKER_FILES)

$(OBJ_DIR)/initialize.o: $(SRC_DIR)/initialize.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/initialize.c -o $(OBJ_DIR)/initialize.o $(LINKER_FILES)

$(OBJ_DIR)/character.o: $(SRC_DIR)/character.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/character.c -o $(OBJ_DIR)/character.o $(LINKER_FILES)

$(OBJ_DIR)/player.o: $(SRC_DIR)/player.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/player.c -o $(OBJ_DIR)/player.o $(LINKER_FILES)

$(OBJ_DIR)/enemies.o: $(SRC_DIR)/enemies.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/enemies.c -o $(OBJ_DIR)/enemies.o $(LINKER_FILES)

$(OBJ_DIR)/bullet.o: $(SRC_DIR)/bullet.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/bullet.c -o $(OBJ_DIR)/bullet.o $(LINKER_FILES)

$(OBJ_DIR)/background.o: $(SRC_DIR)/background.c $(HEADER_FILES)
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/background.c -o $(OBJ_DIR)/background.o $(LINKER_FILES)

recompile_everything:
	gcc $(GCC_VERSION) $(FLAGS) -I$(INCLUDE_DIR) $(SRC_DIR)/*.c main.c -o $(MAIN_EXECUTABLE) $(LINKER_FILES)

clean_executable:
	rm $(MAIN_EXECUTABLE)

clean_obj:
	rm $(OBJ_DIR)/*.o

run:
	./$(MAIN_EXECUTABLE)
