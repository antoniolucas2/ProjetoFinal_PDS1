#include "character.h"
#include "initialize.h"
#include "constants.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * Funcao responsavel por criar a personagem, que pode ser o proprio player, um inimigo ou uma bala.
 * Essa personagem eh sempre tratada como um retangulo.
 * Parametros:
 * posX1:         indica a posicao X1 do par (X1,Y1) que estara o ponto mais em cima e mais a esquerda da personagem.
 * posY1:         indica a posicao Y1 do par (X1,Y1) que estara o ponto mais em cima e mais a esquerda da personagem.
 * posX2:         indica a posicao X2 do par (X2,Y2) que estara o ponto mais abaixo e mais a direita da personagem.
 * posY2:         indica a posicao Y2 do par (X2,Y2) que estara o ponto mais abaixo e mais a direita da personagem.
 * typeCharacter: indica o tipo que a personagem eh, podendo ser PLAYER, ENEMY ou BULLET.
 * typeShowing:   indica a forma que a personagem sera mostrada, podendo ser RECTANGLE ou BITMAP.
 * Retorno:
 * Retorna uma copia para uma personagem.
 */
character create_character(float posX1, float posY1, float posX2, float posY2, enum TYPE_CHARACTER typeCharacter, enum TYPE_SHOWING typeShowing, ...){

  va_list args;

  character newCharacter;

  newCharacter.posX1 = posX1;
  newCharacter.posY1 = posY1;
  newCharacter.posX2 = posX2;
  newCharacter.posY2 = posY2;

  newCharacter.typeCharacter = typeCharacter;
  newCharacter.typeShowing = typeShowing;

  newCharacter.active = true;

  if(typeShowing == BITMAP){

    va_start(args, typeShowing);

    newCharacter.img = va_arg(args, ALLEGRO_BITMAP*);
    assert_pointer_not_null(newCharacter.img, "Nao consegui abrir a imagem pra personagem!\n", ERRO_ABERTURA_IMAGEM);

    va_end(args);

  }

  return newCharacter;

}

void change_character_active_state(character* currCharacter, bool newState){

  currCharacter->active = newState;

}

bool overlap_on_x_axis(character* r1, character* r2){

  if(r1->posX1 >= r2->posX1 && r1->posX1 <= r2->posX2)
    return true;

  else if(r2->posX1 >= r1->posX1 && r2->posX1 <= r1->posX2)
    return true;

  return false;

}

bool overlap_on_y_axis(character* r1, character* r2){

  if(r1->posY1 >= r2->posY1 && r1->posY1 <= r2->posY2)
    return true;

  else if(r2->posY1 >= r1->posY1 && r2->posY1 <= r1->posY2)
    return true;

  return false;

}
