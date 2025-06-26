#include <allegro5/blender.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>

#include <math.h>
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
  ALLEGRO_FONT* font_score =          NULL;
  ALLEGRO_FONT* font_points_warning = NULL;
  ALLEGRO_FONT* font_menu =           NULL;
  ALLEGRO_BITMAP* logo_img =          NULL;
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

  font_score = al_load_ttf_font("fonts/ARIAL.TTF", 40, 0);
  assert_pointer_not_null(font_score, "Nao consegui criar a fonte!\n", NAO_CONSEGUI_CRIAR_A_FONTE);

  font_points_warning = al_load_ttf_font("fonts/Minecraft.ttf", 10, 0);
  assert_pointer_not_null(font_points_warning, "Nao consegui criar a fonte dos points warning!\n", NAO_CONSEGUI_CRIAR_A_FONTE);

  font_menu = al_load_ttf_font("fonts/Minecraft.ttf", 25, 0);
  assert_pointer_not_null(font_menu, "Nao consegui criar a fonte para o menu!", NAO_CONSEGUI_CRIAR_A_FONTE);

  logo_img = al_load_bitmap("img/logo.png");
  assert_pointer_not_null(logo_img, "Nao consegui abrir a imagem da logo!", ERRO_ABERTURA_IMAGEM);

  al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

  character player = create_player();
  character player_bullet = create_player_bullet();
  enemies all_enemies = create_enemies();
  background curr_background = create_background(al_map_rgb(BG_R, BG_G, BG_B), player);

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_keyboard_event_source());

  bool redraw = true;
  bool done = false;
  ALLEGRO_EVENT event;
  enum CURRENT_SCREEN curr_screen = MENU;

  int64_t start_frame = 0;
  int64_t curr_frame;
  const char* opcoes[3] = {"Iniciar jogo", "Como jogar", "Deletar save"};
  int curr_opcao = 0;
  int startY = 600;

  al_start_timer(timer);

  while(!done){

    al_wait_for_event(queue, &event);
    //printf("Tempo: %ld\n", al_get_timer_count(timer));
    curr_frame = al_get_timer_count(timer);

    switch(event.type){

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
          done = true;

        break;

    }

    if(curr_screen == MENU){

      switch(event.type){

        case ALLEGRO_EVENT_KEY_DOWN:

          if(curr_frame <= FPS_FADE_LOGO)
            break;

          if(event.keyboard.keycode == ALLEGRO_KEY_UP)
            curr_opcao = (curr_opcao == 0) ?  2 : curr_opcao-1;

          else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            curr_opcao = (curr_opcao == 2) ? 0 : curr_opcao+1;

          else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){

            start_frame = curr_frame;

            if(curr_opcao == GAME_OPTION)
              curr_screen = GAME;

            else if(curr_opcao == HOW_TO_PLAY)
              curr_screen = HOW_TO_PLAY_SCREEN;

            else if(curr_opcao == DELETE_SAVE)
              curr_screen = SAVE_DELETED;

          }

          break;

        case ALLEGRO_EVENT_TIMER:
          
          redraw = true;

          for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_NOT_SEEN;

          break;

      }

      if(redraw && al_is_event_queue_empty(queue)){

        redraw = false;

        if(curr_frame > FPS_FADE_LOGO){

          al_clear_to_color(al_map_rgb(0, 0, 0));
          al_draw_textf(font_menu, al_map_rgb(255, 255, 255), WIDTH_RES/2, 60, ALLEGRO_ALIGN_CENTER, "Use as setas e o enter para selecionar a opcao.");
          al_draw_bitmap(logo_img, WIDTH_RES*0.18f, HEIGHT_RES*0.2f, 0);

          for(int i = 0; i < 3; i++){
  
            if(curr_opcao == i){

              al_draw_filled_rectangle(WIDTH_RES*0.4, startY + (i+1)*60-20, WIDTH_RES*0.6, startY + (i+1)*60 + 40, al_map_rgb(255, 255, 255));
              al_draw_text(font_menu, al_map_rgb(0, 0, 0), WIDTH_RES/2, startY + (i+1)*60, ALLEGRO_ALIGN_CENTER, opcoes[i]);

            }

            else
              al_draw_text(font_menu, al_map_rgb(255, 255, 255), WIDTH_RES/2, startY + (i+1)*60, ALLEGRO_ALIGN_CENTER, opcoes[i]);

          }

          al_flip_display();

        }

        else{

          al_draw_tinted_bitmap(logo_img, al_map_rgba_f(1, 1, 1, pow(curr_frame/((float)FPS_FADE_LOGO), 4)), WIDTH_RES*0.18f, HEIGHT_RES*0.2f, 0);
          al_flip_display();

        }
      }

    }

    else if(curr_screen == HOW_TO_PLAY_SCREEN){


      //printf("eita %d\n", curr_frame);

      switch(event.type){

        case ALLEGRO_EVENT_TIMER:
          redraw = true;
          break;

        case ALLEGRO_EVENT_KEY_DOWN:
          if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            curr_screen = MENU;

          break;

      }

      if(redraw && al_is_event_queue_empty(queue)){

        redraw = false;
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_multiline_textf(font_menu, al_map_rgb(255, 255, 255), WIDTH_RES/2, HEIGHT_RES*0.5, WIDTH_RES, 0, ALLEGRO_ALIGN_CENTER, "Use as setas para controlar e espaco para atirar!\nAperte enter para voltar pro menu.");
        al_flip_display();

      }

    }

    else if(curr_screen == SAVE_DELETED){

      delete_save(&curr_background);

      switch(event.type){

        case ALLEGRO_EVENT_TIMER:
          redraw = true;
          break;

      }

      if(redraw && al_is_event_queue_empty(queue)){

        redraw = false;
        al_draw_textf(font_menu, al_map_rgb(255, 255, 255), WIDTH_RES/2, HEIGHT_RES*0.9, ALLEGRO_ALIGN_CENTER, "Save deletado!");
        al_flip_display();

      }

      if(curr_frame-start_frame > 60)
        curr_screen = MENU;

    }

    else if(curr_screen == GAME){

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

          for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_NOT_SEEN;

          redraw = true;

          break;

      }

      if(redraw && al_is_event_queue_empty(queue)){

        redraw = false;

        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_background(&curr_background, font_score, font_points_warning);
        draw_player(&player);
        draw_bullet(&player_bullet, &all_enemies, &curr_background);
        draw_enemies(all_enemies);

        al_flip_display();

      }

    }

  }

  destroy_player(&player);
  close_background(&curr_background);
  destroy_enemies(&all_enemies);

  al_destroy_bitmap(logo_img);

  al_destroy_font(font_score);
  al_destroy_font(font_points_warning);
  al_destroy_font(font_menu);

  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_display(disp);

  return 0;

}
