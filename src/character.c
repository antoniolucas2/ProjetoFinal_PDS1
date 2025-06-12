#include "character.h"

#include <stdlib.h>

typedef struct STRUCT_CHARACTER{

  float posX1, posY1;
  float posX2, posY2;

  enum TYPE_CHARACTER typeCharacter;
  enum TYPE_SHOWING typeShowing;

}character;

/*
 * Funcao responsavel por criar a personagem, que pode ser o proprio player, um inimigo ou uma bala.
 * Essa personagem eh sempre tratada como um retangulo.
 * Lembre-se de destruir a personagem apos utiliza-la!
 * Parametros:
 * posX1:         indica a posicao X1 do par (X1,Y1) que estara o ponto mais em cima e mais a esquerda da personagem.
 * posY1:         indica a posicao Y1 do par (X1,Y1) que estara o ponto mais em cima e mais a esquerda da personagem.
 * posX2:         indica a posicao X2 do par (X2,Y2) que estara o ponto mais abaixo e mais a direita da personagem.
 * posY2:         indica a posicao Y2 do par (X2,Y2) que estara o ponto mais abaixo e mais a direita da personagem.
 * typeCharacter: indica o tipo que a personagem eh, podendo ser PLAYER, ENEMY ou BULLET.
 * typeShowing:   indica a forma que a personagem sera mostrada, podendo ser RECTANGLE ou BITMAP.
 * Retorno:
 * Retorna um ponteiro para a personagem criada dinamicamente.
 */
character* create_character(float posX1, float posY1, float posX2, float posY2, enum TYPE_CHARACTER typeCharacter, enum TYPE_SHOWING typeShowing){

  character* newCharacter = malloc(sizeof(character));

  newCharacter->posX1 = posX1;
  newCharacter->posY1 = posY1;
  newCharacter->posX2 = posX2;
  newCharacter->posY2 = posY2;

  newCharacter->typeCharacter = typeCharacter;
  newCharacter->typeShowing = typeShowing;

  return newCharacter;

}

/*
 * Funcao responsavel por destruir a personagem, tomando cuidado para que ela exista.
 * Parametros:
 * pointer: personagem que deseja ser destruida.
 * Retorno:
 * Retorna NULL para indicar que a personagem esta vazia, ou seja, nao alocada dinamicamente.
 */
character* destruct_character(character* pointer){

  if(pointer)
    free(pointer);

  return NULL;

}
