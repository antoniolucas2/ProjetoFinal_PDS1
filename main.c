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

  character* player = create_character(WIDTH_RES*0.45, HEIGHT_RES*0.8, WIDTH_RES*0.55, HEIGHT_RES*0.95, PLAYER, RECTANGLE);
  assert_pointer_not_null(player, "Erro na criacao do personagem", ERRO_CRIACAO_PLAYER);

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


        if(key[ALLEGRO_KEY_LEFT]){

          if(player->posX1-DEFAULT_SPEED > 0){
            player->posX1 -= DEFAULT_SPEED;
            player->posX2 -= DEFAULT_SPEED;
          }

          else{

            player->posX2 -= player->posX1;
            player->posX1 = 0;

          }

        }

        if(key[ALLEGRO_KEY_RIGHT]){

          if(player->posX2 + DEFAULT_SPEED < WIDTH_RES){
            player->posX1 += DEFAULT_SPEED;
            player->posX2 += DEFAULT_SPEED;
          }

          else{

            player->posX1 += (WIDTH_RES-player->posX2);
            player->posX2 = WIDTH_RES;

          }

        }

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
      
      if(player->typeShowing == RECTANGLE){

        al_draw_filled_rectangle(player->posX1, player->posY1,
                                 player->posX2, player->posY2,
                                 al_map_rgb(0, 60, 70));

        printf("A area do retangulo ta %.3f\n", (player->posX2-player->posX1)*(player->posY2-player->posY1));
        
      }

      al_flip_display();

    }

  }

  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_display(disp);

  player = destruct_character(player);

  return 0;

}
