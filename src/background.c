#include "background.h"
#include "character.h"
#include "constants.h"
#include "enemies.h"
#include "initialize.h"

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

  newBackground.file_save = fopen("save/records.txt", "r+");

  if(!newBackground.file_save){

    newBackground.file_save = fopen("save/records.txt", "w+");
    assert_pointer_not_null(newBackground.file_save, "Nao consegui abrir o arquivo do save!", ERRO_ABERTURA_SAVE);

    fprintf(newBackground.file_save, "Record: 0");
    fseek(newBackground.file_save, SEEK_SET, 0);

  }

  fscanf(newBackground.file_save, "Record: %d", &newBackground.last_record);

  return newBackground;


}

void save_and_close_save_file(background* curr_bg){

  if(!curr_bg->file_save){

    fprintf(stderr, "Arquivo nao esta aberto! Cuidado!\n");
    return;

  }

  if(curr_bg->totalScore > curr_bg->last_record){

    fseek(curr_bg->file_save, SEEK_SET, 0);
    fprintf(curr_bg->file_save, "Record: %d", curr_bg->totalScore);

  }

  fclose(curr_bg->file_save);

}

void draw_background(background* currBackground, ALLEGRO_FONT* font){

  char scoreAtual[20];
  char scorePassado[30];

  sprintf(scoreAtual, "Score: %d", currBackground->totalScore);
  sprintf(scorePassado, "Recorde Passado: %d", currBackground->last_record);

  al_draw_filled_rectangle(currBackground->soil.posX1, currBackground->soil.posY1, currBackground->soil.posX2, currBackground->soil.posY2, currBackground->background_color);
  al_draw_text(font, al_map_rgb(255, 255, 255), 30, 30, 0, scoreAtual);
  al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_RES*0.6, 30, 0, scorePassado);

}

bool enemy_on_background(background* currBackground, enemies all_enemies){

  character* lowest = get_lowest_enemy(all_enemies);
  character* soil = &currBackground->soil;

  if(lowest && overlap_on_x_axis(lowest, soil) && overlap_on_y_axis(lowest, soil))
    return true;

  return false;

}
