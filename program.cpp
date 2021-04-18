// Missile Command
// JP Karnilowicz
// Program.cpp
// Main loop

#include "splashkit.h"
#include "game.h"

void load_resources() // Load game images, sounds, etc
{
    load_resource_bundle("game_bundle", "missile_command.txt");
}

int main()
{

    open_window("Missle Command", 1280, 800);  // open new window
    load_resources(); // load resource file

    game_data game = create_game(); // create new game_data
    draw_game(game);                // draw game to screen (For the welcome screen)
    draw_welcomescreen(game.highscores);           // draw welcome screen over game
    delay(5000);                    // delay 3 seconds before starting play

    while (not quit_requested()) // while window is open
    {
        if (!game.gameover)         // if game isn't over
        {                           //
            handle_inputs(game);    // take player inputs
            update_game(game);      // update game data
            draw_game(game);        // draw updated game to screen
        }
        else                             // else, must be game over
        {                                //
            handle_gameover_input(game); // look for user input to start new game
            draw_game(game);             // draw game
        }
    }

    return 0;
}