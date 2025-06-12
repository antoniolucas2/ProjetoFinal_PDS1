#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "initialize.h"

int main(){

  initialize_allegro();

  ALLEGRO_EVENT_QUEUE* queue =        NULL;
  ALLEGRO_FONT* font =                NULL;
  ALLEGRO_TIMER* timer =              NULL;
  ALLEGRO_DISPLAY* disp =             NULL;
  ALLEGRO_AUDIO_STREAM* audioStream = NULL;

  return 0;

}
