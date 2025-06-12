#include <allegro5/allegro.h>

#include <stdbool.h>
#include <stdio.h>

#include "initialize.h" 
#include "constants.h"

void initialize_allegro(){

  if(!al_init()){

    fprintf(stderr, "Nao consegui iniciar o Allegro!\n");
    exit(ALLEGRO_NAO_INICIOU);

  }

  if(!al_install_keyboard()){

    fprintf(stderr, "Nao consegui instalar o teclado!\n");
    exit(TECLADO_NAO_FOI_INSTALADO);

  }

}
