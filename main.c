#include <allegro5/keycodes.h>
#include <allegro5/timer.h>
#include <stdio.h>
#include <stdbool.h>

#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

#include "constants.h"
#include "initialize.h"
#include "character.h"
#include "player.h"
#include "enemies.h"
#include "bullet.h"
#include "background.h"

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

  font = al_load_ttf_font("fonts/ARIAL.TTF", 40, 0);
  assert_pointer_not_null(font, "Nao consegui criar a fonte!\n", NAO_CONSEGUI_CRIAR_A_FONTE);

  character player = create_player();
  character player_bullet = create_player_bullet();
  enemies all_enemies = create_enemies();
  background curr_background = create_background(al_map_rgb(BG_R, BG_G, BG_B), player);
  enum TYPE_CHARACTER enemy_hit;

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_keyboard_event_source());

  bool redraw = true;
  bool done = false;
  ALLEGRO_EVENT event;

  int64_t start_frame = 0;

  al_start_timer(timer);

  while(1){

    al_wait_for_event(queue, &event);
    printf("Tempo: %ld\n", al_get_timer_count(timer));

    if(al_get_timer_count(timer) - start_frame >= TOTAL_FRAMES_TO_MOVE){

      move_enemies(&all_enemies);
      done = enemy_on_background(&curr_background, all_enemies);

      start_frame = al_get_timer_count(timer);
      redraw = true;

    }

    done = done | player_enemy_touch(&all_enemies, &player);

    switch(event.type){

      case ALLEGRO_EVENT_KEY_DOWN:

        if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)
          try_shooting_player_bullet(&player_bullet, &player);

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
      draw_background(&curr_background, font);
      draw_player(&player);
      draw_enemies(all_enemies);
      enemy_hit = draw_bullet(&player_bullet, &all_enemies);

      if(enemy_hit == ENEMY_100)
        curr_background.totalScore += 100;

      else if(enemy_hit == ENEMY_250)
        curr_background.totalScore += 250;

      else if(enemy_hit == ENEMY_500)
        curr_background.totalScore += 500;

      printf("sai total ue\n");
      
      al_flip_display();
      printf("flipei o display\n");

    }

  }

  save_and_close_save_file(&curr_background);

  destroy_enemies(&all_enemies);

  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_display(disp);

  return 0;

}
