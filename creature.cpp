//
// Created by chase on 10/7/2022.
//

#include "creature.h"
#include "functions.h"

int creatureID = 0;

Creature::Creature(int Power, int Toughness) {
    _Power = Power;
    _Toughness = Toughness;
    _isAvailable = true;
    _creatureId = creatureCounter(creatureID);
}

void Creature::setToughness(int newToughness) {
    _Toughness = newToughness;
}

int Creature::getPower() const {
    return _Power;
}

int Creature::getToughness() const {
    return _Toughness;
}

bool Creature::getAvailability() const {
    return _isAvailable;
}

void Creature::setAvailability(bool available) {
    _isAvailable = available;
}

int Creature::getCreatureId() {
    return _creatureId;
}

void Creature::setPower(int newStrength) {
    _Power = newStrength;
}
