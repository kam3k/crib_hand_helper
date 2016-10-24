#include <tuple>

#include "crib_hand_helper/hand_counter.h"

using std::make_tuple;
using std::get;

namespace
{
  using SetsOfTwo = std::vector<std::tuple<int, int>>;
  using SetsOfThree = std::vector<std::tuple<int, int, int>>;
  using SetsOfFour = std::vector<std::tuple<int, int, int, int>>;
  using SetsOfFive = std::vector<std::tuple<int, int, int, int, int>>;

  const SetsOfTwo SETS_OF_TWO = {
      make_tuple(0, 1), make_tuple(0, 2), make_tuple(0, 3), make_tuple(0, 4),
      make_tuple(1, 2), make_tuple(1, 3), make_tuple(1, 4), make_tuple(2, 3),
      make_tuple(2, 4), make_tuple(3, 4)};

  const SetsOfThree SETS_OF_THREE = {make_tuple(0, 1, 2), make_tuple(0, 1, 3),
                                     make_tuple(0, 1, 4), make_tuple(0, 2, 3),
                                     make_tuple(0, 2, 4), make_tuple(0, 3, 4),
                                     make_tuple(1, 2, 3), make_tuple(1, 2, 4),
                                     make_tuple(1, 3, 4), make_tuple(2, 3, 4)};

  const SetsOfFour SETS_OF_FOUR = {
      make_tuple(0, 1, 2, 3), make_tuple(0, 1, 2, 4), make_tuple(0, 1, 3, 4),
      make_tuple(0, 2, 3, 4), make_tuple(1, 2, 3, 4)};

  const SetsOfFive SETS_OF_FIVE = {make_tuple(0, 1, 2, 3, 4)};

  unsigned count_fifteens(const Hand& hand, const Card& cut)
  {
    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;

    for (const auto& indices : SETS_OF_TWO)
    {
      if (h[get<0>(indices)].value + h[get<1>(indices)].value == 15)
      {
        score += 2;
      }
    }

    for (const auto& indices : SETS_OF_THREE)
    {
      if (h[get<0>(indices)].value + h[get<1>(indices)].value +
              h[get<2>(indices)].value ==
          15)
      {
        score += 2;
      }
    }

    for (const auto& indices : SETS_OF_FOUR)
    {
      if (h[get<0>(indices)].value + h[get<1>(indices)].value +
              h[get<2>(indices)].value + h[get<3>(indices)].value ==
          15)
      {
        score += 2;
      }
    }

    for (const auto& indices : SETS_OF_FIVE)
    {
      if (h[get<0>(indices)].value + h[get<1>(indices)].value +
              h[get<2>(indices)].value + h[get<3>(indices)].value +
              h[get<4>(indices)].value ==
          15)
      {
        score += 2;
      }
    }

    return score;
  }

  unsigned count_pairs(const Hand& hand, const Card& cut)
  {
    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;
    for (const auto& indices : SETS_OF_TWO)
    {
      if (h[std::get<0>(indices)].rank == h[std::get<1>(indices)].rank)
      {
        score += 2;
      }
    }

    return score;
  }

  unsigned count_runs(const Hand& hand, const Card& cut)
  {
    return 0;
  }

  unsigned count_flush(const Hand& hand, const Card& cut)
  {
    const auto& suit = hand[0].suit;
    for (Hand::size_type i = 1; i < hand.size(); ++i)
    {
      if (hand[i].suit != suit)
      {
        return 0;
      }
    }
    return cut.suit == suit ? 5 : 4;
  }

  unsigned count_nobs(const Hand& hand, const Card& cut)
  {
    for (const auto& card : hand)
    {
      if (card.name == 'J' && card.suit == cut.suit)
      {
        return 1;
      }
    }
    return 0;
  }
}

unsigned count_hand(const Hand& hand, const Card& cut)
{
  return count_fifteens(hand, cut) + count_pairs(hand, cut) +
         count_runs(hand, cut) + count_flush(hand, cut) + count_nobs(hand, cut);
}
