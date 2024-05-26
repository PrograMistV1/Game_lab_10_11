#include "headers/Player.h"

Player::Player() {
    this->inventory = new Inventory(5);
}


Inventory *Player::getInventory() const {
    return this->inventory;
}

void Player::save() {
}

int Player::getHealth() const {
    return this->health;
}

int Player::getMaxHealth() const {
    return this->maxHealth;
}

void Player::setHealth(const int health) {
    this->health = health;
}

void Player::setMaxHealth(const int health) {
    this->maxHealth = health;
}

int Player::getEnergy() const {
    return this->energy;
}

int Player::getMaxEnergy() const {
    return this->maxEnergy;
}

void Player::setEnergy(const int energy) {
    this->energy = energy;
}

void Player::setMaxEnergy(const int energy) {
    this->maxEnergy = energy;
}
