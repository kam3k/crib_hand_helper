#ifndef CARD_H
#define CARD_H

#include <array>

struct Card
{
  unsigned rank;
  char suit;
};

using Hand = std::array<Card, 6>;

#endif /* ifndef CARD_H */
