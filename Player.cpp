//
// Created by chase on 10/7/2022.
//

#include <limits>
#include "Player.h"
#include "creature.h"
#include "iostream"
#include "vector"
#include "functions.h"
#include "string.h"
#include "random"
#include "cstdlib"




using namespace std;

Player::Player() {
    _Life = 20;
    _Mana = 6;
    _name = "Opponent";
}

int Player::getLife() const {
    return _Life;
}

void Player::setLife(int newLife) {
    _Life = newLife;
}

int Player::getMana() const {
    return _Mana;
}

void Player::setMana(int newMana) {
    _Mana = newMana;
}

std::string Player::getName() const {
    return _name;
}

void Player::setName() {
    cout << "Please enter your name: ";
    cin >>  _name;
}


bool Player::action_attack(Player &defending_player) {

    //At beginning of each attack step, kill all creatures with toughness <= 0
    updateCreatures(defending_player);

    if(getName() == "Opponent"){
        if(!opponent_game_logic(defending_player)){
            string gameLog = "-> " + getName() + " passes the turn to " + defending_player.getName();
            cout << gameLog << endl << endl << endl;
            gameLogWrite(gameLog);
            gameLogWrite("");
            return false;
        }
        else{
            return true;
        }
    }
    else {
        cout << endl << "Available Mana: " << getMana() << " | ";
        printAttackMoves();

        char valid_actions[] = {'1', '2', '3', '4', '5', '6', 'e', 'E'};
        char action;
        bool check = true;

        while (check) {
            cin >> action;
            for (int i = 0; i < 8; i++) {
                if (char(action) == valid_actions[i]) {
                    check = false;
                    break;
                }
            }
            if (check){
                cout << "Please enter a valid action from the actions menu '[1] [2] ... [e]'" << endl;
            }

        }
        string gameLog;

        switch (action) {
            case '1':
                //Cast Creature
                Cast_Creature();
                break;
            case '2':
                //Attack
                Attack(defending_player);
                break;
            case '3':
                //Buff Creature
                Buff_Creature(defending_player);
                break;
            case '4':
                //Heal Creature
                Heal_Creature(defending_player);
                break;
            case '5':
                //Damage Creature
                Damage_Creature(defending_player);
                break;

            case '6':
                //Damage Opponent
                Damage_Opponent(defending_player);
                break;

            case 'e':
                gameLog = "-> " + getName() + " passes the turn to " + defending_player.getName();
                cout << gameLog << endl << endl << endl;
                gameLogWrite(gameLog);
                gameLogWrite("");
                return false;
            case 'E':
                gameLog = "-> " + getName() + " passes the turn to " + defending_player.getName();
                cout << gameLog << endl << endl << endl;
                gameLogWrite(gameLog);
                gameLogWrite("");
                return false;
        }

        return true;
    }


}

void Player::Buff_Creature(Player &defending_player){

    if(getName() == "Opponent"){
        vector<Creature> availableCreatures;
        for(int i = 0; i < ownedCreatures.size(); i++){
            if(ownedCreatures[i].getAvailability()){
                availableCreatures.push_back(ownedCreatures[i]);
            }
        }

        int creatureIdx;
        if(availableCreatures.size()!=0){
            creatureIdx = rand()%(availableCreatures.size());
        }
        else {
            return;
        }

        ownedCreatures[creatureIdx].setPower(ownedCreatures[creatureIdx].getPower() + 1);

        string gameLog = "-> " + getName() + " buffed [" + to_string(ownedCreatures[creatureIdx].getCreatureId()) + "] to ("
                               + to_string(ownedCreatures[creatureIdx].getPower()) + "/" + to_string(ownedCreatures[creatureIdx].getToughness()) + ")";
        cout << gameLog << endl;
        gameLogWrite(gameLog);

        setMana(getMana() - 2);
    }

    else {

        if (getMana() < 2) {
            cout << "This actions requires 2 Mana, you have " << getMana() << " Mana." << endl;
        } else if (ownedCreatures.empty() && defending_player.ownedCreatures.empty()) {
            cout << "No creatures to buff, cast creatures using on your turn using [1]." << endl;
        } else {
            cout << "Select a creature [NUMBER] to buff:" << endl;

            string buff_select = selectCreature(defending_player);

            //Assign selected creature 1 additional toughness
            for (int i = 0; i < (ownedCreatures).size(); i++) {
                if (buff_select == to_string(ownedCreatures[i].getCreatureId())) {
                    ownedCreatures[i].setPower(ownedCreatures[i].getPower() + 1);
                    string gameLog = "-> " + getName() + " buffed [" + to_string(ownedCreatures[i].getCreatureId()) + "] to ("
                         +to_string(ownedCreatures[i].getPower()) + "/" + to_string(ownedCreatures[i].getToughness()) + ")";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);

                }
            }

            for (int i = 0; i < (defending_player.ownedCreatures).size(); i++) {
                if (buff_select == to_string(defending_player.ownedCreatures[i].getCreatureId())) {
                    defending_player.ownedCreatures[i].setPower((defending_player.ownedCreatures[i].getPower()) + 1);
                    string gameLog = "-> " + getName() + " buffed [" + to_string(defending_player.ownedCreatures[i].getCreatureId())
                         + "] to (" + to_string(defending_player.ownedCreatures[i].getPower()) + "/" + to_string(defending_player.ownedCreatures[i].getToughness()) + ")";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);
                }
            }

            setMana(getMana() - 2);

        }
    }
}

