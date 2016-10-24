#include "crib_hand_helper/hand_counter.h"

namespace
{
  unsigned count_fifteens(const Hand& hand, const Card& cut)
  {
    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;
    for (Hand::size_type i = 0; i < h.size(); ++i)
    {
      for (Hand::size_type j = i + 1; j < h.size(); ++j)
      {
        if (h[i].value + h[j].value == 15)
        {
          score += 2;
        }
        for (Hand::size_type k = j + 1; k < h.size(); ++k)
        {
          if (h[i].value + h[j].value + h[k].value ==
              15)
          {
            score += 2;
          }
          for (Hand::size_type m = k + 1; m < h.size(); ++m)
          {
            if (h[i].value + h[j].value + h[k].value +
                    h[m].value ==
                15)
            {
              score += 2;
            }
          }
        }
      }
    }
    if (h[0].value + h[1].value + h[2].value + h[3].value + h[4].value == 15)
    {
      score += 2;
    }
    return score;
  }

  unsigned count_pairs(const Hand& hand, const Card& cut)
  {
    Hand h = hand;
    h.push_back(cut);

    unsigned score = 0;
    for (Hand::size_type i = 0; i < h.size(); ++i)
    {
      for (Hand::size_type j = i + 1; j < h.size(); ++j)
      {
        if (h[i].rank == h[j].rank)
        {
          score += 2;
        }
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
    for (decltype(hand.size()) i = 1; i < hand.size(); ++i)
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
