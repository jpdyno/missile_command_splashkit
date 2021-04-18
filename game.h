// Missile Command
// JP Karnilowicz
// game.h
// Definitions for game.cpp

#ifndef MISSLE_COMMAND_GAME
#define MISSLE_COMMAND_GAME

#include "splashkit.h"
#include "parameters.h"
#include "buildings.h"
#include "launcher.h"
#include "bonuses.h"
#include "missiles.h"
#include "explosions.h"
#include "highscores.h"

#include <vector>
using namespace std;

// Game data structure
struct game_data
{
    launcher_data launcher;              // Missle launcher data
    vector<building_data> buildings;     // Array of buildings in game
    vector<missile_data> missiles;       // Dynamic Array of missiles in game
    vector<explosion_data> explosions;   // Dynamic Array of explosions in game
    vector<bonus_data> bonuses;          // current bonuses showing on screen
    applied_bonus_tracker bonus_tracker; // a struct of information for all bonuses currently applied in game
    int difficulty_wave;                 // difficultly wave (doubles as amount of missiles per enemy launch)
    int countdown_to_next_enemy_launch;  // countdown until next enemy missile launches
    int countdown_to_next_wave;          // countdown until next wave of difficulty (where amount of missiles per launch increases)
    int score;                           // player score
    bool gameover;                       // goes true when game is over (all buildings destroyed)
    vector<int> highscores;              // Dynamic Array of previous high scores
};

/**  Creates a new game
 *  @returns   New game data, with new buildings etc.
 */
game_data create_game();

/**  Draws scenery (ground, backdrop elements, etc)
 */
void draw_scenery();

/**  Draws game title and welcome screen on startup
 *  @param highscores   highscores to display
 */
void draw_welcomescreen(const vector<int> &highscores);

/**  Draws gameover graphic and score to screen\
 *  @param highscores   list of highscores to draw to screen
 *  @param score   final score
 *  @param difficulty_wave   final difficulty reached
 */
void draw_gameover(const vector<int> &highscores, int score, int difficulty_wave);

/**  Draws HUD (wave / powerups / score)
 *  @param game   game_data to draw
 */
void draw_hud(int score, int difficulty_wave, const applied_bonus_tracker &bonus_tracker);

/**  Draws game to screen
 *  @param game   game_data to draw
 */
void draw_game(const game_data &game);

/**  Takes in user inputs
 *  @param game   game_data to change on input
 */
void handle_inputs(game_data &game);

/**  Takes in user inputs during gameover screen
 *  @param game   game_data to reset on input
 */
void handle_gameover_input(game_data &game);

/**  Checks sprite collisions and reacts appropriatly
 *  @param game   game containing sprites
 */
void check_collisions(game_data &game);

/**  Clears screen of all missiles (bonus activated by right mouse button)
 *  @param missiles   vector containing missiles
 *  @param explosions   vector containing explosions
 *  @param score   game score to apply points to
 */
void clear_screen(vector<missile_data> &missiles, vector<explosion_data> &explosions, int &score);

/**  Updates game data
 *  @param game
 */
void update_game(game_data &game);

#endif