void Player::Heal_Creature(Player &defending_player) {


    if(getName() == "Opponent"){

        int casting_cost = castingCostX();

        int creatureIdx = rand()%(ownedCreatures.size());
        ownedCreatures[creatureIdx].setToughness(ownedCreatures[creatureIdx].getToughness() + casting_cost);

        string gameLog = "-> " + getName() + " healed [" + to_string(ownedCreatures[creatureIdx].getCreatureId()) + "] to ("
             +to_string(ownedCreatures[creatureIdx].getPower()) + "/" + to_string(ownedCreatures[creatureIdx].getToughness()) + ")";
        cout << gameLog << endl;
        gameLogWrite(gameLog);
    }

    else {

        if (ownedCreatures.empty() && defending_player.ownedCreatures.empty()) {
            cout << "No creatures to heal, cast creatures using on your turn using [1]." << endl;
        } else {
            cout << "Select a creature [NUMBER] to heal:" << endl;
            string heal_select = selectCreature(defending_player);
            int casting_cost = castingCostX();

            bool check = false;
            //Assign creature x additional life, where x = casting_cost
            for (int i = 0; i < (ownedCreatures).size(); i++) {
                if (heal_select == to_string(ownedCreatures[i].getCreatureId())) {
                    ownedCreatures[i].setToughness(ownedCreatures[i].getToughness() + casting_cost);
                    string gameLog = "-> " + getName() + " healed [" + to_string(ownedCreatures[i].getCreatureId()) + "] to ("
                         +to_string(ownedCreatures[i].getPower()) + "/" + to_string(ownedCreatures[i].getToughness()) + ")";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);
                    check = true;
                }
            }

            //If for some reason you decide to heal an opponent's creature, here is this.
            if (!check) {
                for (int i = 0; i < (defending_player.ownedCreatures).size(); i++) {
                    if (heal_select == to_string(defending_player.ownedCreatures[i].getCreatureId())) {
                        defending_player.ownedCreatures[i].setToughness(
                                (defending_player.ownedCreatures[i].getToughness()) + casting_cost);
                        string gameLog = "-> " + getName() + " healed [" + to_string(defending_player.ownedCreatures[i].getCreatureId())
                             + "] to (" + to_string(defending_player.ownedCreatures[i].getPower()) + "/"
                             +to_string(defending_player.ownedCreatures[i].getToughness()) + ")";
                        cout << gameLog << endl;
                        gameLogWrite(gameLog);
                    }
                }
            }

            //Mana decrement handled by castingCostX();
        }
    }
}

