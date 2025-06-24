#include "character.h"
#include "constants.h"
#include "enemies.h"

#include <stdio.h>
#include <allegro5/allegro_primitives.h>

character create_player_bullet(){

  character newPlayerBullet = create_character(0, 0, 0, 0, PLAYER_BULLET, RECTANGLE);
  newPlayerBullet.active = false;

  return newPlayerBullet;

}

void try_shooting_player_bullet(character* player_bullet, character* player){

  printf("ENTREI REAU\n\n\n\n\n\n\n\n\n");

  if(player_bullet->typeCharacter != PLAYER_BULLET){

    printf("Esta nao eh uma bala do jogador. Cuidado!\n");
    return;

  }

  if(player_bullet->active == true){

    printf("A bala ja foi atirada em algum momento anterior!\n");
    return;

  }

  printf("ENTREI\n\n\n\n\n");

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

void draw_bullet(character* bullet, enemies* all_enemies){
  
  if(!bullet->active)
    return;

  move_bullet(bullet);

  int currLine;
  bool touched = false;
  character* currEnemy;

  for(currLine = 0; currLine < TOTAL_LINES; currLine++){

    if(all_enemies->totalEachLine[currLine] > 0 && overlap_on_y_axis(bullet, &all_enemies->matrix_enemies[currLine][0]))
      break;

  }

  if(currLine != TOTAL_LINES){

    for(int i = 0; i < all_enemies->totalEachLine[currLine]; i++){

      currEnemy = &all_enemies->matrix_enemies[currLine][i];

      if(overlap_on_x_axis(currEnemy, bullet)){
      
        touched = true;
        remove_enemy(all_enemies, currLine, i);
        break;

      }

    }

  }

  if(touched){

    bullet->active = false;
    printf("Toquei!\n");
    return;

  }

  al_draw_filled_rectangle(bullet->posX1, bullet->posY1, bullet->posX2, bullet->posY2, al_map_rgb(255, 255, 255));


}
