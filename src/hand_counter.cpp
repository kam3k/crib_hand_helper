#include <algorithm>
#include <cassert>
#include <vector>

#include "crib_hand_helper/constants.h"
#include "crib_hand_helper/hand_counter.h"

namespace
{
  unsigned count_fifteens(const Hand& hand, const Card& cut)
  {
    assert(hand.size() == 4);

    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;
    unsigned sum = 0;

    for (const auto& sets : ALL_SETS)
    {
      for (const auto& indices : sets)
      {
        sum = 0;
        for (const auto& index : indices)
        {
          sum += h[index].value;
        }
        if (sum == 15)
        {
          score += 2;
        }
      }
    }

    return score;
  }

  unsigned count_pairs(const Hand& hand, const Card& cut)
  {
    assert(hand.size() == 4);

    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;
    for (const auto& indices : FIVE_CHOOSE_TWO_INDICES)
    {
      if (h[indices[0]].rank == h[indices[1]].rank)
      {
        score += 2;
      }
    }

    return score;
  }

  unsigned count_runs_of_three(const Hand& hand)
  {
    assert(hand.size() == 5);

    unsigned score = 0;

    for (const auto& indices : FIVE_CHOOSE_THREE_INDICES)
    {
      for (Hand::size_type i = 1; i < indices.size(); ++i)
      {
        if (hand[indices[i]].rank != hand[indices[i - 1]].rank + 1)
        {
          break;
        }
        else if (i == indices.size() - 1)
        {
          score += 3;
        }
      }
    }

    return score;
  }

  unsigned count_runs_of_four(const Hand& hand)
  {
    assert(hand.size() == 5);

    unsigned score = 0;

    for (const auto& indices : FIVE_CHOOSE_FOUR_INDICES)
    {
      for (Hand::size_type i = 1; i < indices.size(); ++i)
      {
        if (hand[indices[i]].rank != hand[indices[i - 1]].rank + 1)
        {
          break;
        }
        else if (i == indices.size() - 1)
        {
          score += 4;
        }
      }
    }

    return score;
  }

  unsigned count_runs_of_five(const Hand& hand)
  {
    assert(hand.size() == 5);

    for (Hand::size_type i = 1; i < hand.size(); ++i)
    {
      if (hand[i].rank != hand[i - 1].rank + 1)
      {
        return 0;
      }
    }
    return 5;
  }

  unsigned count_runs(const Hand& hand, const Card& cut)
  {
    assert(hand.size() == 4);

    Hand h = hand;
    h.push_back(cut);
    std::sort(h.begin(), h.end(), [](const Card& card_1, const Card& card_2) {
      return card_1.rank < card_2.rank;
    });

    auto score = count_runs_of_five(h);

    if (score == 0)
    {
      score += count_runs_of_four(h);
      if (score == 0)
      {
        score += count_runs_of_three(h);
      }
    }

    return score;
  }

  unsigned count_flush(const Hand& hand, const Card& cut)
  {
    assert(hand.size() == 4);

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
    assert(hand.size() == 4);

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
  assert(hand.size() == 4);

  return count_fifteens(hand, cut) + count_pairs(hand, cut) +
         count_runs(hand, cut) + count_flush(hand, cut) + count_nobs(hand, cut);
}