void Player::Attack(Player &defending_player) {
    if(getName() == "Opponent"){
        for(int i = 0; i < ownedCreatures.size()-1; i++){
            if(ownedCreatures[i].getAvailability()){
                ownedCreatures[i].setAvailability(false);
                AttackCombat(defending_player,ownedCreatures[i]);
            }
        }
    }

    else {
        vector<Creature> availableCreaturesCheck;
        for (int i = 0; i < ownedCreatures.size(); i++) {
            if (ownedCreatures[i].getAvailability() == 1) {
                availableCreaturesCheck.push_back(ownedCreatures[i]);
            }
        }

        if (ownedCreatures.empty() && defending_player.ownedCreatures.empty() || availableCreaturesCheck.empty()) {
            cout << "No creatures available to attack, cast creatures using on your turn using [1]." << endl;
        } else {
            cout << "Select a creature [NUMBER] to attack with." << endl;
            string attackingCreature = selectAttacker();

            for (int i = 0; i < (ownedCreatures).size(); i++) {
                if (attackingCreature == to_string(ownedCreatures[i].getCreatureId())) {
                    ownedCreatures[i].setAvailability(false);
                    AttackCombat(defending_player, ownedCreatures[i]);
                }
            }
        }
    }
}

void Player::Damage_Creature(Player &defending_player) {

    if(getName() == "Opponent"){
        vector<Creature> availableDefendingCreatures;
        for(int i = 0; i < defending_player.ownedCreatures.size(); i++){
            availableDefendingCreatures.push_back(ownedCreatures[i]);
        }

        int creatureIdx;
        if(availableDefendingCreatures.size()!=0){
            creatureIdx = rand()%(availableDefendingCreatures.size());
        }
        else {
            return;
        }

        defending_player.ownedCreatures[creatureIdx].setToughness(defending_player.ownedCreatures[creatureIdx].getToughness() - 1);

        string gameLog = "-> " + getName() + " damaged [" + to_string(defending_player.ownedCreatures[creatureIdx].getCreatureId()) + "] to ("
             +to_string(defending_player.ownedCreatures[creatureIdx].getPower()) + "/" + to_string(defending_player.ownedCreatures[creatureIdx].getToughness()) + ")";

        cout << gameLog << endl;
        gameLogWrite(gameLog);

        setMana(getMana() - 2);
    }

    else {


        if (ownedCreatures.empty() && defending_player.ownedCreatures.empty()) {
            cout << "No creatures to damage, cast creatures using on your turn using [1]." << endl;
        } else {
            cout << "Select a creature [NUMBER] to damage:" << endl;
            string heal_select = selectCreature(defending_player);
            int casting_cost = castingCostX();

            //Assign creature x additional life, where x = casting_cost
            for (int i = 0; i < (ownedCreatures).size(); i++) {
                if (heal_select == to_string(ownedCreatures[i].getCreatureId())) {
                    ownedCreatures[i].setToughness(ownedCreatures[i].getToughness() - casting_cost);
                    string gameLog = "-> " + getName() + " damaged [" + to_string(ownedCreatures[i].getCreatureId()) + "] to ("
                         +to_string(ownedCreatures[i].getPower()) + "/" + to_string(ownedCreatures[i].getToughness()) + ")";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);
                }
            }

            for (int i = 0; i < (defending_player.ownedCreatures).size(); i++) {
                if (heal_select == to_string(defending_player.ownedCreatures[i].getCreatureId())) {
                    defending_player.ownedCreatures[i].setToughness(
                            (defending_player.ownedCreatures[i].getToughness()) - casting_cost);
                    string gameLog = "-> " + getName() + " damaged [" + to_string(defending_player.ownedCreatures[i].getCreatureId())
                         + "] to (" + to_string(defending_player.ownedCreatures[i].getPower())  + "/"
                         +to_string(defending_player.ownedCreatures[i].getToughness()) + ")";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);
                }
            }

            //Mana decrement handled by castingCostX();
        }
    }
    updateCreatures(defending_player);
}

void Player::Damage_Opponent(Player &targetPlayer) {
    int casting_cost = castingCostX();

    char check;
    while(casting_cost%2 == 1){
        cout << "Cannot damage opponent by .5 (values will be rounded down), you sure you want to continue? (y/n) ";
        cin >> check;

        if (check=='y' || check=='Y'){
            break;
        }
        else{
            //Refund value and retry paying x.
            setMana(getMana()+casting_cost);
            casting_cost = castingCostX();
        }
    }
    int newLife = targetPlayer.getLife()-(casting_cost/2);
    targetPlayer.setLife(newLife);

    string gameLog = "-> " + getName() + " shoots a fireball at " + targetPlayer.getName() + " for " +to_string(casting_cost/2) + " damage.";
    cout << gameLog << endl;
    gameLogWrite(gameLog);
    //Mana decrement handled by castingCostX();
}

