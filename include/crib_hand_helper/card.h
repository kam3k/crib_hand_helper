#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

namespace crib
{
  struct Card
  {
    Card() = delete;
    Card(char name, char suit);
    Card(const std::string& name_and_suit)
      : Card(name_and_suit[0], name_and_suit[1]){};
    unsigned rank;   // 1 (ace) to 13 (king)
    unsigned value;  // 1-9 (A-9) and 10 (T-K)
    char name;       // 'A', '2', ..., 'T', 'J', 'Q', 'K'
    char suit;       // 'c', 'd', 'h', or 's'
  };

  using Hand = std::vector<Card>;
} /* crib */

#endif /* ifndef CARD_H */
