// Missile Command
// JP Karnilowicz
// missiles.cpp
// procedures and functions relating to the control of all missiles in game

#include "game.h"

missile_data create_missile(team missile_team, point_2d origin_xy, point_2d target_xy, const applied_bonus_tracker &bonus_tracker) // create a new missle data with default values
{
    missile_data new_missile; // new missile_data
    int missile_speed;        // integer for missile speed
    bitmap target_bitmap;     // bitmap for target
    bitmap missile_bitmap;    // bitmap for missile

    new_missile.missile_team = missile_team; // allocate missile to player or enemy
    new_missile.origin_xy = origin_xy;       // load in origin coordinates
    new_missile.target_xy = target_xy;       // load in target coordinates

    if (missile_team == ENEMY)                              // If missile is an enemy missile
    {                                                       //
        target_bitmap = bitmap_named("target_trans");       // give enemy target sprite
        missile_bitmap = bitmap_named("missile_small_red"); // give enemy missile sprite
        missile_speed = ENEMY_MISSILE_SPEED;                // set missile speed at enemy missile speed
    }
    else                                             // Otherwise missile must be a player
    {                                                //
        target_bitmap = bitmap_named("target_blue"); // give player target sprite

        if (bonus_tracker.increase_missile_size > 0)             // if missile size bonus is applied
        {                                                        //
            missile_bitmap = bitmap_named("missile_large_blue"); // use larger missile sprite
        }                                                        //
        else                                                     // otherwise
        {                                                        //
            missile_bitmap = bitmap_named("missile_small_blue"); // use regular missile sprite
        }

        if (bonus_tracker.increase_missile_speed > 0)   // If missile speed bonus is applied
        {                                               //
            missile_speed = PLAYER_MISSILE_SPEED_BONUS; // set bonus missile speed
        }                                               //
        else                                            // otherwise
        {                                               //
            missile_speed = PLAYER_MISSILE_SPEED;       // set reguler missile speed
        }
    }

    new_missile.target_sprite = create_sprite(target_bitmap);                                  // create missile sprite
    sprite_set_x(new_missile.target_sprite, target_xy.x - (bitmap_width(target_bitmap) / 2));  // set target at x (compensate for bitmap size)
    sprite_set_y(new_missile.target_sprite, target_xy.y - (bitmap_height(target_bitmap) / 2)); // set target at y (compensate for bitmap size)

    new_missile.missile_sprite = create_sprite(missile_bitmap);                                  // create missile sprite
    double rotation = find_angle(origin_xy, target_xy);                                          // find angle to rotate missile sprite
    sprite_set_rotation(new_missile.missile_sprite, rotation);                                   // rotate missile sprite
    sprite_set_x(new_missile.missile_sprite, origin_xy.x - (bitmap_width(missile_bitmap) / 2));  // set missile at origin x  (compensate for bitmap size)
    sprite_set_y(new_missile.missile_sprite, origin_xy.y - (bitmap_height(missile_bitmap) / 2)); // set missile at origin y  (compensate for bitmap size)

    sprite_set_dx(new_missile.missile_sprite, missile_speed); // set missile movement speed

    return new_missile; // return new_launcher data
}

void add_missile(vector<missile_data> &missiles, team missile_team, point_2d origin_xy, point_2d target_xy, const applied_bonus_tracker &bonus_tracker) // adds new missile to game
{
    missile_data new_missile;                                                        // new missile_data
    new_missile = create_missile(missile_team, origin_xy, target_xy, bonus_tracker); // create new missile with passed in team, origin, target and bonuses
    missiles.push_back(new_missile);                                                 // insert missile into game
}

void delete_missile(vector<missile_data> &missiles, int index)
{
    int last_index = missiles.size() - 1;   // get last index in dynamic array
    missiles[index] = missiles[last_index]; // move missile from last index into index of missile being removed (overwriting)
    missiles.pop_back();                    // delete last index in dynamic array
}

void draw_missiles(const vector<missile_data> &missiles)
{
    for (int i = 0; i < missiles.size(); i++)    // loop through and draw all missiles in game
    {                                            //
        draw_sprite(missiles[i].missile_sprite); // draw missile
        draw_sprite(missiles[i].target_sprite);  // draw target
    }
}

void generate_enemy_missile(vector<missile_data> &missiles, const applied_bonus_tracker &bonus_tracker)
{
    point_2d origin_xy = point_at(rnd(50, screen_width() - 50), -20);                  // pick random missile origin, just above visible screen
    point_2d target_xy = point_at(rnd(50, screen_width() - 50), screen_height() - 96); // pick random target, at building level
    add_missile(missiles, ENEMY, origin_xy, target_xy, bonus_tracker);                 // add enemy missile to the game
}

void update_missiles(vector<missile_data> &missiles)
{                                                // X and Y coordinates of screen boundary at which to delete missle from game
    int X_boundary_left = -100;                  // X left, delete 100 pixels off screen.
    int X_boundary_right = screen_width() + 100; // X right, delete 100 pixels off screen.
    int Y_boundary_top = -100;                   // Y top is given a bit of extra space wherein to create enemy missiles off screen

    for (int i = 0; i < missiles.size(); i++)      // loop through and draw all missiles in game
    {                                              //
        update_sprite(missiles[i].missile_sprite); // update sprite

        // The below checks if missiles go offscreen,
        // technically shouldn't happen anymore as they should explode when they hit their target but leaving this in as a precaution
        if ((sprite_x(missiles[i].missile_sprite) < X_boundary_left) or  // if missile leaves left side of screen or
            (sprite_x(missiles[i].missile_sprite) > X_boundary_right) or // if missile leaves right side of screen or
            (sprite_y(missiles[i].missile_sprite) < Y_boundary_top))     // if missile leaves top of screen or
        {                                                                //
            delete_missile(missiles, i);                                 // Then deletes missiles
        }                                                                //
    }
}