#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "constants.h"
#include "initialize.h"
#include "character.h"

int main(){

  initialize_allegro();

  ALLEGRO_EVENT_QUEUE* queue =        NULL;
  ALLEGRO_FONT* font =                NULL;
  ALLEGRO_TIMER* timer =              NULL;
  ALLEGRO_DISPLAY* disp =             NULL;
  ALLEGRO_AUDIO_STREAM* audioStream = NULL;

  queue = al_create_event_queue();
  assert_pointer_not_null(queue, "Erro na criacao da fila", ERRO_CRIACAO_FILA);

  character* player = create_character(0, 0, 6, 6, PLAYER, RECTANGLE);
  assert_pointer_not_null(player, "Erro na criacao do personagem", ERRO_CRIACAO_PLAYER);

  player = destruct_character(player);

  return 0;

}
