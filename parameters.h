// Missile Command
// JP Karnilowicz
// Paratmeters.h
// Filled with defined parameters used throughout game.

#ifndef MISSLE_COMMAND_PARAMETERS
#define MISSLE_COMMAND_PARAMETERS

// Missile stuff
#define PLAYER_MISSILE_SPEED 6          // How fast player missiles fly
#define ENEMY_MISSILE_SPEED 2           // How fast enemy missiles fly
#define RELOAD_TIMER_COUNTDOWN 60       // Time it takes for launcer to allow next missile to be launched (60 = 1 second)
#define TIME_BETWEEN_ENEMY_MISSILES 300 // Time it takes between enemy missiles launching, at the beginning of the game (60 = 1 second)
#define EXPLOSION_SHRINK_RATE 0.02      // How fast explosions shrink and disappear 0.01 = 1%, 60 times/second
#define EXPLOSION_ROTATION_RATE 7       // How fast explosions sprite rotates. 5 = 5 degrees, 60 times/second

// Game stuff
#define PI 3.14159265358979323846264338327950288 // defined for the find_angle() function, as no PI constant seems to be included in cmath
#define POINTS_FOR_MISSILE_KILL 50               // How much score to add for each missle killed
#define NEW_GAME_STARTING_DIFFICULTY 1           // What difficulty wave to start a new game at
#define LAUNCHES_BEFORE_DIFFICULTY_INCREASE 6    // How many launches of enemy missles in each wave of difficulty
#define BREATHER_TIME_BEFORE_NEXT_WAVE 600       // Time to give player a breather between waves (60 = 1 second)
#define POINTS_FOR_BUILDINGS_EACH_WAVE 250       // How many points for each building still standing at the end of each difficulty wave (multiplied by wave number)

// Bonus stuff
#define CHANCE_OF_BONUS_APPEARANCE 0.3   // chance of a bonus appearing at launch (1.0 = 100%)
#define BONUS_SPRITE_SPEED 3             // How fast bonus sprite moves over screen
#define APPLIED_BONUS_TIME 1200          // How long an applied bonus lasts (60 = 1 second)
#define RELOAD_TIMER_COUNTDOWN_BONUS 10; // Time it takes for launcer to allow next missile to be launched, when launcher reload bonus is applied (60 = 1 second)
#define PLAYER_MISSILE_SPEED_BONUS 12    // How fast player missiles fly when bonus applied
#define PLAYER_MISSILE_SIZE_BONUS 1.5    // scale how much bigger the large missiles explosions are (1.0 = 100%)

#endif