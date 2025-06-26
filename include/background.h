#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include "character.h"
#include "enemies.h"

#include <stdio.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

typedef struct STRUCT_POINTS_WARNING{

  int currentPoints;
  int frames_left;

  int posX;
  int posY;

}points_warning;

typedef struct STRUCT_BACKGROUND{

  character soil;
  int totalScore;
  ALLEGRO_COLOR background_color;
  FILE* file_save;
  int last_record;

  points_warning* vector_points;
  int total_points;

  ALLEGRO_BITMAP* space_scenary;
  ALLEGRO_BITMAP* soil_img;

}background;

background create_background(ALLEGRO_COLOR background_color, character current_player);
void draw_background(background* currBackground, ALLEGRO_FONT* font_score, ALLEGRO_FONT* font_points);
bool enemy_on_background(background* currBackground, enemies all_enemies);
void close_background(background* curr_bg);
void add_score_background(background* currBackground, points_warning points);

#endif
