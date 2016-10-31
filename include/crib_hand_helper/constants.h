#ifndef CRIB_CONSTANTS_H
#define CRIB_CONSTANTS_H

#include <string>
#include <vector>

namespace crib
{
  const std::string CARD_NAMES = "A23456789TJQK";
  const std::string CARD_SUITS = "cdhs";

  using IndexSets = std::vector<std::vector<unsigned>>;

  const IndexSets FIVE_CHOOSE_TWO_INDICES = {{0, 1}, {0, 2}, {0, 3}, {0, 4},
                                             {1, 2}, {1, 3}, {1, 4}, {2, 3},
                                             {2, 4}, {3, 4}};
  const IndexSets FIVE_CHOOSE_THREE_INDICES = {
      {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 3}, {0, 2, 4},
      {0, 3, 4}, {1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}};
  const IndexSets FIVE_CHOOSE_FOUR_INDICES = {
      {0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 4}, {0, 2, 3, 4}, {1, 2, 3, 4}};
  const IndexSets FIVE_CHOOSE_FIVE_INDICES = {{0, 1, 2, 3, 4}};

  const std::vector<IndexSets> ALL_SETS = {
      FIVE_CHOOSE_TWO_INDICES, FIVE_CHOOSE_THREE_INDICES,
      FIVE_CHOOSE_FOUR_INDICES, FIVE_CHOOSE_FIVE_INDICES};

  const IndexSets SIX_CHOOSE_TWO_INDICES = {
      {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4},
      {1, 5}, {2, 3}, {2, 4}, {2, 5}, {3, 4}, {3, 5}, {4, 5}};
} /* crib */

#endif /* ifndef CRIB_CONSTANTS */
