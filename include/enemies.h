#ifndef ENEMIES_HEADER
#define ENEMIES_HEADER

#include "character.h"

typedef struct STRUCT_ENEMIES{

  character** matrix_enemies;
  int* totalEachLine;
  int totalEnemies;
  int currentLineToMove;
  int direction;

}enemies;

enemies create_enemies();
void destroy_enemies(enemies* destroy);
void draw_enemies(enemies all_enemies);
void move_enemies(enemies* all_enemies);

#endif
