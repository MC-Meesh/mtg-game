//
// Created by chase on 10/7/2022.
//

#include "iostream"
#include "Player.h"
#include <iomanip>
#include <fstream>



using namespace std;

//----------------ClearFile--------------------
void clearFile(){
    remove("gameLog.txt");
}




//-----------Init, intro, and rules-----------------
void introduction(){
    cout << endl;
    cout << "Welcome to this game that is totally original and took no inspiration from CSCI-261 Labs or Magic The Gathering." << endl;
    cout << "Your objective is to reduce your opponent's life total to zero. You will do this using creatures and spells." << endl;
}

void printStats(Player &player_to_print){

    //Opponent view
    if (player_to_print.getName() == "Opponent") {

        //Head
        cout << left << ">" << setfill('-') << setw(30) << "";
        cout << setw(30+(player_to_print.getName().size())) << player_to_print.getName();
        cout << right << "<" << endl;

        //Life
        cout << left << setfill(' ') << setw(22) << "";
        cout << "Life: " << player_to_print.getLife() << "    |    Mana: ??" << endl;

        //Creatures
        cout <<  "Unavailable Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if (!(player_to_print.ownedCreatures)[i].getAvailability()) {
                    cout << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                            (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        cout << endl;

        cout << "Available Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if ((player_to_print.ownedCreatures)[i].getAvailability()) {
                    cout << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        cout << endl;
    }



    //Player View (Bottom)
    else{
        cout << "Available Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if ((player_to_print.ownedCreatures)[i].getAvailability()) {
                    cout << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        cout << endl;

        cout <<  "Unavailable Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if (!(player_to_print.ownedCreatures)[i].getAvailability()) {
                    cout << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        cout << endl;

        //Life
        cout << left << setfill(' ') << setw(22) << "";
        cout << "Life: " << player_to_print.getLife() << "    |    Mana: " << player_to_print.getMana() << endl;

        //Head
        cout << left << ">" << setfill('-') << setw(30) << "";
        cout << setw(38) << player_to_print.getName();
        cout << right << "<" << endl;
    }


}

void rules(){

    while(true){
        char rules;
        cout << "Would you like to read the rules? (y/n) ";
        cin >> rules;

        if (rules=='y' || rules=='Y'){
            cout << endl;
            cout << "================================= Rules ====================================" << endl;

            cout << "This is a turn based game in which you spend 'Mana' to proactively deal damage to your opponent - first to 0 Life loses." << endl <<
                 "*Each player starts with 20 Life, 7 mana, and no Creatures." << endl <<
                 "*During your turn (Attack), you can: create creatures, use creatures to attack your opponent, deal damage to other creatures, or deal damage to your opponent directly." << endl <<
                 "   -'Cast a Creature' creates a creature under your control with base Power and Toughness related to the mana you spent to cast that creature, notated as (POWER/TOUGHNESS) on the board." << endl <<
                 "*During your opponents turn (Defense), you can use creatures to block their incoming attacks (blocking creatures are chosen after attackers are declared)." << endl <<
                 "   -Blocking a creature will protect you from damage that you would take otherwise." << endl <<
                 "   -Blocking does not cost mana, but you can only block with creatures who haven't attacked from your (Attack) turn." << endl <<
                 "   -A blocking creature and attacking creature will deal damage to each other, if a creature's Toughness reaches 0 it will die" << endl <<
                 "   -Creatures can be healed if you spend Mana on your turn." << endl <<
                 "*Each attack turn, you will be awarded mana, plus additional mana based on creatures you own." << endl <<
                 "*Mana cost for each item is shown as (C), where C is the cost of that action. Actions with (x) as the cost allow you to input the cost to change the impact of a given action." <<  endl <<
                 "*If you or an opponent drops below 0 life and the turn is passed, that player will lose the game" << endl;
            cout << "================================================================================" << endl;
            return;
        }
        else if(rules=='n'||rules=='N'){
            return;
        }
        else{
            cout << "Please type 'y' or 'n'" << endl;
        }


    }
}

void game_init(){
    string Null;
    cout << endl << "You will go first, use the [number keys] followed by RETURN to enter your moves." << endl << "Good Luck! Type something to begin: ";
    cin >> Null;
    cout << endl;
}

void printBoard(Player &opponent, Player &user){
    printStats(opponent);
    cout << endl << endl;
    printStats(user);
}

void printAttackMoves() {
    cout << "Actions: " << endl;

    cout << "Cast Creature (x)" << " | Attack with Creature" << " | Buff Creature by 1 (2)" << " | Heal Creature by x (x)" << " | Damage Creature by x (x)" << " | Damage Opponent by x/2 (x)" << " | End Turn" << endl;
    cout << "" << setfill(' ') << right << setw(9) << "[1]";
    cout << "" << setw(22) << right << "[2]";
    cout << "" << setw(22) << right << "[3]";
    cout << "" << setw(25) << right << "[4]";
    cout << "" << setw(25) << right << "[5]";
    cout << "" << setw(30) << right  << "[6]";
    cout << "" << setw(21) << right << "[e]";
    cout << endl << "Your action: ";
}

int creatureCounter(int &creatureID){
    creatureID += 1;
    return creatureID;
}

void addMana(Player &player){

    if(player.getName() == "Opponent"){
        int newMana = player.getMana() + 1.5*(2*(player.ownedCreatures.size()) + 1);
        player.setMana(newMana);
    }
    else {
        int newMana = player.getMana() + 2 * (player.ownedCreatures.size()) + 1;
        player.setMana(newMana);
    }
}

void setAvailability(Player &player){
    for(int i = 0; i < player.ownedCreatures.size(); i++){
        player.ownedCreatures[i].setAvailability(true);
    }
}

//----------------------Writing text to game log------------------------------

void gameLogWrite(string toWrite){
    ofstream output( "gameLog.txt", std::ios_base::app );
    if( output.fail() ) {               // check for an error opening the output
        cerr << "Failed to open file \"output.txt\" << endl";
        return;
    }

    output << toWrite << endl;

    output.close();
}

void logStats(Player &player_to_print){

    ofstream output( "gameLog.txt" , std::ios_base::app);
    if( output.fail() ) {               // check for an error opening the output
        cerr << "Failed to open file \"output.txt\" << endl";
        return;
    }

    //Opponent view
    if (player_to_print.getName() == "Opponent") {

        //Head
        output << left << ">" << setfill('-') << setw(30) << "";
        output << setw(30+(player_to_print.getName().size())) << player_to_print.getName();
        output << right << "<" << endl;

        //Life
        output << left << setfill(' ') << setw(22) << "";
        output << "Life: " << player_to_print.getLife() << "    |    Mana: ??" << endl;

        //Creatures
        output <<  "Unavailable Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if (!(player_to_print.ownedCreatures)[i].getAvailability()) {
                    output << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        output << endl;

        output << "Available Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if ((player_to_print.ownedCreatures)[i].getAvailability()) {
                    output << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        output << endl;
    }



        //Player View (Bottom)
    else{
        output << "Available Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if ((player_to_print.ownedCreatures)[i].getAvailability()) {
                    output << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        output << endl;

        output <<  "Unavailable Creatures: ";
        if (!(player_to_print.ownedCreatures).empty()) {
            for (int i=0; i < (player_to_print.ownedCreatures).size(); i++) {
                if (!(player_to_print.ownedCreatures)[i].getAvailability()) {
                    output << "[" << (player_to_print.ownedCreatures)[i].getCreatureId() << "] " << (player_to_print.ownedCreatures)[i].getPower() << "/" <<
                         (player_to_print.ownedCreatures)[i].getToughness() << "   ";
                }
            }
        }
        output << endl;

        //Life
        output << left << setfill(' ') << setw(22) << "";
        output << "Life: " << player_to_print.getLife() << "    |    Mana: " << player_to_print.getMana() << endl;

        //Head
        output << left << ">" << setfill('-') << setw(30) << "";
        output << setw(38) << player_to_print.getName();
        output << right << "<" << endl << endl;
    }

    output.close();

}

void logBoard(Player &opponent, Player &user){

    logStats(opponent);

    ofstream output( "gameLog.txt", std::ios_base::app );
    if( output.fail() ) {               // check for an error opening the output
        cerr << "Failed to open file \"output.txt\" << endl";
        return;
    }
    output << endl << endl;
    output.close();

    logStats(user);

}


//---------------------Win Condition-----------------

bool winCondition(Player &attacker, Player &defender){
    //User wins
    if(attacker.getName() != "Opponent") {
        if(defender.getLife() <= 0){
            cout << endl << "You won the game, congrats!" << endl;
            cout << "Final Board" << endl;
            printBoard(defender,attacker);
            logBoard(defender, attacker);
            return true;
        }
    }
    //Opponent wins
    else{
        if(defender.getLife() <= 0){
            cout << endl <<"Opponent won the game, better luck next time." << endl;
            cout << "Final Board" << endl;
            printBoard(attacker,defender);
            logBoard(attacker,defender);
            cout << "A log of your most recent game titled 'gameLog.txt' can be found at your default output directory." << endl;
            return true;
        }
    }
    //Nobody has won yet
    return false;
}


