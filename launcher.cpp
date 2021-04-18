// Missile Command
// JP Karnilowicz
// launcher.cpp
// procedures and functions related to the player controlled missile launcher

#include "game.h"
#include <cmath> // included for atan2() function used in find_angle() function

launcher_data create_launcher() // create a new new_launcher
{
    launcher_data new_launcher;                           // new launcher_data
    bitmap launcher_head = bitmap_named("launcher_head"); // get appropriate bitmap
    new_launcher.sprite = create_sprite(launcher_head);   // convert to sprite

    new_launcher.launcher_xy.x = (screen_width() / 2) - (bitmap_height(launcher_head) / 2); // place launcher in horizontal centre
    new_launcher.launcher_xy.y = (screen_height() - 150);                                   // place launcher just launcher base
    sprite_set_position(new_launcher.sprite, new_launcher.launcher_xy);                     // set sprite position to location
    sprite_set_rotation(new_launcher.sprite, -90);                                          // set launcher head rotation, just so it looks nice in the welcome screen

    new_launcher.launcher_xy = center_point(new_launcher.sprite); // replace launcher coordinates, with coordinates of the centre of the sprite for use as in handle_input() to pass in player missile origin

    new_launcher.reload_countdown = 0; // start with launcher loaded, ready to fire

    return new_launcher; // return new_launcher data
}

double find_angle(point_2d origin_xy, point_2d target_xy) // find angle for launcher sprite
{
    double deltaY = (target_xy.y - origin_xy.y); //  get difference in y coordinates
    double deltaX = (origin_xy.x - target_xy.x); //  get difference in x coordinates
    double result = atan2(deltaX, deltaY);       // calculate angle in radians
    result = result * (180 / PI);                // convert to degrees
    result = result + 90;                        // compensate 90 to be relative from the vertical
    return result;                               // return angle
}

void draw_launcher(const launcher_data &launcher) // draw missle launcher
{
    draw_sprite(launcher.sprite); // draw sprite

    if (launcher.reload_countdown == 0)                                                               // if launcher is ready to fire
    {                                                                                                 //
        fill_circle(COLOR_BRIGHT_GREEN, launcher.launcher_xy.x - 18, launcher.launcher_xy.y + 37, 3); // display "ready to fire" green indicator (indicator position relative to launcher position)
    }                                                                                                 //
    else                                                                                              // else
    {                                                                                                 //
        fill_circle(COLOR_RED, launcher.launcher_xy.x - 18, launcher.launcher_xy.y + 37, 3);          // display "not ready" red indicator (indicator position relative to launcher position)
    }
}

void update_launcher(launcher_data &launcher) // draw missle launcher
{
    point_2d mouse_xy = point_at(mouse_x(), mouse_y());           // find mouse cursor location
    double rotation = find_angle(launcher.launcher_xy, mouse_xy); // use function to find angle to rotate launcher head
    sprite_set_rotation(launcher.sprite, rotation);               // rotate launcher head sprite

    // decrement launcher reload timer countdown if required
    if (launcher.reload_countdown > 0)
    {
        launcher.reload_countdown--;
    }
}