void Player::Cast_Creature() {
    int casting_cost = castingCostX();

    int power = (casting_cost);
    int toughness = (casting_cost/2) + casting_cost;
    Creature newCreature(power,toughness);
    ownedCreatures.push_back(newCreature);
    string gameLog =  "-> " + getName() + " created a new creature [" + to_string(newCreature.getCreatureId()) +  "] with stats (" +
            to_string(power) + "/" + to_string(toughness)  +  ")";
    cout << gameLog << endl;
    gameLogWrite(gameLog);
}


//Combat Mechanics - Attacking
void Player::AttackCombat(Player &defending_player, Creature &creatureAttackingPlayer) {
    string gameLog = "-> " + getName() + " swings a (" + to_string(creatureAttackingPlayer.getPower()) + "/" + to_string(creatureAttackingPlayer.getToughness()) + ") creature at " + defending_player.getName();
    cout << gameLog << endl;
    gameLogWrite(gameLog);

    action_block(defending_player, creatureAttackingPlayer);
    updateCreatures(defending_player);
}


//Combat Mechanics - Blocking
void Player::action_block(Player &defending_player, Creature &creatureAttackingPlayer) {

    vector<Creature> availableCreatures;

    if (!(defending_player.ownedCreatures).empty()) {
        for (int i=0; i < (defending_player.ownedCreatures).size(); i++) {
            if ((defending_player.ownedCreatures)[i].getAvailability()) {
                availableCreatures.push_back((defending_player.ownedCreatures)[i]);
            }
        }
    }

    //USER Blocks
    if (defending_player.getName() != "Opponent") {
        if (!availableCreatures.empty()) {
            while (true) {
                char block;
                cout << "Would you like to block with a creature? (y/n) ";
                cin >> block;

                if (block == 'y' || block == 'Y') {
                    //BLocking -- > Creature Combat

                    //Choose creature to block
                    cout << "Select a creature to block with: " << endl;
                    string blockingCreatureID = selectBlocker(defending_player);

                    //Creature Combat
                    for (int i=0; i < (defending_player.ownedCreatures).size(); i++) {
                        if(blockingCreatureID == to_string(defending_player.ownedCreatures[i].getCreatureId())){
                            defending_player.ownedCreatures[i].setToughness(defending_player.ownedCreatures[i].getToughness()-creatureAttackingPlayer.getPower());
                            creatureAttackingPlayer.setToughness(creatureAttackingPlayer.getToughness()-defending_player.ownedCreatures[i].getPower());
                            string gameLog = "-> [" + to_string(creatureAttackingPlayer.getCreatureId()) + "] deals " + to_string(creatureAttackingPlayer.getPower()) + " damage to your creature [" + to_string(defending_player.ownedCreatures[i].getCreatureId()) + "], who retaliates with " + to_string(defending_player.ownedCreatures[i].getPower()) + " damage.";
                            cout << gameLog << endl;
                            gameLogWrite(gameLog);
                        }
                    }
                    return;
                } else if (block == 'n' || block == 'N') {
                    string gameLog = "-> Attacking creature connects, dealing " + to_string(creatureAttackingPlayer.getPower()) + " damage to " + defending_player.getName();
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);

                    defending_player.setLife((defending_player.getLife())-(creatureAttackingPlayer.getPower()));
                    return;
                } else {
                    cout << "Please type 'y' or 'n'" << endl;
                }
            }

        } else {
            cout << "No creatures available to block." << endl;
            string gameLog = "-> Attacking creature connects, dealing " + to_string(creatureAttackingPlayer.getPower()) + " damage to " + defending_player.getName();
            cout << gameLog << endl;
            gameLogWrite(gameLog);


            defending_player.setLife((defending_player.getLife())-(creatureAttackingPlayer.getPower()));
            return;
        }
    }

    //Opponent blocks
    else{
        if (!availableCreatures.empty()) {

            //Random creature to block


            int blockingCreatureID = defending_player.ownedCreatures[0].getCreatureId();

            for(int i = 0; i<defending_player.ownedCreatures.size(); i++){
                if(defending_player.ownedCreatures[i].getAvailability()){
                    blockingCreatureID = defending_player.ownedCreatures[i].getCreatureId();
                    break;
                }
            }


            //Creature Combat
            for (int i=0; i < (defending_player.ownedCreatures).size(); i++) {
                if(blockingCreatureID == (defending_player.ownedCreatures[i].getCreatureId())){
                    defending_player.ownedCreatures[i].setToughness(defending_player.ownedCreatures[i].getToughness()-creatureAttackingPlayer.getPower());
                    creatureAttackingPlayer.setToughness(creatureAttackingPlayer.getToughness()-defending_player.ownedCreatures[i].getPower());

                    string gameLog = "-> [" + to_string(creatureAttackingPlayer.getCreatureId()) + "] deals " + to_string(creatureAttackingPlayer.getPower()) + " damage to [" + to_string(defending_player.ownedCreatures[i].getCreatureId()) + "], who retaliates with " + to_string(defending_player.ownedCreatures[i].getPower()) + " damage.";
                    cout << gameLog << endl;
                    gameLogWrite(gameLog);

                    return;
                }
            }

        }
        else{
            string gameLog = "-> Attacking creature connects, dealing " + to_string(creatureAttackingPlayer.getPower()) + " damage to " + defending_player.getName();
            cout << gameLog << endl;
            gameLogWrite(gameLog);


            defending_player.setLife((defending_player.getLife())-(creatureAttackingPlayer.getPower()));
            return;
        }

    }
}


