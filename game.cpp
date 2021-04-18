// Missile Command
// JP Karnilowicz
// game.cpp
// Main game functions, including updating, drawing, handling inputs, and collisions.

#include "splashkit.h"
#include "game.h"

game_data create_game() // create a new game
{
    game_data new_game; // new game_data

    new_game.score = 0;                                                    // start score at zero
    new_game.countdown_to_next_enemy_launch = 180;                         // launch very first missile 3 seconds after beginning game (60 = 1 second)
    new_game.difficulty_wave = NEW_GAME_STARTING_DIFFICULTY;               // start with only launching 1 missile at a time
    new_game.countdown_to_next_wave = LAUNCHES_BEFORE_DIFFICULTY_INCREASE; // set how many waves of missiles are sent before next difficulty
    new_game.gameover = false;                                             // is the game over?

    new_game.launcher = create_launcher(); // create new missle launcher

    for (int i = 0; i < 6; i++) // interate to add buildings at all 6 locations
    {
        new_game.buildings.push_back(create_building(i + 1));
    }

    read_highscores_from_file(new_game.highscores); // read in the previous high scores from external file

    return new_game; // return new game data
}

void draw_scenery()
{

    bitmap clouds = bitmap_named("clouds");               // get clouds bitmap
    bitmap mountains = bitmap_named("mountains");         // get mountains bitmap
    bitmap ground = bitmap_named("ground");               // get ground bitmap
    bitmap launcher_base = bitmap_named("launcher_base"); // get launcher_base bitmap

    draw_bitmap(clouds, 1, 150);    // draw clouds background layer
    draw_bitmap(mountains, 1, 350); // draw mountains background layer

    double y = screen_height() - bitmap_height(ground); // y position for ground (bitmap right to the bottom of screen)
    double x = 0;                                       // starting x position for ground

    for (int i = 0; i < screen_width(); i = i + bitmap_width(ground)) // interate to draw ground tiles over entire screen width
    {
        draw_bitmap(ground, x, y);    // draw tile
        x = x + bitmap_width(ground); // add tile width to x position for next tile placement
    }

    y = screen_height() - bitmap_height(ground) - bitmap_height(launcher_base); // y position for launcher base (above ground)
    x = (screen_width() / 2) - (bitmap_height(launcher_base) / 2);              // starting x position for ground

    draw_bitmap(launcher_base, x, y); // draw base for missile launcher
}

void draw_welcomescreen(const vector<int> &highscores)
{
    font hud_font = font_named("franklin_medium");                                           // load a font
    bitmap welcome = bitmap_named("welcome");                                                // get welcome splashscreen
    draw_bitmap(welcome, (screen_width() - bitmap_width("welcome")) / 2, 100);               // draw welcome to screen
    draw_text("CLICK YOUR MOUSE TO LAUCH MISSILES", COLOR_DARK_RED, hud_font, 30, 380, 500); // display difficulty wave
    draw_text("CLICK YOUR MOUSE TO LAUCH MISSILES", COLOR_BLACK, hud_font, 30, 382, 502);    // display difficulty wave
    draw_highscores(highscores);                                                             // draw highscores to screen
    refresh_screen();                                                                        // refresh screen
}

void draw_gameover(const vector<int> &highscores, int score, int difficulty_wave)
{
    font hud_font = font_named("franklin_medium");                                                              // load a font
    bitmap gameover = bitmap_named("gameover");                                                                 // get gameover splashscreen
    draw_bitmap(gameover, (screen_width() - bitmap_width("gameover")) / 2, 100);                                // draw tile
    draw_text("YOU DEFENDED UNTIL WAVE " + to_string(difficulty_wave), COLOR_DARK_RED, hud_font, 40, 390, 500); // display difficulty wave
    draw_text("YOU DEFENDED UNTIL WAVE " + to_string(difficulty_wave), COLOR_BLACK, hud_font, 40, 392, 502);    // display difficulty wave
    draw_text("FINAL SCORE: " + to_string(score), COLOR_DARK_RED, hud_font, 40, 390, 540);                      // display score
    draw_text("FINAL SCORE: " + to_string(score), COLOR_BLACK, hud_font, 40, 392, 542);                         // display score
    draw_highscores(highscores);                                                                                // draw highscores to screen
}

