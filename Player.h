//
// Created by chase on 10/7/2022.
//

#ifndef CODE_PLAYER_H
#define CODE_PLAYER_H

#include "creature.h"
#include "string"
#include "vector"

using namespace std;


class Player{
public:
    Player(); //when a player obj is instantiated, they will always have the same starting values

    int getLife() const;
    void setLife(int newLife);
    int getMana() const;
    void setMana(int newMana);
    std::string getName() const;
    void setName();

    //Attack Actions (Player's turn)
    bool action_attack(Player &defending_player); //user prompt for choosing and executing attack options below
    void Buff_Creature(Player &defending_player);
    void Heal_Creature(Player &defending_player);
    void Attack(Player &targetPlayer); //%
    void Damage_Creature(Player &defending_player);
    void Damage_Opponent(Player &targetPlayer);
    void Cast_Creature();
    void AttackCombat(Player &defending_player, Creature &creatureAttackingPlayer);


    //Block Actions
    void action_block(Player &defending_player, Creature &creatureAttackingPlayer); //user prompt for choosing and executing block options
    string selectBlocker(Player &defending_player);


    //Misc Functions
    string selectCreature(Player defending_player);
    string selectAttacker();
    int castingCostX();
    void updateCreatures(Player &defending_player);

    //Opponent Logic
    bool opponent_game_logic(Player &defending_player);

    //Creatures player owns
    vector <Creature> ownedCreatures;

private:
    int _Life;
    int _Mana;
    std::string _name;
};


#endif //CODE_PLAYER_H
