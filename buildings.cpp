// Missile Command
// JP Karnilowicz
// buildings.cpp
// procedures and functions relating to creating, updating and drawing the building objects in game

#include "game.h"

building_data create_building(int location) // create a new game
{
    building_data new_building; // create new buildings to add into game_data

    double y;               // y position of buildings
    double x;               // x position of first building
    bitmap building_bitmap; // building bitmap

    new_building.location = location;                                  // give building it's location
    building_bitmap = bitmap_named("building_" + to_string(location)); // load default building bitmap into variable
    new_building.building_sprite = create_sprite(building_bitmap);     // assign default building bitmap sprite

    switch (location) // apply appropriate location of building along x axis
    {
    case 1:                                                       //  First location
        x = 75;                                                   //  100 pixels from left edge
        break;                                                    //
    case 2:                                                       //  Second locationg
        x = 250;                                                  //  250 pixels from left edge
        break;                                                    //
    case 3:                                                       //  Third location
        x = 400;                                                  //  400 pixels from left edge
        break;                                                    //
    case 4:                                                       //  Fourth location
        x = screen_width() - bitmap_width(building_bitmap) - 400; //  400 pixels from right edge
        break;                                                    //
    case 5:                                                       //  Fifth location
        x = screen_width() - bitmap_width(building_bitmap) - 250; //  250 pixels from right edge
        break;                                                    //
    default:                                                      //  Sixth
        x = screen_width() - bitmap_width(building_bitmap) - 75;  //  100 pixels from right edge
        break;                                                    //
    }                                                             //
    sprite_set_x(new_building.building_sprite, x);                // Assign x position of building

    y = screen_height() - bitmap_height(building_bitmap) - 64; // Place all buildings at bottom of screen, with 64 pixel buffer for the ground
    sprite_set_y(new_building.building_sprite, y);             // Assign y position of building

    new_building.destroyed = false; // new building is not destroyed

    return new_building; // return new building data
}

void draw_buildings(const vector<building_data> &buildings)
{
    for (int i = 0; i < buildings.size(); i++)     // interate to draw all buildings
    {                                              //
        draw_sprite(buildings[i].building_sprite); // draw appropriate sprite
    }
}

void building_sprite_destroyed(building_data &building)
{
    if (!building.destroyed)                                              // If building has beent tagged destroyed
    {                                                                     //
        bitmap building_destroyed_bitmap;                                 // new building destroyed bitmap
        sprite building_destroyed_sprite;                                 // new building destroyed sprite
        point_2d building_xy = sprite_position(building.building_sprite); // get position of old building sprite

        building_destroyed_bitmap = bitmap_named("building_" + to_string(building.location) + "_destroyed"); // load building destroyed bitmap into variable
        building_destroyed_sprite = create_sprite(building_destroyed_bitmap);                                // create new sprite from building destroyed bitmap
        building_xy.y = screen_height() - bitmap_height(building_destroyed_bitmap) - 64;                     // compensate y axis position, since building destroyed sprite is shorter than the default building sprite
        sprite_set_position(building_destroyed_sprite, building_xy);                                         // load compensated coords into building destroyed sprite

        building.building_sprite = building_destroyed_sprite; // replace building sprite with building destroyed sprite
    }
}

int buildings_still_standing(const vector<building_data> &buildings)
{
    int count = 0; // start counter at zero

    for (int i = 0; i < buildings.size(); i++) // loop through building vector
    {                                          //
        if (!buildings[i].destroyed)           // if buidling is not tagged as destroyed
        {                                      //
            count++;                           // add to count
        }
    }
    return count;
}