void draw_hud(int score, int difficulty_wave, const applied_bonus_tracker &bonus_tracker)
{
    font hud_font = font_named("franklin_medium");                                          // load a font
    draw_text("WAVE: " + to_string(difficulty_wave), COLOR_DARK_RED, hud_font, 20, 30, 30); // display difficulty wave (shadow)
    draw_text("WAVE: " + to_string(difficulty_wave), COLOR_BLACK, hud_font, 20, 31, 31);    // display difficulty wave
    draw_text("SCORE: " + to_string(score), COLOR_DARK_RED, hud_font, 20, 30, 50);          // display score (shadow)
    draw_text("SCORE: " + to_string(score), COLOR_BLACK, hud_font, 20, 31, 51);             // display score

    if (bonus_tracker.increase_missile_speed > 0)               // if missile speed bonus is active
    {                                                           //
        draw_bitmap(bitmap_named("bonus_speed_icon"), 30, 115); // show icon
    }
    if (bonus_tracker.increase_missile_size > 0)               // if missile size bonus is active
    {                                                          //
        draw_bitmap(bitmap_named("bonus_size_icon"), 30, 155); // show icon
    }
    if (bonus_tracker.increase_reload_speed > 0)                 // if reload speed bonus is active
    {                                                            //
        draw_bitmap(bitmap_named("bonus_reload_icon"), 30, 195); // show icon
    }
    if (bonus_tracker.clear_screen > 0)                                        //
    {                                                                          //
        draw_bitmap(bitmap_named("bonus_clear_icon"), 30, 75);                 // show icon
        draw_text("RIGHT CLICK TO USE", COLOR_DARK_RED, hud_font, 15, 90, 85); // and instructions (shadow)
        draw_text("RIGHT CLICK TO USE", COLOR_BLACK, hud_font, 15, 91, 86);    // and instructions
    }
}

void draw_game(const game_data &game)                               // draw updated game
{                                                                   //
    clear_screen(COLOR_SKY_BLUE);                                   // clear screen
    draw_scenery();                                                 // draw scenery
    draw_hud(game.score, game.difficulty_wave, game.bonus_tracker); // draw hud
    draw_buildings(game.buildings);                                 // draw buildings
    draw_missiles(game.missiles);                                   // draw all missiles in game
    draw_bonuses(game.bonuses);                                     // draw all missiles in game
    draw_explosions(game.explosions);                               // draw all missiles in game
    draw_launcher(game.launcher);                                   // draw launcher head
    if (game.gameover)
    {
        draw_gameover(game.highscores, game.score, game.difficulty_wave); // draw gameover overlay
    }
    refresh_screen(60);
}

void handle_inputs(game_data &game)
{
    process_events(); // splashkit required to get user inputs

    if (mouse_clicked(LEFT_BUTTON) and (game.launcher.reload_countdown == 0))                        // if left mouse button is pressed
    {                                                                                                //
        point_2d mouse_xy = point_at(mouse_x(), mouse_y());                                          // take mouse click coordinates
        add_missile(game.missiles, PLAYER, game.launcher.launcher_xy, mouse_xy, game.bonus_tracker); // add missile to game with launcher as origin, mouse as target

        if (game.bonus_tracker.increase_reload_speed > 0)                  // check if increase reload speed bonus is applied
        {                                                                  //
            game.launcher.reload_countdown = RELOAD_TIMER_COUNTDOWN_BONUS; // start bonus reload timer countdown
        }                                                                  //
        else                                                               //
        {                                                                  //
            game.launcher.reload_countdown = RELOAD_TIMER_COUNTDOWN;       // start standard reload timer countdown
        }
    }

    if (mouse_clicked(RIGHT_BUTTON) and (game.bonus_tracker.clear_screen))
    {
        clear_screen(game.missiles, game.explosions, game.score);
        game.bonus_tracker.clear_screen = false;
    }
}

void handle_gameover_input(game_data &game)
{
    process_events(); // splashkit required to get user inputs

    if (key_typed(SPACE_KEY))
    {
        game = create_game();
    }
}

