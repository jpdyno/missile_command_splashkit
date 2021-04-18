// Missile Command
// JP Karnilowicz
// explosions.cpp
// functions and procedures relating to explosions in game


#include "game.h"

explosion_data create_explosion(team missile_team, point_2d origin_xy, int increase_missile_size) // create a new explosion data with default values
{
    explosion_data new_explosion;                                     // new explosion_data
    bitmap explosion_bitmap = bitmap_named("explosion");              // get bitmap
    new_explosion.explosion_sprite = create_sprite(explosion_bitmap); // create explosion sprite

    sprite_set_x(new_explosion.explosion_sprite, origin_xy.x - (bitmap_width(explosion_bitmap) / 2));  // set explosion origin x (compensate for bitmap size)
    sprite_set_y(new_explosion.explosion_sprite, origin_xy.y - (bitmap_height(explosion_bitmap) / 2)); // set explosion origin y (compensate for bitmap size)

    if (missile_team == PLAYER and increase_missile_size > 0)          // If missile size bonus is applied
    {                                                                                //
        sprite_set_scale(new_explosion.explosion_sprite, PLAYER_MISSILE_SIZE_BONUS); // increase missile explosions scale
    }

    return new_explosion; // return new_explosions data
}

void add_explosion(vector<explosion_data> &explosions, const team missile_team, const point_2d explosion_xy, int increase_missile_size) // adds new explosion to game
{
    explosion_data new_explosion;                                                // new explosion_data
    new_explosion = create_explosion(missile_team, explosion_xy, increase_missile_size); // create new explosion with passed in information
    explosions.push_back(new_explosion);                                         // insert explosion into game
}

void delete_explosion(vector<explosion_data> &explosions, int index)
{
    int last_index = explosions.size() - 1;     // get last index in dynamic array
    explosions[index] = explosions[last_index]; // move explosion from last index into index of explosion being removed (overwriting)
    explosions.pop_back();                      // delete last index in dynamic array
}

void draw_explosions(const vector<explosion_data> &explosions)
{
    for (int i = 0; i < explosions.size(); i++)      // loop through and draw all explosions in game
    {                                                //
        draw_sprite(explosions[i].explosion_sprite); // draw sprites
    }
}

void update_explosions(vector<explosion_data> &explosions)
{
    for (int i = 0; i < explosions.size(); i++)                                                  // loop through all explosions in game
    {                                                                                            //
        update_sprite(explosions[i].explosion_sprite);                                           // update sprite first, since explosion may be deleted if scale shrinks enough
                                                                                                 //
        float rotation = sprite_rotation(explosions[i].explosion_sprite);                        // get rotation of explosion sprite
        sprite_set_rotation(explosions[i].explosion_sprite, rotation - EXPLOSION_ROTATION_RATE); // and decrement by EXPLOSION_ROTATION_RATE (to make a cool spinny effect)
                                                                                                 //
        float scale = sprite_scale(explosions[i].explosion_sprite);                              // get scale of explosion sprite

        if (scale > 0)                                                                       // if sprite is still big enough to see
        {                                                                                    //
            sprite_set_scale(explosions[i].explosion_sprite, scale - EXPLOSION_SHRINK_RATE); // Shrink sprite by EXPLOSION_SHRINK_RATE
        }                                                                                    //
        else                                                                                 // otherwise sprite is now too small to be visible
        {                                                                                    //
            delete_explosion(explosions, i);                                                 // delete explosion
        }
    }
}