#ifndef INITIALIZE_HEADER
#define INITIALIZE_HEADER

/* Essa funcao eh responsavel por iniciar tudo que eh necessario para o Allegro,
 * e caso algo nao consiga ser inicializado, ela imprime no stderr o que nao foi
 * inicializado e termina o programa com exit(CODIGO). Esses codigos estao definidos
 * no header constants.h*/
void initialize_allegro();

#endif