void check_collisions(game_data &game) // check sprite collisions
{
    int Y_ground_level = (screen_height() - 100); // Y bottom is compensated 100 pixels to about ground level

    for (int i = 0; i < game.missiles.size(); i++) // go through and check missile collisions
    {
        if (sprite_y(game.missiles[i].missile_sprite) > Y_ground_level)                                                                                             // If missile hits ground level, explode
        {                                                                                                                                                           //
            add_explosion(game.explosions, game.missiles[i].missile_team, center_point(game.missiles[i].missile_sprite), game.bonus_tracker.increase_missile_size); // add explosion at missile location
            delete_missile(game.missiles, i);                                                                                                                       // delete missile from game
        }

        if (sprite_collision(game.missiles[i].missile_sprite, game.missiles[i].target_sprite))                                                                     // if missile hits it's target, explode
        {                                                                                                                                                          //
            add_explosion(game.explosions, game.missiles[i].missile_team, center_point(game.missiles[i].target_sprite), game.bonus_tracker.increase_missile_size); // create explosion at target location (which is slightly off to where the missile is, but we require the explosions to be where the user targeted)
            delete_missile(game.missiles, i);                                                                                                                      // delete missile from game
        }

        for (int j = 0; j < game.buildings.size(); j++)                                                                                                                 // loop through every building in game.
        {                                                                                                                                                               //
            if (sprite_collision(game.missiles[i].missile_sprite, game.buildings[j].building_sprite))                                                                   // if an missile hits a building, destroy it
            {                                                                                                                                                           //
                add_explosion(game.explosions, game.missiles[i].missile_team, center_point(game.missiles[i].missile_sprite), game.bonus_tracker.increase_missile_size); // create explosion at missile location
                delete_missile(game.missiles, i);                                                                                                                       // delete missile from game
            }
        }
    }

    for (int i = 0; i < game.explosions.size(); i++) // go through and check explosion collisions
    {
        for (int j = 0; j < game.buildings.size(); j++)                                                   // loop through every building in game.
        {                                                                                                 //
            if (sprite_collision(game.explosions[i].explosion_sprite, game.buildings[j].building_sprite)) // if an explosion hits a building, destroy it
            {                                                                                             //
                building_sprite_destroyed(game.buildings[j]);
                game.buildings[j].destroyed = true;
            }
        }

        for (int j = 0; j < game.missiles.size(); j++)                                                  // loop through every building in game.
        {                                                                                               //
            if (sprite_collision(game.explosions[i].explosion_sprite, game.missiles[j].missile_sprite)) // if an explosions hits a building, destroy it
            {                                                                                           //
                if (game.missiles[j].missile_team == ENEMY)                                             // check if missile being destroyed is an enemy missile
                {                                                                                       // if so
                    game.score = game.score + POINTS_FOR_MISSILE_KILL;                                  // add score
                }
                delete_missile(game.missiles, j); // delete missile from game
            }
        }

        for (int j = 0; j < game.bonuses.size(); j++)                                                // loop through every bonus in game.
        {                                                                                            //
            if (sprite_collision(game.explosions[i].explosion_sprite, game.bonuses[j].bonus_sprite)) // if an explosion hits a bonus
            {                                                                                        //
                apply_bonus(game.bonus_tracker, game.bonuses[j].type);                               // Apply bonus here
                delete_bonus(game.bonuses, j);                                                       // delete bonus from game
            }
        }
    }
}

void clear_screen(vector<missile_data> &missiles, vector<explosion_data> &explosions, int &score)
{
    for (int i = missiles.size() - 1; i >= 0; i--) // loop backwards through all missiles in game (otherwise if out missile vector size keeps changing, our exit loop target keeps changing)
    {
        add_explosion(explosions, missiles[i].missile_team, center_point(missiles[i].missile_sprite), 0); // create explosion at target location (which is slightly off to where the missile is, but we require the explosions to be where the user targeted)
        delete_missile(missiles, i);                                                                      // delete missile from game
        score = score + POINTS_FOR_MISSILE_KILL;                                                          // add points for missile destroy
    }
}

void update_game(game_data &game)
{
    update_launcher(game.launcher);     // update missile launcher data
    update_explosions(game.explosions); // update explosions data
    update_missiles(game.missiles);     // update all missiles in game
    update_bonuses(game.bonuses);       // update all onscreen bonuses
    check_collisions(game);             // check collisions between sprites

    decrement_bonus_tracker(game.bonus_tracker); // decrement counters for applied bonuses

    int buildings_standing = buildings_still_standing(game.buildings); // count how many buildings are still standing

    if (buildings_standing < 1)                        // if no buildings are left standing,
    {                                                  //
        game.gameover = true;                          // set game over (this will signal the main loop to display game over screen)
        check_highscores(game.highscores, game.score); // check score aSgainst highscore list and add if required
    }                                                  //

    if (game.countdown_to_next_enemy_launch < 0)                           // if countdown for next launch of missiles is finished
    {                                                                      //
        for (int i = 0; i < game.difficulty_wave; i++)                     // loop through and launch specific number of missiles for current difficulty wave.
        {                                                                  //
            generate_enemy_missile(game.missiles, game.bonus_tracker);     //
        }                                                                  //
        game.countdown_to_next_enemy_launch = TIME_BETWEEN_ENEMY_MISSILES; // reset countdown to next wave of missiles
        game.countdown_to_next_wave--;                                     // decrement countdown to next difficulty

        if (rnd() < CHANCE_OF_BONUS_APPEARANCE) // roll for a chance at a bonus
        {                                       //
            add_bonus(game.bonuses);            // congratulate player with a bonus appearance
        }

        if (game.countdown_to_next_wave <= 0)                                                                       // If countdown for next difficulty is finished
        {                                                                                                           //
            game.score = game.score + (buildings_standing * game.difficulty_wave * POINTS_FOR_BUILDINGS_EACH_WAVE); // multiply buildings still standing * difficulty wave * points for buildings for end-of-wave bonus score
            game.difficulty_wave++;                                                                                 // add another missle per launch
            game.countdown_to_next_wave = LAUNCHES_BEFORE_DIFFICULTY_INCREASE;                                      //  reset the countdown for next difficulty
            game.countdown_to_next_enemy_launch = BREATHER_TIME_BEFORE_NEXT_WAVE;                                   // and give player some breathing time before next difficulty wave
            add_bonus(game.bonuses);                                                                                // congratulate player with a bonus appearance
        }
    }
    game.countdown_to_next_enemy_launch--; // decrement counter to next enemy missle launch
}
