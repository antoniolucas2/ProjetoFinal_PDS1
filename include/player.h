#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "character.h"

/*
 * Funcao responsavel por criar o jogador.
 */
character create_player();

/*
 * Funcao que libera da memoria o jogador.
 * Parametros:
 * player - ponteiro para o jogador.
 */
character* destroy_player(character* player);

/*
 * Funcao responsavel por mover o player para a esquerda, respeitando o limite da esquerda.
 * Parametros:
 * player - jogador a ser movido para a esquerda. Se for passado uma personagem que nao seja do tipo PLAYER,
 *          o codigo nao faz nada.
 */
void move_player_left(character* player);

/* Funcao responsavel por mover o player para a direita, respeitando o limite da direita.
 * Parametros:
 * player - jogador a ser movido para a esquerda. Se for passado uma personagem que nao seja do tipo PLAYER,
 *          o codigo nao faz nada.
 */
void move_player_right(character* player);

/*
 * Funcao responsavel por desenhar o jogador na tela.
 * Parametros:
 * player - jogador a ser desenhado na tela. Se for passado outro tipo de personagem que nao PLAYER, nada eh feito.
 */
void draw_player(character* player);

#endif
