// Missile Command
// JP Karnilowicz
// bonuses.cpp
// functions and procedures relating to in game bonuses

#include "game.h"

bonus_data create_bonus()
{
    bonus_data new_bonus;                                             // new bonus data
    bitmap bonus_bitmap;                                              // new bonus bitmap
    point_2d bonus_starting_xy = point_at(-100, screen_height() / 4); // starting point of bonuses, just off screen to the left

    int choose_type = rnd(1, 5); //pick what type of bonus this will be
    // rnd(int, int) is supposed to be inclusive, but its apparently not inclusive on the max side

    switch (choose_type) // uses reandom number to assign bonus type, and appropriate bitmap
    {
    case 4:
        new_bonus.type = INCREASE_RELOAD_SPEED;
        bonus_bitmap = bitmap_named("bonus_reload");
        break;
    case 3:
        new_bonus.type = INCREASE_MISSILE_SPEED;
        bonus_bitmap = bitmap_named("bonus_speed");
        break;
    case 2:
        new_bonus.type = INCREASE_MISSILE_SIZE;
        bonus_bitmap = bitmap_named("bonus_size");

        break;
    default:
        new_bonus.type = CLEAR_SCREEN;
        bonus_bitmap = bitmap_named("bonus_clear");
        break;
    }

    new_bonus.bonus_sprite = create_sprite(bonus_bitmap);           // create sprite from selected bitmap
    sprite_set_position(new_bonus.bonus_sprite, bonus_starting_xy); // set sprite start position
    sprite_set_dx(new_bonus.bonus_sprite, BONUS_SPRITE_SPEED);      // set sprite moving

    return new_bonus;
}

void add_bonus(vector<bonus_data> &bonuses)
{
    bonus_data new_bonus;         // new bonus_data
    new_bonus = create_bonus();   // create new bonus with random type
    bonuses.push_back(new_bonus); // insert bonus into game
}

void delete_bonus(vector<bonus_data> &bonuses, int index)
{
    int last_index = bonuses.size() - 1;  // get last index in dynamic array
    bonuses[index] = bonuses[last_index]; // move bonus from last index into index of bonus being removed (overwriting)
    bonuses.pop_back();                   // delete last index in dynamic array
}

void draw_bonuses(const vector<bonus_data> &bonuses)
{
    for (int i = 0; i < bonuses.size(); i++)  // loop through and draw all bonuses on screen
    {                                         //
        draw_sprite(bonuses[i].bonus_sprite); // draw bonus
    }
}

void update_bonuses(vector<bonus_data> &bonuses)
{
    int X_boundary_right = screen_width() + 100; // X right side boundary, 100 pixels off screen.

    for (int i = 0; i < bonuses.size(); i++) // loop through all bonuses in game
    {
        update_sprite(bonuses[i].bonus_sprite); // update bonus sprite

        if ((sprite_x(bonuses[i].bonus_sprite) > X_boundary_right)) // if bonus goes off screen
        {                                                           //
            delete_bonus(bonuses, i);                               // then delete bonus
        }                                                           //
    }
}

void apply_bonus(applied_bonus_tracker &bonus_tracker, const bonus_type type)
{
    switch (type) // apply bonus types
    {
    case INCREASE_RELOAD_SPEED:                                   // If reload speed bonus
        bonus_tracker.increase_reload_speed = APPLIED_BONUS_TIME; // reset reload speed bonus countdown
        break;
    case INCREASE_MISSILE_SPEED:                                   // If missile speed bonus
        bonus_tracker.increase_missile_speed = APPLIED_BONUS_TIME; // reset missile speed bonus countdown
        break;
    case INCREASE_MISSILE_SIZE:                                   // If missile  bonus
        bonus_tracker.increase_missile_size = APPLIED_BONUS_TIME; // reset missile size bonus countdown
        break;
    default:                               // Otherwise, must be a clear screen bonus
        bonus_tracker.clear_screen = true; // so apply that
        break;
    }
}

void decrement_bonus_tracker(applied_bonus_tracker &bonus_tracker)
{
    if (bonus_tracker.increase_reload_speed > 0) // If reload speed bonus countdown is above zero
    {                                            //
        bonus_tracker.increase_reload_speed--;   // Decrement it
    }

    if (bonus_tracker.increase_missile_speed > 0) // If missile speed bonus countdown is above zero
    {                                             //
        bonus_tracker.increase_missile_speed--;   // Decrement it
    }

    if (bonus_tracker.increase_missile_size > 0) // If missile size bonus countdown is above zero
    {                                            //
        bonus_tracker.increase_missile_size--;   // Decrement it
    }
}