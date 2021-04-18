// Missile Command
// JP Karnilowicz
// highscores.h
// definitions for highscores.cpp

#ifndef MISSLE_COMMAND_HIGHSCORES
#define MISSLE_COMMAND_HIGHSCORES
#include "splashkit.h"


/**  Reads highscore list from external file into dynamic array
 *  @param highscores   vector to store highscores
 */
void read_highscores_from_file(vector<int> &highscores);

/**  Writes highscores from dynamic array into to external file
 *  @param highscores   vector with highscores to store externally
 */
void write_highscores_to_file(const vector<int> &highscores);

/**  Used to sort highscores from highers to lowest.
 *  @param values   vector of integers to sort
 */
void bubble_sort(vector<int> &values);

/**  if the highscore vector contains more than 10 scores, trim it down to 10.
 *  @param values   vector of integers to trim
 */
void trim_highscores(vector<int> &values);

/**  Vector to check if a new score is a highscore, if so add it to the highscores array and external file
 *  @param highscores   vector of high scores
 *  @param new_score   new score to check
 */
void check_highscores(vector<int> &highscores, int new_score);

/**  Draws a list of highscores to screen (for welcome and gameover screens)
 *  @param highscores   vector of high scores to display
 */
void draw_highscores(const vector<int> &highscores);

#endif
