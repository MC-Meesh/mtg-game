//
// Created by chase on 10/7/2022.
//

#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include "Player.h"
#include "fstream"

//File Setup
void clearFile();

//Intro
void introduction();
void rules();
void game_init();

//Print to terminal
void printBoard(Player &opponent, Player &user);
void printStats(Player &player_to_print);
void printAttackMoves();

//Game rules and functions
int creatureCounter(int &creatureID);
void addMana(Player &player);
void setAvailability(Player &player);

//Log to board
void gameLogWrite(string toWrite);
void logBoard(Player &opponent, Player &user);
void logStats(Player &player_to_print);

//End condition
bool winCondition(Player &attacker, Player &defender);




#endif //CODE_FUNCTIONS_H
