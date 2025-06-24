#include "character.h"
#include "constants.h"
#include "initialize.h"
#include "enemies.h"

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro_primitives.h>

character** create_matrix_enemies(){

  character** matrix_enemies;

  matrix_enemies = malloc(TOTAL_LINES * sizeof(character*));
  assert_pointer_not_null(matrix_enemies, "Erro na criacao das linhas das matriz de inimigos", ERRO_CRIACAO_LINHA_INIMIGOS);

  int currentY = 20;
  int currentX;

  for(int i = 0; i < TOTAL_LINES; i++){

    matrix_enemies[i] = malloc(TOTAL_ENEMIES_PER_LINE * sizeof(character));
    currentX = WALL_DISTANCE;

    for(int j = 0; j < TOTAL_ENEMIES_PER_LINE; j++){

      matrix_enemies[i][j] = create_character(currentX, currentY, currentX + PLAYER_ENEMY_WIDTH, currentY + PLAYER_ENEMY_HEIGHT, ENEMY, RECTANGLE);
      currentX += PLAYER_ENEMY_WIDTH + ((WIDTH_RES - 2*WALL_DISTANCE - PLAYER_ENEMY_WIDTH)/(TOTAL_ENEMIES_PER_LINE-1) - PLAYER_ENEMY_WIDTH);

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

void draw_enemies(enemies all_enemies){

  character** matrix = all_enemies.matrix_enemies;

  if(!matrix){

    printf("Matriz esta vazia! Cuidado!\n");
    return;

  }

  for(int i = 0; i < TOTAL_LINES; i++){

    for(int j = 0; j < TOTAL_ENEMIES_PER_LINE; j++){

      al_draw_filled_rectangle(matrix[i][j].posX1, matrix[i][j].posY1, matrix[i][j].posX2, matrix[i][j].posY2, al_map_rgb(126, 0, 0));

    }

  }

}

enemies create_enemies(){

  enemies newEnemies;

  newEnemies.matrix_enemies = create_matrix_enemies();

  assert_pointer_not_null(newEnemies.matrix_enemies, "Nao consegui alocar a matriz de inimigos!", ERRO_CRIACAO_MATRIZ_INIMIGOS);

  newEnemies.totalEachLine = malloc(sizeof(int)*TOTAL_LINES);
  assert_pointer_not_null(newEnemies.totalEachLine, "Nao consegui alocar um vetor que diz quantos inimigos vivos tem na linha!", ERRO_VETOR_TOTAL_INIMIGOS);

  for(int i = 0; i < TOTAL_LINES; i++)
    newEnemies.totalEachLine[i] = TOTAL_ENEMIES_PER_LINE;

  newEnemies.currentLineToMove = 0;
  newEnemies.direction = 1;
  newEnemies.totalEnemies = TOTAL_LINES * TOTAL_ENEMIES_PER_LINE;

  return newEnemies;

}

void destroy_enemies(enemies* destroy){

  if(destroy->matrix_enemies)
    destroy->matrix_enemies = destroy_matrix_enemies(destroy->matrix_enemies);

  if(destroy->totalEachLine)
    free(destroy->totalEachLine);

}

void move_enemies_line(enemies* all_enemies){

  int newY;

  for(int i = 0; i < TOTAL_LINES; i++){

    for(int j = 0; j < all_enemies->totalEachLine[i]; j++){

      newY = all_enemies->matrix_enemies[i][j].posY1 + ENEMY_VERTICAL_TRAVEL_DISTANCE;
      all_enemies->matrix_enemies[i][j].posY1 = newY;
      all_enemies->matrix_enemies[i][j].posY2 = newY + PLAYER_ENEMY_HEIGHT;

    }

  }

}

void move_enemies(enemies* all_enemies){

  int currentLine = all_enemies->currentLineToMove;

  while(!all_enemies->totalEachLine[currentLine])
    currentLine = (currentLine+1) % TOTAL_LINES;

  int newX;
  int totalEnemies = all_enemies->totalEachLine[currentLine];

  if(all_enemies->direction == 1 && all_enemies->matrix_enemies[currentLine][totalEnemies-1].posX2 + ENEMY_HORIZONTAL_TRAVEL_DISTANCE > WIDTH_RES){
    
    move_enemies_line(all_enemies); 
    all_enemies->direction = -1;

  }

  else if(all_enemies->direction == -1 && all_enemies->matrix_enemies[currentLine][0].posX1 - ENEMY_HORIZONTAL_TRAVEL_DISTANCE < 0){
    
    move_enemies_line(all_enemies); 
    all_enemies->direction = 1;

  }

  all_enemies->currentLineToMove = currentLine;
  
  for(int i = 0; i < all_enemies->totalEachLine[currentLine]; i++){

    newX = all_enemies->matrix_enemies[currentLine][i].posX1;
    newX += ENEMY_HORIZONTAL_TRAVEL_DISTANCE * all_enemies->direction;

    all_enemies->matrix_enemies[currentLine][i].posX1 = newX;
    all_enemies->matrix_enemies[currentLine][i].posX2 = newX + PLAYER_ENEMY_WIDTH;

  }

  all_enemies->currentLineToMove = (currentLine+1)%TOTAL_LINES;

}
