// Missile Command
// JP Karnilowicz
// buildings.h
// Definitions for buildings.cpp


#ifndef MISSLE_COMMAND_BUILDINGS
#define MISSLE_COMMAND_BUILDINGS
#include "splashkit.h"

// Building data structure
struct building_data
{
    int location;                     // location of building (1-6)
    sprite building_sprite;           // appropriate sprite for building
    sprite building_destroyed_sprite; // appropriate sprite for building when destroyed
    bool destroyed;                   // is this building destroyed?
};

/**  Creates a new building data
 *  @param location   Location of building on screen (1-6)
 *  @returns   New building data
 */
building_data create_building(int location);

/**  Updates buildings
 *  @param buildings   Vector of building_data to draw
 */
void draw_buildings(const vector<building_data> &buildings);

/**  Changes building sprite to show building destroyed
 *  @param building   Building to change
 */
void building_sprite_destroyed(building_data &building);

/**  counts how many buildings are still standing.
 *  @param buildings   Vector of buildings to go through
 *  @returns   A count of how many buildings are still standing
 */
int buildings_still_standing(const vector<building_data> &buildings);

#endif