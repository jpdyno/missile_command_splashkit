// Missile Command
// JP Karnilowicz
// bonuses.h
// definitions for bonuses.cpp

#ifndef MISSLE_COMMAND_BONUSES
#define MISSLE_COMMAND_BONUSES

#include "splashkit.h"

// Types of bonus available
enum bonus_type
{
    INCREASE_RELOAD_SPEED,  // allows player to shoot more missiles quicker
    INCREASE_MISSILE_SPEED, // makes players missiles travel faster
    INCREASE_MISSILE_SIZE,  // makes players missiles and explosions bigger
    CLEAR_SCREEN,           // gives player the ability to explode all missiles on screen.
};

// Game bonus structure, for the bonus icons floating on screen
struct bonus_data
{
    sprite bonus_sprite; // bonus sprite
    bonus_type type;     // bonus type
};

// Applied bonus tracker structure, used to track all applied bonuses in game
struct applied_bonus_tracker
{
    int increase_reload_speed = 0;  // countdown for how long reload is applied (60 = 1 second)
    int increase_missile_speed = 0; // countdown for how long speed is applied (60 = 1 second)
    int increase_missile_size = 0;  // countdown for how long size is applied (60 = 1 second)
    bool clear_screen = false;      // true if player has ability to clear screen
};

/**  creates a new bonus_data with random type
 * @returns a new bonus_data populated with infomation
 */
bonus_data create_bonus();

/**  creates a new bonus and adds it to the game for the player to collect
 *  @param bonuses   vector of bonuses to add to
 */
void add_bonus(vector<bonus_data> &bonuses);

/**  deletes bonus data from game
 *  @param bonuses   vector of bonuses to delete from
 *  @param index   index of bonus to detel
 */
void delete_bonus(vector<bonus_data> &bonuses, int index);

/**  draws bonuses to screen
 *  @param bonuses   vector of bonuses to draw
 */
void draw_bonuses(const vector<bonus_data> &bonuses);

/**  updates bonuses on screen
 *  @param bonuses   vector of bonuses to update
 */
void update_bonuses(vector<bonus_data> &bonuses);

/**  Applies bonuses to game
 *  @param bonus_tracker   tracker of bonuses applied
 *  @param type   bonus type to apple
 */
void apply_bonus(applied_bonus_tracker &bonus_tracker, bonus_type type);

/**  decrements countdowns for applied bonuses
 *  @param bonus_tracker   tracker of bonuses to countdown
 */
void decrement_bonus_tracker(applied_bonus_tracker &bonus_tracker);

#endif