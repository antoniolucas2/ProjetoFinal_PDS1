#ifndef BULLET_HEADER

#define BULLET_HEADER

#include "character.h"
#include "enemies.h"
#include "background.h"

#include <allegro5/allegro_audio.h>

character create_player_bullet();
void try_shooting_player_bullet(character* player_bullet, character* player, ALLEGRO_SAMPLE* spl);
enum TYPE_CHARACTER draw_bullet(character* bullet, enemies* all_enemies, background* curr_background, ALLEGRO_SAMPLE* enemy_death);

#endif
