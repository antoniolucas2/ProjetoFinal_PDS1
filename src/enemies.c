#include "character.h"
#include "constants.h"
#include "initialize.h"

#include <stdlib.h>
#include <stdio.h>

character** create_matrix_enemies(){

  character** matrix_enemies;

  matrix_enemies = malloc(TOTAL_LINES * sizeof(character*));
  assert_pointer_not_null(matrix_enemies, "Erro na criacao das linhas das matriz de inimigos", ERRO_CRIACAO_LINHA_INIMIGOS);

  int currentY = 20;
  int currentX;

  for(int i = 0; i < TOTAL_LINES; i++){

    matrix_enemies[i] = malloc(TOTAL_ENEMIES_PER_LINE * sizeof(character));
    currentX = 30;

    for(int j = 0; j < TOTAL_ENEMIES_PER_LINE; j++){

      matrix_enemies[i][j] = create_character(currentX, currentY, currentX + PLAYER_ENEMY_WIDTH, currentY + PLAYER_ENEMY_HEIGHT, ENEMY, RECTANGLE);
      currentX += PLAYER_ENEMY_WIDTH + 5;

    }

    currentY += PLAYER_ENEMY_HEIGHT + 10;

  }

  return matrix_enemies;

}

character** destroy_matrix_enemies(character** matrix){

  if(!matrix){

    printf("Matrix ja vazia!\n");
    return NULL;

  }

  for(int i = 0; i < TOTAL_LINES; i++)
    free(matrix[i]);

  free(matrix);

  return NULL;

}
