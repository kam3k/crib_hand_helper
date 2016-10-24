#ifndef CARD_H
#define CARD_H

#include <vector>

struct Card
{
  Card() = delete;
  Card(unsigned rank, char suit);
  Card(char name, char suit);
  unsigned rank; // 1 (ace) to 13 (king)
  unsigned value; // 1-9 (A-9) and 10 (T-K)
  char name; // 'A', '2', ..., 'T', 'J', 'Q', 'K'
  char suit; // 'c', 'd', 'h', or 's'
};

using Hand = std::vector<Card>;

#endif /* ifndef CARD_H */
