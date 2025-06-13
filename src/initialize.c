#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <stdbool.h>
#include <stdio.h>

#include "initialize.h" 
#include "constants.h"

/* Essa funcao eh responsavel por iniciar tudo que eh necessario para o Allegro,
 * e caso algo nao consiga ser inicializado, ela imprime no stderr o que nao foi
 * inicializado e termina o programa com exit(CODIGO). Esses codigos estao definidos
 * no header constants.h*/
void initialize_allegro(){

  if(!al_init()){

    fprintf(stderr, "Nao consegui iniciar o Allegro!\n");
    exit(ALLEGRO_NAO_INICIOU);

  }

  if(!al_install_keyboard()){

    fprintf(stderr, "Nao consegui instalar o teclado!\n");
    exit(TECLADO_NAO_FOI_INSTALADO);

  }

  if(!al_init_image_addon()){

    fprintf(stderr, "Nao consegui iniciar o addon de imagens!\n");
    exit(ERRO_ADDON_IMAGENS);

  }

  if(!al_install_audio()){

    fprintf(stderr, "Nao consegui instalar o audio!\n");
    exit(ERRO_INSTALACAO_AUDIO);

  }

  if(!al_init_acodec_addon()){

    fprintf(stderr, "Nao consegui iniciar os codecs de audio!\n");
    exit(ACODECS_NAO_INICIOU);

  }

  if(!al_reserve_samples(TOTAL_AUDIO_SAMPLES)){

    fprintf(stderr, "Nao consegui reservar os %d samples de audio!\n", TOTAL_AUDIO_SAMPLES);
    exit(ERRO_RESERVA_SAMPLES);

  }

  if(!al_init_primitives_addon()){

    fprintf(stderr, "Nao consegui iniciar o addon dos primitives!\n");
    exit(PRIMITIVES_NAO_INICIARAM);

  }
  
}

/* Essa funcao se certifica de que o ponteiro passado nao eh nulo e, caso seja,
 * termina o programa com exit(erro).
 * Parametros:
 * p:       ponteiro a ser analisado.
 * message: mensagem de erro.
 * error:   erro do tipo ERROS_ALLEGRO que o usuario deseja que seja emitido se o ponteiro for nulo.
 */
void assert_pointer_not_null(void* p, const char* message, enum ERROS_ALLEGRO error){

  if(!p){

    fprintf(stderr, "%s", message);
    exit(error);

  }

}
