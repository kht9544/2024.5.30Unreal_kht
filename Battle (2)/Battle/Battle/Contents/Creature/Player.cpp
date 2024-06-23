#include "pch.h"
#include "Player.h"

Player::Player(string name, int hp, int atk)
// : Creature()
: Creature(name, hp, atk)
, _exp(0)
{
}

Player::~Player()
{
}
