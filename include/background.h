#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include "character.h"
#include "enemies.h"

#include <stdio.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

typedef struct STRUCT_BACKGROUND{

  character soil;
  int totalScore;
  ALLEGRO_COLOR background_color;
  FILE* file_save;
  int last_record;

}background;

background create_background(ALLEGRO_COLOR background_color, character current_player);
void draw_background(background* currBackground, ALLEGRO_FONT* font);
bool enemy_on_background(background* currBackground, enemies all_enemies);
void save_and_close_save_file(background* curr_bg);

#endif
