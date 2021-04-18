// Missile Command
// JP Karnilowicz
// highscores.cpp
// procedures and functions relating to saving/reading highscores in external file

#include "splashkit.h"
#include "game.h"
#include <fstream>
using namespace std;

void read_highscores_from_file(vector<int> &highscores)
{
    ifstream file_data;  // create new file data
    string input_string; // input_string to use to read in from file

    file_data.open("highscores.csv");                                   // open high score file
    if (file_data.is_open())                                            // if file is open
    {                                                                   //
        while (!file_data.eof())                                        // while not at end of file
        {                                                               //
            getline(file_data, input_string);                           // read new line from file
            if (is_integer(input_string))                               // confirm line is a number, just in case
            {                                                           //
                highscores.push_back(convert_to_integer(input_string)); // add number to high score vector
            }
        }
        file_data.close();           // close file

        bubble_sort(highscores);     // sort highscores
        trim_highscores(highscores); // make sure only 10 high scores are stored
    }
}

void write_highscores_to_file(const vector<int> &highscores)
{
    ofstream file_data;                             // create new file_data
    file_data.open("highscores.csv");               // open file "highscores.csv" - will create if it doesn't exist.
    if (file_data.is_open())                        // if file is open
    {                                               //
        for (int i = 0; i < highscores.size(); i++) // for every high score in the vector
        {                                           //
            file_data << highscores[i];             // write the score
            file_data << "\n";                      // move to next line
        }                                           //
        file_data.close();                          // close file
    }
}

void bubble_sort(vector<int> &values)
{
    int temp; // temp integer to assist with value swap during sorting

    for (int j = 0; j < values.size() - 1; j++)     // loop sorting routine for as many times as there are values in it.
    {                                               //
        for (int i = 0; i < values.size() - 1; i++) // Go through every value in dynamic array
        {                                           //
            if (values[i] < values[i + 1])          // if value is less than next value,
            {                                       //
                temp = values[i];                   // swap them
                values[i] = values[i + 1];          //
                values[i + 1] = temp;               //
            }
        }
    }
}

void trim_highscores(vector<int> &highscores)
{
    while (highscores.size() > 10) // if high score list is above 10 for whatever reason,
    {                              //
        highscores.pop_back();     // trim it down to only 10 scores
    }
}

void check_highscores(vector<int> &highscores, int new_highscore)
{
    if ((highscores.size() < 10) || (new_highscore > highscores[9])) // if new score is higher than the lowest highscore on file, then it is a highscore!
    {
        font hud_font = font_named("franklin_medium");                         // load font for high score notification dialog
        display_dialog("Congrats!", "You got a new highscore!", hud_font, 15); // give user high score notification

        highscores.push_back(new_highscore); // add highscore to vector

        bubble_sort(highscores);              // sort highscores
        trim_highscores(highscores);          // make sure only 10 high scores are stored
        write_highscores_to_file(highscores); // Write new highscores to file
    }
}

void draw_highscores(const vector<int> &highscores)
{
    font hud_font = font_named("franklin_medium"); // load required font
    color hud_box_color = {0, 0, 0, 0.1};          // Custom slightly transparent color for highscore backdrop. format is {R,G,B,Opacity}

    int y_position = 180;
    fill_rectangle(hud_box_color, 1030, 140, 200, 300);               // draw background shade
    draw_rectangle(COLOR_DARK_RED, 1030, 140, 200, 300);              // border around background box
    draw_text("HIGHSCORES", COLOR_BLACK, hud_font, 25, 1057, 150);    // highscore heading
    draw_text("HIGHSCORES", COLOR_DARK_RED, hud_font, 25, 1058, 151); // highscore heading

    for (int i = 0; i < highscores.size(); i++) // for every high score in the vector
    {
        draw_text(to_string(i + 1), COLOR_BLACK, hud_font, 25, 1040, y_position);             // draw placing
        draw_text(to_string(i + 1), COLOR_DARK_RED, hud_font, 25, 1041, y_position + 1);      // draw placing
        draw_text(to_string(highscores[i]), COLOR_DARK_RED, hud_font, 25, 1090, y_position);  // draw highscore
        draw_text(to_string(highscores[i]), COLOR_BLACK, hud_font, 25, 1091, y_position + 1); // draw highscore
        y_position = y_position + 25;
    }
}
