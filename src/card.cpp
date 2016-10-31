#include "crib_hand_helper/card.h"

namespace crib
{
  Card::Card(char name, char suit) : name(name), suit(suit)
  {
    switch (name)
    {
      case 'A':
        rank = 1;
        break;
      case 'T':
        rank = 10;
        break;
      case 'J':
        rank = 11;
        break;
      case 'Q':
        rank = 12;
        break;
      case 'K':
        rank = 13;
        break;
      default:
        rank = name - '0';
    }

    value = rank < 11 ? rank : 10;
  }
} /* crib */
