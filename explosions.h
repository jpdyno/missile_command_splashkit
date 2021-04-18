// Missile Command
// JP Karnilowicz
// explosions.h
// definitions for explosions.cpp

#ifndef MISSLE_COMMAND_EXPLOSIONS
#define MISSLE_COMMAND_EXPLOSIONS

#include "splashkit.h"

// explosion data structure
struct explosion_data
{
    sprite explosion_sprite; // sprite for explosion
};

/**  creates a new explosion_data and sets default values
 *  @param missile_team   was this explosions caused by a PLAYER or ENEMY missile
 *  @param origin_xy   Centre point of explosion
 *  @param bonus_tracker
 *  @returns a new explosion_data
 */
explosion_data create_explosion(team missile_team, point_2d origin_xy, int increase_missile_size);

/**  creates explosion at location, adds it to game.
 *  @param explosions   vector of explosions to add to
 *  @param missile_team   was this explosions caused by a PLAYER or ENEMY missile
 *  @param origin_xy   Centre point of explosion
 *  @param bonus_tracker
 */
void add_explosion(vector<explosion_data> &explosions, team missile_team, point_2d explosion_xy, int increase_missile_size);

/**  deletes explosion from vector
 *  @param explosions   vector containing explosion
 *  @param index   vector index of explosion to explode
 */
void delete_explosion(vector<explosion_data> &explosions, int index);

/**  draws explosions to screen
 *  @param missiles   vector of explosions to draw to screen
 */
void draw_explosions(const vector<explosion_data> &explosions);

/**  updates explosions data
 *  @param explosions   vector of explosions to update
 */
void update_explosions(vector<explosion_data> &explosions);

#endif