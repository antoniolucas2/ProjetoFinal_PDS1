#include "background.h"
#include "character.h"
#include "constants.h"
#include "enemies.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>

background create_background(ALLEGRO_COLOR background_color, character current_player){

  background newBackground;

  int y_bg = current_player.posY2+1;

  newBackground.soil = create_character(0, y_bg, WIDTH_RES, HEIGHT_RES, BACKGROUND, RECTANGLE);
  newBackground.totalScore = 0;
  newBackground.background_color = background_color;

  return newBackground;


}

void draw_background(background* currBackground, ALLEGRO_FONT* font){

  char string[20];
  sprintf(string, "Score: %d", currBackground->totalScore);

  al_draw_filled_rectangle(currBackground->soil.posX1, currBackground->soil.posY1, currBackground->soil.posX2, currBackground->soil.posY2, currBackground->background_color);
  al_draw_text(font, al_map_rgb(255, 255, 255), 30, 30, 0, string);

}

bool enemy_on_background(background* currBackground, enemies all_enemies){

  character* lowest = get_lowest_enemy(all_enemies);
  character* soil = &currBackground->soil;

  if(lowest && overlap_on_x_axis(lowest, soil) && overlap_on_y_axis(lowest, soil))
    return true;

  return false;

}
