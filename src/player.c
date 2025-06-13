#include "character.h"
#include "constants.h"

#include <stdio.h>

#include <allegro5/allegro_primitives.h>

/*
 * Funcao responsavel por criar o jogador.
 */
character create_player(){

  character newPlayer = create_character(WIDTH_RES/2.0 - (PLAYER_ENEMY_WIDTH/2), HEIGHT_RES- 2*PLAYER_ENEMY_HEIGHT, WIDTH_RES/2.0 + (PLAYER_ENEMY_WIDTH/2), HEIGHT_RES-PLAYER_ENEMY_HEIGHT, PLAYER, RECTANGLE);

  return newPlayer;

} 

/*
 * Funcao responsavel por mover o player para a esquerda, respeitando o limite da esquerda.
 * Parametros:
 * player - jogador a ser movido para a esquerda. Se for passado uma personagem que nao seja do tipo PLAYER,
 *          o codigo nao faz nada.
 */
void move_player_left(character* player){

  if(player->typeCharacter != PLAYER){

    printf("Voce passou um tipo de personagem errado. Passe apenas player para essa funcao.\n");
    return;

  }

  if(player->posX1-DEFAULT_SPEED > 0){
    player->posX1 -= DEFAULT_SPEED;
    player->posX2 -= DEFAULT_SPEED;
  }

  else{

    player->posX2 -= player->posX1;
    player->posX1 = 0;

  }

}

/* Funcao responsavel por mover o player para a direita, respeitando o limite da direita.
 * Parametros:
 * player - jogador a ser movido para a esquerda. Se for passado uma personagem que nao seja do tipo PLAYER,
 *          o codigo nao faz nada.
 */
void move_player_right(character* player){

  if(player->typeCharacter != PLAYER){

    printf("Voce passou um tipo de personagem errado. Passe apenas player para essa funcao.\n");
    return;

  }

  if(player->posX2 + DEFAULT_SPEED < WIDTH_RES){
    player->posX1 += DEFAULT_SPEED;
    player->posX2 += DEFAULT_SPEED;
  }

  else{

    player->posX1 += (WIDTH_RES-player->posX2);
    player->posX2 = WIDTH_RES;

  }


}

/*
 * Funcao responsavel por desenhar o jogador na tela.
 * Parametros:
 * player - jogador a ser desenhado na tela. Se for passado outro tipo de personagem que nao PLAYER, nada eh feito.
 */
void draw_player(character* player){

  if(player->typeCharacter != PLAYER){

    printf("Voce passou um tipo de personagem errado. Passe apenas player para essa funcao.\n");
    return;

  }

  if(player->typeShowing == RECTANGLE){

    al_draw_filled_rectangle(player->posX1, player->posY1,
        player->posX2, player->posY2,
        al_map_rgb(0, 60, 70));

    printf("A area do retangulo ta %.3f\n", (player->posX2-player->posX1)*(player->posY2-player->posY1));

  }


}