//================================ Misc Functions for Player Class ===========================
string Player::selectCreature(Player defending_player){
    //Construct list of valid creatures
    vector<Creature> availableCreatures;

    //Users creatures
    cout << "Your creatures: ";
    for (int i=0; i < (ownedCreatures).size(); i++) {
        availableCreatures.push_back(ownedCreatures[i]);
        cout << "[" << ownedCreatures[i].getCreatureId() << "] (" << ownedCreatures[i].getPower() << "/" << ownedCreatures[i].getToughness() << ")  ";
    }
    cout << endl;

    if(!defending_player.ownedCreatures.empty()) {
        cout << "Opponents creatures: ";
        for (int i = 0; i < (defending_player.ownedCreatures).size(); i++) {
            availableCreatures.push_back(defending_player.ownedCreatures[i]);
            cout << "[" << defending_player.ownedCreatures[i].getCreatureId() << "] (" << defending_player.ownedCreatures[i].getPower() << "/" << defending_player.ownedCreatures[i].getToughness() << ")  ";
        }
        cout << endl;
    }


    //Check Selection
    bool check = true;

    string select;

    while (check) {
        cin >> select;
        for (int i = 0; i < availableCreatures.size(); i++) {
            if ((select) == to_string(availableCreatures[i].getCreatureId())) {
                check = false;
                break;
            }
        }
        if (check){
            cout << "Please enter a valid creature NUMBER, creatures are identified as [NUMBER]" << endl;
        }
    }
    return select;
}


string Player::selectAttacker(){
    vector <Creature> availableCreatures;
    cout << "Your Available Creatures: ";

    for (int i = 0; i < ownedCreatures.size(); i++) {
        if (ownedCreatures[i].getAvailability() == 1) {
            cout << "[" << (ownedCreatures)[i].getCreatureId() << "] " << (ownedCreatures)[i].getPower() << "/" <<
                 (ownedCreatures)[i].getToughness() << "   ";
            availableCreatures.push_back(ownedCreatures[i]);

        }
    }

    //Check Selection
    bool check = true;

    string select;

    while (check) {
        cin >> select;
        for (int i = 0; i < availableCreatures.size(); i++) {
            if ((select) == to_string(availableCreatures[i].getCreatureId())) {
                check = false;
                break;
            }
        }
        if (check){
            cout << "Please enter a valid creature NUMBER, creatures are identified as [NUMBER]" << endl;
        }
    }
    return select;
}


