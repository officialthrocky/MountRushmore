#include "player.h"
#include <string>
#include <vector>
using namespace std;

Player::Player()
{
  playerName = "Null";
  points = 0;
};

Player::Player(string name)
{
  playerName = name;
  points = 0;
};

Player::~Player()
{
  picks.clear();
};

void Player::operator=(const Player &x)
{
  playerName = x.playerName;
  picks = x.picks;
  points = x.points;
}