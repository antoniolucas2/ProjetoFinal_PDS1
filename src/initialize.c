#include <allegro5/allegro.h>

#include <stdbool.h>
#include <stdio.h>

void initialize_allegro(){

  if(!al_init()){

    fprintf(stderr, "Nao consegui iniciar o Allegro!\n");
    exit(1);

  }

  if(!al_install_keyboard()){

    fprintf(stderr, "Nao consegui instalar o teclado!\n");
    exit(1);

  }

}
