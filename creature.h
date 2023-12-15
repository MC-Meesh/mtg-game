//
// Created by chase on 10/7/2022.
//

#ifndef CODE_CREATURE_H
#define CODE_CREATURE_H

#include "string"

class Creature{
public:
    Creature(int Power, int Toughness);
    void Block(Creature tarGetCreature);

    int getToughness() const;
    void setToughness(int newToughness);
    int getPower() const;
    void setPower(int newStrength);
    bool getAvailability() const;
    void setAvailability(bool available);
    int getCreatureId();



private:
    int _Power;
    int _Toughness;
    bool _isAvailable;
    int _creatureId;
};

#endif //CODE_CREATURE_H
