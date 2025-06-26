#ifndef BULLET_HEADER

#define BULLET_HEADER

#include "character.h"
#include "enemies.h"
#include "background.h"

character create_player_bullet();
void try_shooting_player_bullet(character* player_bullet, character* player);
enum TYPE_CHARACTER draw_bullet(character* bullet, enemies* all_enemies, background* curr_background);

#endif
