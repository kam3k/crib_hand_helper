#include <string>

#include "crib_hand_helper/card.h"

Card::Card(unsigned rank, char suit) : rank(rank), suit(suit)
{
  value = rank < 11 ? rank : 10;

  switch (rank)
  {
    case 1:
      name = 'A';
    case 10:
      name = 'T';
    case 11:
      name = 'J';
    case 12:
      name = 'Q';
    case 13:
      name = 'K';
    default:
      name = std::to_string(rank)[0];
  }
}

Card::Card(char name, char suit) : name(name), suit(suit)
{
  switch (name)
  {
    case 'A':
      rank = 1;
    case 'T':
      rank = 10;
    case 'J':
      rank = 11;
    case 'Q':
      rank = 12;
    case 'K':
      rank = 13;
    default:
      rank = std::stoi(std::string(1, name));
  }

  value = rank < 11 ? rank : 10;
}
