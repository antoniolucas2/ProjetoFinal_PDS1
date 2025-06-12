#ifndef INITIALIZE_HEADER
#define INITIALIZE_HEADER

#include "constants.h"

/* Essa funcao eh responsavel por iniciar tudo que eh necessario para o Allegro,
 * e caso algo nao consiga ser inicializado, ela imprime no stderr o que nao foi
 * inicializado e termina o programa com exit(CODIGO). Esses codigos estao definidos
 * no header constants.h*/
void initialize_allegro();

/* Essa funcao se certifica de que o ponteiro passado nao eh nulo e, caso seja,
 * termina o programa com exit(erro).
 * Parametros:
 * p:       ponteiro a ser analisado.
 * message: mensagem de erro.
 * error:   erro do tipo ERROS_ALLEGRO que o usuario deseja que seja emitido se o ponteiro for nulo.
 */
void assert_pointer_not_null(void* p, const char* message, enum ERROS_ALLEGRO error);

#endif
