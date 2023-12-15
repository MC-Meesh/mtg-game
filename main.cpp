/* Michael Allen - CSCI 261 Final Project - "Creatures++"
 *
 * Sources:
 * Taking only int inputs and avoiding error: https://www.codespeedy.com/taking-only-integer-input-in-cpp/
 *
 *
 * */




#include <iostream>
#include "creature.h"
#include "Player.h"
#include "functions.h"
#include "random"

using namespace std;

int main() {
    srand(time(NULL));

    //Clear gameLog from previous game
    clearFile();

    //Init a user and computer player
    introduction();

    //Init players
    class Player opponent;

    class Player user;
    user.setName();

    //Rules
    rules();
    game_init();

    //Main game loop
    while(true) {

        //Attack
        addMana(user);
        setAvailability(user);
        logBoard(opponent,user);
        while (true) {
            printBoard(opponent, user);
            if (!user.action_attack(opponent)) {
                break;
            }
        }
        if(winCondition(user, opponent)){
            return 0;
        }


        //Defense
        addMana(opponent);
        setAvailability(opponent);
        logBoard(opponent,user);
        while (true) {
            printBoard(opponent, user);
            if (!opponent.action_attack(user)) {
                break;
            }
        }
        if(winCondition(opponent, user)){
            return 0;
        }

    }
}
