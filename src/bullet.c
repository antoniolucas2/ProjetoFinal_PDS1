#include "character.h"
#include "constants.h"
#include "enemies.h"
#include "background.h"

#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

character create_player_bullet(){

  character newPlayerBullet = create_character(0, 0, 0, 0, PLAYER_BULLET, RECTANGLE);
  newPlayerBullet.active = false;

  return newPlayerBullet;

}

void try_shooting_player_bullet(character* player_bullet, character* player, ALLEGRO_SAMPLE* spl){

  if(player_bullet->typeCharacter != PLAYER_BULLET){

    printf("Esta nao eh uma bala do jogador. Cuidado!\n");
    return;

  }

  if(player_bullet->active == true){

    printf("A bala ja foi atirada em algum momento anterior!\n");
    return;

  }

  al_play_sample(spl, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

  int posX1Player = player->posX1;
  int posY1Player = player->posY1;

  int posX1 = posX1Player + PLAYER_ENEMY_WIDTH/2;
  int posY2 = posY1Player - 1;

  int posX2 = posX1 + BULLET_WIDTH;
  int posY1 = posY2 - BULLET_HEIGHT; 

  *player_bullet = create_character(posX1, posY1, posX2, posY2, PLAYER_BULLET, RECTANGLE);
  player_bullet->active = true;

}

void move_bullet(character* bullet){

  if(bullet->typeCharacter != PLAYER_BULLET){

    printf("Nao eh uma personagem do tipo bala! Cuidado!\n");
    return;

  }

  if(bullet->active != true)
    return;

  int newY1, newY2;

  newY1 = bullet->posY1 - BULLET_SPEED;
  newY2 = newY1 + BULLET_HEIGHT;

  if(newY2 < 0)
    bullet->active = false;

  bullet->posY1 = newY1;
  bullet->posY2 = newY2;

}

enum TYPE_CHARACTER draw_bullet(character* bullet, enemies* all_enemies, background* curr_background, ALLEGRO_SAMPLE* enemy_death){
  
  move_bullet(bullet);

  if(!bullet->active)
    return PLAYER_BULLET;

  int currLine;
  bool touched = false;
  character* currEnemy;
  enum TYPE_CHARACTER enemy_type = PLAYER_BULLET;

  for(currLine = 0; currLine < TOTAL_LINES; currLine++){

    if(all_enemies->totalEachLine[currLine] > 0 && overlap_on_y_axis(bullet, &all_enemies->matrix_enemies[currLine][0]))
      break;

  }

  if(currLine != TOTAL_LINES){

    for(int i = 0; i < all_enemies->totalEachLine[currLine]; i++){

      currEnemy = &all_enemies->matrix_enemies[currLine][i];

      if(overlap_on_x_axis(currEnemy, bullet)){
      
        touched = true;
        enemy_type = all_enemies->matrix_enemies[currLine][i].typeCharacter;
        points_warning points;
        points.currentPoints = (enemy_type == ENEMY_100) ? 100 : (enemy_type == ENEMY_250) ? 250 : 500;
        points.posX = currEnemy->posX1 + PLAYER_ENEMY_WIDTH/2;
        points.posY = currEnemy->posY1 - 1;
        points.frames_left = FRAME_POINTS;
        add_score_background(curr_background, points);
        remove_enemy(all_enemies, currLine, i, enemy_death);
        break;

      }

    }

  }

  if(touched){

    bullet->active = false;
    printf("Toquei! Tipo: %d\n", enemy_type);
    return enemy_type;

  }

  al_draw_filled_rectangle(bullet->posX1, bullet->posY1, bullet->posX2, bullet->posY2, al_map_rgb(255, 255, 255));

  return PLAYER_BULLET;

}
