#include "background.h"
#include "character.h"
#include "constants.h"
#include "enemies.h"
#include "initialize.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  newBackground.vector_points = NULL;
  newBackground.total_points = 0;

  srand(time(NULL));
  int scenary = rand()%4 + 1;

  char filename[30];
  sprintf(filename, "img/cenario%d.png", scenary);

  newBackground.space_scenary = al_load_bitmap(filename);
  assert_pointer_not_null(newBackground.space_scenary, "Nao consegui abrir a imagem pro cenario de fundo!\n", ERRO_ABERTURA_IMAGEM);
  newBackground.soil_img = al_load_bitmap("img/solo.png");
  assert_pointer_not_null(newBackground.soil_img, "Nao consegui abrir a imagem pro solo!\n", ERRO_ABERTURA_IMAGEM);

  return newBackground;


}

void close_background(background* curr_bg){

  if(!curr_bg->file_save){

    fprintf(stderr, "Arquivo nao esta aberto! Cuidado!\n");
    return;

  }

  if(curr_bg->totalScore > curr_bg->last_record){

    fseek(curr_bg->file_save, SEEK_SET, 0);
    fprintf(curr_bg->file_save, "Record: %d", curr_bg->totalScore);

  }

  fclose(curr_bg->file_save);

  if(curr_bg->vector_points)
    free(curr_bg->vector_points);

  al_destroy_bitmap(curr_bg->space_scenary);
  al_destroy_bitmap(curr_bg->soil_img);

}

void delete_points_warning(background* curr_background, int idx){

  if(!curr_background->vector_points || curr_background->total_points == 0){

    printf("Vetor dos points warning ja esta vazio! Cuidado!\n");
    return;

  }

  for(int i = idx + 1; i < curr_background->total_points; i++)
    curr_background->vector_points[i-1] = curr_background->vector_points[i];

  curr_background->vector_points = realloc(curr_background->vector_points, (--curr_background->total_points)*sizeof(points_warning));

  if(curr_background->total_points == 0)
    curr_background->vector_points = NULL;

}

void draw_background(background* currBackground, ALLEGRO_FONT* font_score, ALLEGRO_FONT* font_points){

  al_draw_bitmap(currBackground->space_scenary, 0, 0, 0);
  al_draw_bitmap(currBackground->soil_img, currBackground->soil.posX1, currBackground->soil.posY1, 0);
  //al_draw_filled_rectangle(currBackground->soil.posX1, currBackground->soil.posY1, currBackground->soil.posX2, currBackground->soil.posY2, currBackground->background_color);
  al_draw_textf(font_score, al_map_rgb(255, 255, 255), 30, 30, ALLEGRO_ALIGN_LEFT, "Score: %d", currBackground->totalScore);
  al_draw_textf(font_score, al_map_rgb(255, 255, 255), WIDTH_RES-30, 30, ALLEGRO_ALIGN_RIGHT, "Recorde passado: %d", currBackground->last_record);

  points_warning curr_points;

  for(int i = 0; i < currBackground->total_points;){

    curr_points = currBackground->vector_points[i];
  
    if(curr_points.frames_left == 0)
      delete_points_warning(currBackground, i);

    else{

      al_draw_textf(font_points, al_map_rgba_f(1, 1, 1, curr_points.frames_left/((float)FRAME_POINTS)), curr_points.posX, curr_points.posY, 0, "%d", curr_points.currentPoints);
      curr_points.posY -= POINTS_VERTICAL_SPEED;
      curr_points.frames_left--;
      currBackground->vector_points[i] = curr_points;
      i++;

    }

  }

}

bool enemy_on_background(background* currBackground, enemies all_enemies){

  character* lowest = get_lowest_enemy(all_enemies);
  character* soil = &currBackground->soil;

  if(lowest && overlap_on_x_axis(lowest, soil) && overlap_on_y_axis(lowest, soil))
    return true;

  return false;

}

void add_score_background(background* currBackground, points_warning points){

  currBackground->totalScore += points.currentPoints;
  currBackground->vector_points = realloc(currBackground->vector_points, (++currBackground->total_points)*sizeof(points_warning));

  currBackground->vector_points[currBackground->total_points-1] = points;

}

void delete_save(background* curr_background){

  if(!curr_background->file_save){

    printf("O arquivo do save nem existe! Cuidado!\n");
    return;

  }

  fclose(curr_background->file_save);
  curr_background->file_save = fopen("save/records.txt", "w+");
  assert_pointer_not_null(curr_background->file_save, "Nao consegui reabrir o arquivo do save", ERRO_ABERTURA_SAVE);

  fprintf(curr_background->file_save, "Record: 0");
  curr_background->last_record = 0;
  fseek(curr_background->file_save, SEEK_SET, 0);

}
