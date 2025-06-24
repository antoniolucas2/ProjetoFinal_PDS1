#ifndef BULLET_HEADER

#define BULLET_HEADER

#include "character.h"
#include "enemies.h"

character create_player_bullet();

void try_shooting_player_bullet(character* player_bullet, character* player);

void draw_bullet(character* bullet, enemies* all_enemies);

#endif
