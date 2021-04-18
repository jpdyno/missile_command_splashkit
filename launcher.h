// Missile Command
// JP Karnilowicz
// launcher.h
// Definitions for launcher.cpp


#ifndef MISSLE_COMMAND_LAUNCHER
#define MISSLE_COMMAND_LAUNCHER
#include "splashkit.h"

// Missle launcher data structure
struct launcher_data
{
    sprite sprite;        // appropriate sprite for launcher
    point_2d launcher_xy; // launcher location on screen
    int reload_countdown; // countdown time to be able to reload again
};

/**  Creates a new missile launcher
 *  @returns   New missile launcher data
 */
launcher_data create_launcher();

/**  Finds the target angle
 *  @param origin_xy   Centre point of origin
 *  @param target_xy   Centre point of target
 *  @returns   the angle between Y axis and line from origin to target.
 */
double find_angle(point_2d origin_xy, point_2d target_xy);

/**  Draws the missile launcher
 *  @param launcher   launcher_data to draw from
 */
void draw_launcher(const launcher_data &launcher);

/**  Updates missile launcher
 *  @param launcher   data to update
 */
void update_launcher(launcher_data &launcher);

#endif