string Player::selectBlocker(Player &defending_player) {
    vector<Creature> availableCreatures;
    cout << "Your Available Creatures: ";
    if (!(defending_player.ownedCreatures).empty()) {
        for (int i=0; i < (defending_player.ownedCreatures).size(); i++) {
            if ((defending_player.ownedCreatures)[i].getAvailability()) {
                cout << "[" << (defending_player.ownedCreatures)[i].getCreatureId() << "] " << (defending_player.ownedCreatures)[i].getPower() << "/" <<
                     (defending_player.ownedCreatures)[i].getToughness() << "   ";
                availableCreatures.push_back(defending_player.ownedCreatures[i]);
            }
        }
    }

        //Check Selection
        bool check = true;

        string select;

        while (check) {
            cin >> select;
            for (int i = 0; i < availableCreatures.size(); i++) {
                if ((select) == to_string(availableCreatures[i].getCreatureId())) {
                    check = false;
                    break;
                }
            }
            if (check) {
                cout << "Please enter a valid creature NUMBER, creatures are identified as [NUMBER]" << endl;
            }
        }
        return select;
}


int Player::castingCostX(){
    //x mana
    int casting_cost;

    if(getName()=="Opponent"){
        casting_cost = (rand()%getMana() - 2);
        if (casting_cost <= 0){
            casting_cost = 1;
        }
    }

    else {
        while (true) {
            cout << "Select a value for 'x': ";
            cin >> casting_cost;

            //https://www.codespeedy.com/taking-only-integer-input-in-cpp/ - Used to parse for ints
            if (!cin) {
                cout << "Please enter a numerical value." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }


            if (int(casting_cost) > getMana()) {
                cout << "Please enter a Mana value less than or equal to " << getMana() << endl;
            } else {
                break;
            }
        }
    }

    //Update mana pool
    setMana(getMana()-casting_cost);

    return casting_cost;
}

void Player::updateCreatures(Player &defending_player) {

    //Attacker update
    for(int i = 0; i < ownedCreatures.size(); i++){
        if(ownedCreatures[i].getToughness() <= 0){
            string gameLog = "-> [" + to_string(ownedCreatures[i].getCreatureId()) + "] has been slain and left the battlefield.";
            ownedCreatures.erase (ownedCreatures.begin()+i);
            cout << gameLog << endl;
            gameLogWrite(gameLog);
        }
    }

    //Defender update
    for(int i = 0; i < defending_player.ownedCreatures.size(); i++){
        if(defending_player.ownedCreatures[i].getToughness() <= 0){
            string gameLog = "-> [" + to_string(defending_player.ownedCreatures[i].getCreatureId()) + "] has been slain and left the battlefield.";
            defending_player.ownedCreatures.erase (defending_player.ownedCreatures.begin()+i);
            cout << gameLog << endl;
            gameLogWrite(gameLog);
        }
    }
}

//==================== Opponent Game Logic =================================
bool Player::opponent_game_logic(Player &defending_player) {

    vector<Creature> availableCreatures;
    for(int i = 0; i < ownedCreatures.size(); i++){
        if(ownedCreatures[i].getAvailability()){
            availableCreatures.push_back(ownedCreatures[i]);
        }
    }

    //1 - Swing for kill if in range
    if(defending_player.getLife() <= (getMana()/2)){
        int casting_cost = getMana();
        int newLife = defending_player.getLife()-(casting_cost/2);
        defending_player.setLife(newLife);
        string gameLog = "-> " + getName() + " deals the finishing blow to " + defending_player.getName() + " for " + to_string(casting_cost/2) + " damage using a fireball [6].";
        cout << gameLog << endl;
        gameLogWrite(gameLog);

        return false;
    }

    //2 - Create creatures (3/4 of the time when mana is available)
    else if ((getMana() > 1) && rand()%4 >= 1){
        Cast_Creature();
        return true;
    }
    //3 - Swing with some creatures
    else if (availableCreatures.size()>1 && rand()%4 >= 1) {
        Attack(defending_player);
        return true;
    }

    //4 - Rand use of damage, heal, and buffs
    else if (!ownedCreatures.empty() && getMana() > 0){
        int action = rand()%3;

        switch (action) {
            case 0:
                if(getMana() >= 2) {
                    Buff_Creature(defending_player);
                }
                break;
            case 1:
                Heal_Creature(defending_player);
                break;
            case 2:
                Damage_Creature(defending_player);
                break;
        }
        return true;
    }

    else{
        return false;
    }

    return true;
}