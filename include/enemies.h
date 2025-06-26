#ifndef ENEMIES_HEADER
#define ENEMIES_HEADER

#include "character.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

typedef struct STRUCT_ENEMIES{

  character** matrix_enemies;
  int* totalEachLine;
  int totalEnemies;
  int currentLineToMove;
  int direction;

  ALLEGRO_BITMAP* array_bitmaps[3];

}enemies;

enemies create_enemies();
void destroy_enemies(enemies* destroy);
void draw_enemies(enemies all_enemies);
void move_enemies(enemies* all_enemies, ALLEGRO_SAMPLE* enemies_moving);
void remove_enemy(enemies* all_enemies, int lineEnemy, int indexEnemy, ALLEGRO_SAMPLE* explode);
character* get_lowest_enemy(enemies all_enemies);
bool player_enemy_touch(enemies* all_enemies, character* player);

#endif
