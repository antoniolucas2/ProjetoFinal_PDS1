#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER

enum TYPE_CHARACTER{PLAYER=0, ENEMY, BULLET};
enum TYPE_SHOWING{RECTANGLE=0, BITMAP};

typedef struct STRUCT_CHARACTER character;

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
character* create_character(float posX1, float posY1, float posX2, float posY2, enum TYPE_CHARACTER typeCharacter, enum TYPE_SHOWING typeShowing);

/*
 * Funcao responsavel por destruir a personagem, tomando cuidado para que ela exista.
 * Parametros:
 * pointer: personagem que deseja ser destruida.
 * Retorno:
 * Retorna NULL para indicar que a personagem esta vazia, ou seja, nao alocada dinamicamente.
 */
character* destruct_character(character* pointer);

#endif
