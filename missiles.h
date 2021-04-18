// Missile Command
// JP Karnilowicz
// missiles.h
// definitions for missiles.cpp

#ifndef MISSLE_COMMAND_MISSILES
#define MISSLE_COMMAND_MISSILES
#include "splashkit.h"

// small enum to allocate teams to missiles
enum team
{
    PLAYER,
    ENEMY
};

// Missile data structure
struct missile_data
{
    team missile_team;     // allocate missile to player or enemy
    sprite missile_sprite; // appropriate sprite for missile
    sprite target_sprite;  // appropriate sprite for target
    point_2d origin_xy;    // missile origin coordinates
    point_2d target_xy;    // missile target coordinates
};

/**  creates a new missle and sets default values
 *  @param missile_team   allocate missile to PLAYER or ENEMY
 *  @param origin_xy   Centre point of missle origin
 *  @param target_xy   Centre point of missle target
 *  @param bonus_tracker   game bonus tracker, to know if require to apply any bonus attributes to new missile
 *  @returns a new missile_data complete with details
 */
missile_data create_missile(team missile_team, point_2d origin_xy, point_2d target_xy, const applied_bonus_tracker &bonus_tracker);

/**  creates a new missle_data and sets default values
 *  @param missiles   vector containing missile
 *  @param missile_team   allocate missile to PLAYER or ENEMY
 *  @param origin_xy   Centre point of missle origin
 *  @param target_xy   Centre point of missle target
 *  @param bonus_tracker   game bonus tracker, to know if require to apply any bonus attributes to new missile
 */
void add_missile(vector<missile_data> &missiles, team missile_team, point_2d origin_xy, point_2d target_xy, const applied_bonus_tracker &bonus_tracker);

/**  deletes missile from vector
 *  @param missiles   vector containing missile
 *  @param index   vector index of missile to delete
 */
void delete_missile(vector<missile_data> &missiles, int index);

/**  draws missiles to screen
 *  @param missiles   vector of missiles to draw to screen
 */
void draw_missiles(const vector<missile_data> &missiles);

/**  creates a new enemy missle and adds it to the game
 *  @param missiles   vector containing missile
 */
void generate_enemy_missile(vector<missile_data> &missiles, const applied_bonus_tracker &bonus_tracker);

/**  updates missile data
 *  @param missiles   vector of missiles to update
 */
void update_missiles(vector<missile_data> &missiles);

#endif