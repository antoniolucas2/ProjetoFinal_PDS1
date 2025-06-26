#include "character.h"
#include "constants.h"
#include "initialize.h"
#include "enemies.h"

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro_primitives.h>

character** create_matrix_enemies(enemies* all_enemies){

  character** matrix_enemies;

  matrix_enemies = malloc(TOTAL_LINES * sizeof(character*));
  assert_pointer_not_null(matrix_enemies, "Erro na criacao das linhas das matriz de inimigos", ERRO_CRIACAO_LINHA_INIMIGOS);

  int currentY = CEIL_DISTANCE;
  int currentX;
  enum TYPE_CHARACTER curr_enemy_type;

  for(int i = 0; i < TOTAL_LINES; i++){

    matrix_enemies[i] = malloc(TOTAL_ENEMIES_PER_LINE * sizeof(character));
    currentX = WALL_DISTANCE;

    curr_enemy_type = ((i/2)%3 == 0) ? ENEMY_500 : ((i/2)%3 == 1) ? ENEMY_250 : ENEMY_100;

    for(int j = 0; j < TOTAL_ENEMIES_PER_LINE; j++){

      matrix_enemies[i][j] = create_character(currentX, currentY, currentX + PLAYER_ENEMY_WIDTH, currentY + PLAYER_ENEMY_HEIGHT, curr_enemy_type, BITMAP, all_enemies->array_bitmaps[(i/2)%3]);
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

    for(int j = 0; j < all_enemies.totalEachLine[i]; j++){

      if(matrix[i][j].typeShowing == RECTANGLE)
        al_draw_filled_rectangle(matrix[i][j].posX1, matrix[i][j].posY1, matrix[i][j].posX2, matrix[i][j].posY2, al_map_rgb(126, 0, 0));

      else if(matrix[i][j].typeShowing == BITMAP)
        al_draw_bitmap(matrix[i][j].img, matrix[i][j].posX1, matrix[i][j].posY1, 0);

    }

  }

}

enemies create_enemies(){

  enemies newEnemies;

  ALLEGRO_BITMAP* inimigo100 = al_load_bitmap("img/inimigo100.png");
  ALLEGRO_BITMAP* inimigo250 = al_load_bitmap("img/inimigo250.png");
  ALLEGRO_BITMAP* inimigo500 = al_load_bitmap("img/inimigo500.png");

  assert_pointer_not_null(inimigo100, "Nao consegui abrir a imagem do inimigo de 100 pontos!\n", ERRO_ABERTURA_IMAGEM);
  assert_pointer_not_null(inimigo250, "Nao consegui abrir a imagem do inimigo de 250 pontos!\n", ERRO_ABERTURA_IMAGEM);
  assert_pointer_not_null(inimigo500, "Nao consegui abrir a imagem do inimigo de 500 pontos!\n", ERRO_ABERTURA_IMAGEM);

  newEnemies.array_bitmaps[0] = inimigo100;
  newEnemies.array_bitmaps[1] = inimigo250;
  newEnemies.array_bitmaps[2] = inimigo500;

  newEnemies.matrix_enemies = create_matrix_enemies(&newEnemies);

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

  if(destroy->matrix_enemies[0][0].typeShowing == BITMAP){

    al_destroy_bitmap(destroy->array_bitmaps[0]);
    al_destroy_bitmap(destroy->array_bitmaps[1]);
    al_destroy_bitmap(destroy->array_bitmaps[2]);

  }

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

  if(all_enemies->totalEnemies == 0)
    return;

  int currentLine = all_enemies->currentLineToMove;

  while(!all_enemies->totalEachLine[currentLine])
    currentLine = (currentLine+1) % TOTAL_LINES;

  int newX;
  int totalEnemies = all_enemies->totalEachLine[currentLine];

  if(all_enemies->direction == 1 && all_enemies->matrix_enemies[currentLine][totalEnemies-1].posX2 + ENEMY_HORIZONTAL_TRAVEL_DISTANCE > WIDTH_RES){
    
    move_enemies_line(all_enemies); 
    all_enemies->direction = -1;
    return;

  }

  else if(all_enemies->direction == -1 && all_enemies->matrix_enemies[currentLine][0].posX1 - ENEMY_HORIZONTAL_TRAVEL_DISTANCE < 0){
    
    move_enemies_line(all_enemies); 
    all_enemies->direction = 1;
    return;

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

void remove_enemy(enemies* all_enemies, int lineEnemy, int indexEnemy){

  if(!all_enemies){

    fprintf(stderr, "A matriz de inimigos nao esta alocada. Cuidado!\n");
    return;

  }

  if(lineEnemy < 0 || lineEnemy >= TOTAL_LINES){

    fprintf(stderr, "Linha errada colocada. Cuidado!\n");
    return;

  }

  if(indexEnemy < 0 || indexEnemy >= all_enemies->totalEachLine[lineEnemy]){

    fprintf(stderr, "Indice errado do inimigo colocado. Cuidado!\n");
    return;

  }

  printf("acho que toquei em linhas %d pos %d, e a linha tem um total de %d!\n", lineEnemy, indexEnemy, all_enemies->totalEachLine[lineEnemy]);

  all_enemies->matrix_enemies[lineEnemy][indexEnemy].active = false;
  character enemyElim = all_enemies->matrix_enemies[lineEnemy][indexEnemy];
  int i;

  for(i = indexEnemy+1; i < all_enemies->totalEachLine[lineEnemy]; i++)
    all_enemies->matrix_enemies[lineEnemy][i-1] = all_enemies->matrix_enemies[lineEnemy][i];

  if(i > 0)
    all_enemies->matrix_enemies[lineEnemy][i-1] = enemyElim;

  all_enemies->totalEachLine[lineEnemy]--;
  all_enemies->totalEnemies--;

  printf("sai da funcaum\n");

}

character* get_lowest_enemy(enemies all_enemies){

  if(all_enemies.totalEnemies == 0)
    return NULL;

  int i;

  for(i = TOTAL_LINES-1; i >= 0 && all_enemies.totalEachLine[i] == 0; i--);

  return &all_enemies.matrix_enemies[i][0];

}

bool player_enemy_touch(enemies* all_enemies, character* player){

  character* curr_enemy;

  for(int i = TOTAL_LINES-1; i >= 0; i--){

    for(int j = 0; j < all_enemies->totalEachLine[i]; j++){

      curr_enemy = &all_enemies->matrix_enemies[i][j];

      if(curr_enemy->posY2 < player->posY1)
        return false;

      else if(overlap_on_x_axis(curr_enemy, player) && overlap_on_y_axis(curr_enemy, player))
        return true;

    }


  }

  return false;

}
