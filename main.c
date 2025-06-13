#include <stdio.h>
#include <stdbool.h>

#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "constants.h"
#include "initialize.h"
#include "character.h"
#include "player.h"

int main(){

  initialize_allegro();

  ALLEGRO_EVENT_QUEUE* queue =        NULL;
  ALLEGRO_FONT* font =                NULL;
  ALLEGRO_TIMER* timer =              NULL;
  ALLEGRO_DISPLAY* disp =             NULL;
  ALLEGRO_AUDIO_STREAM* audioStream = NULL;

  unsigned char key[ALLEGRO_KEY_MAX];
  memset(key, 0, sizeof(key));

  queue = al_create_event_queue();
  assert_pointer_not_null(queue, "Erro na criacao da fila", ERRO_CRIACAO_FILA);

  timer = al_create_timer(1.0/FPS); 
  assert_pointer_not_null(timer, "Erro na criacao do timer", ERRO_CRIACAO_FILA);

  disp = al_create_display(WIDTH_RES, HEIGHT_RES);
  assert_pointer_not_null(disp, "Erro na criacao do display", ERRO_CRIACAO_DISPLAY);

  character player = create_player();

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_keyboard_event_source());

  bool redraw = true;
  bool done = false;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  while(1){

    al_wait_for_event(queue, &event);

    switch(event.type){

      case ALLEGRO_EVENT_KEY_DOWN:
        key[event.keyboard.keycode] = KEY_NOT_SEEN | KEY_DOWN;
        break;

      case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= ~KEY_DOWN;
        break;

      case ALLEGRO_EVENT_TIMER:


        if(key[ALLEGRO_KEY_LEFT])
          move_player_left(&player);

        if(key[ALLEGRO_KEY_RIGHT])
          move_player_right(&player);

        if(key[ALLEGRO_KEY_ESCAPE])
          done = true;

        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= ~KEY_NOT_SEEN;

        redraw = true;

        break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;

    }

    if(done)
      break;

    if(redraw && al_is_event_queue_empty(queue)){

      redraw = false;

      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw_player(&player);
      
      al_flip_display();

    }

  }

  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_display(disp);

  return 0;

}
